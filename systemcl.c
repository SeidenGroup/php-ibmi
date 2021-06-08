/* ibmi extension for PHP (c) 2021 Calvin Buckley */

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include <stdio.h>
#include <ctype.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <as400_protos.h>

#include "php.h"
#include "ext/standard/info.h"
#include "SAPI.h"
#include "php_ibmi.h"
#if PHP_MAJOR_VERSION >= 8
#include "ibmi_arginfo.h"
#else
#include "ibmi_legacy_arginfo.h"
#endif

/* For compatibility with older PHP versions */
#ifndef ZEND_PARSE_PARAMETERS_NONE
#define ZEND_PARSE_PARAMETERS_NONE() \
	ZEND_PARSE_PARAMETERS_START(0, 0) \
	ZEND_PARSE_PARAMETERS_END()
#endif

/* XXX: These should be moved to their own header so they aren't duplicated */
#define IBMI_CL_EBCDIC_OUTPUT 0x1
#define IBMI_CL_SPAWN 0x2
#define IBMI_CL_NO_MESSAGES 0x4

/**
 * We prefer building the flags instead of passing them to raw to PHP because
 * the default semantics are tricky for the average IBM i user.
 */
static int build_systemCL_flags(int php_flags)
{
	int new_flags = 0;
	/* Capture spool to stdout, like "system" does. Maybe keep it later. */
	/* XXX: make optional? */
	new_flags |= SYSTEMCL_SPOOL_STDOUT;
	/* Do the right thing by default (ASCII translation, out into EBCDIC) */
	if (!(php_flags & IBMI_CL_EBCDIC_OUTPUT)) {
		/* XXX: We don't filter stdin because we don't expect it */
		new_flags |= (SYSTEMCL_FILTER_STDOUT | SYSTEMCL_FILTER_STDERR);
	}
	if (php_flags & IBMI_CL_SPAWN) {
		new_flags |= SYSTEMCL_SPAWN;
	}
	if (!(php_flags & IBMI_CL_NO_MESSAGES)) {
		/* It doesn't really matter for now, since it's all jumbled... */
		new_flags |= SYSTEMCL_MSG_STDOUT;
	}
	/* XXX: keep spool, environment, remove msgid */
	return new_flags;
}

/**
 * Doesn't fork, but temporarily replaces stdout/stderr into a single stream.
 * This allows PHP to intercept the output from systemCL, while executing in
 * the context of the PHP process (so i.e chgjob works).
 */
static FILE* php_ibmi_popen(const char *cl, int flags)
{
	int fds[2], tmpout = -1, tmperr = -1;

	/* read from fds[0], dup fds[1] as XPF's stdout/stderr */
	if (pipe(fds) == -1) {
		return NULL;
	}

	/* XXX: Set CLOEXEC for new pipes, and if needed on out/err. Mutex? */
	tmpout = dup(1);
	if (tmpout == -1) {
		goto fail;
	}
	tmperr = dup(2);
	if (tmperr == -1) {
		goto fail;
	}
	/* XXX: error checking here */
	dup2(fds[1], 1);
	dup2(fds[1], 2);
	systemCL(cl, flags);
	dup2(tmpout, 1);
	dup2(tmperr, 2);
	fsync(fds[1]);
	close(fds[1]);
	return fdopen(fds[0], "r");
fail:
	if (tmpout != -1) {
		close(tmpout);
	}
	if (tmperr != -1) {
		close(tmperr);
	}
	close(fds[0]);
	close(fds[1]);
	return NULL;
}

static size_t strip_trailing_whitespace(char *buf, size_t bufl) {
	size_t l = bufl;
	while (l-- > 0 && isspace(((unsigned char *)buf)[l]));
	if (l != (bufl - 1)) {
		bufl = l + 1;
		buf[bufl] = '\0';
	}
	return bufl;
}

static size_t handle_line(int type, zval *array, char *buf, size_t bufl) {
	if (type == 1) {
		PHPWRITE(buf, bufl);
		if (php_output_get_level() < 1) {
			sapi_flush();
		}
	} else if (type == 2) {
		bufl = strip_trailing_whitespace(buf, bufl);
		add_next_index_stringl(array, buf, bufl);
	}
	return bufl;
}

/* {{{ php_ibmi_exec
 * If type==0, only last line of output is returned (exec)
 * If type==1, all lines will be printed and last lined returned (system)
 * If type==2, all lines will be saved to given array (exec with &$array)
 * If type==3, output will be printed binary, no lines will be saved or returned (passthru)
 *
 */
PHPAPI int php_ibmi_exec(int type, const char *cmd, int flags, zval *array, zval *return_value)
{
	FILE *fp;
	char *buf;
	int pclose_return;
	char *b, *d=NULL;
	php_stream *stream;
	size_t buflen, bufl = 0;
#if PHP_SIGCHILD
	void (*sig_handler)() = NULL;
#endif

#if PHP_SIGCHILD
	sig_handler = signal (SIGCHLD, SIG_DFL);
#endif

	fp = php_ibmi_popen(cmd, build_systemCL_flags(flags));

	if (!fp) {
		php_error_docref(NULL, E_WARNING, "Unable to fork [%s]", cmd);
		goto err;
	}

	stream = php_stream_fopen_from_pipe(fp, "rb");

	buf = (char *) emalloc(EXEC_INPUT_BUF);
	buflen = EXEC_INPUT_BUF;

	if (type != 3) {
		b = buf;

		while (php_stream_get_line(stream, b, EXEC_INPUT_BUF, &bufl)) {
			/* no new line found, let's read some more */
			if (b[bufl - 1] != '\n' && !php_stream_eof(stream)) {
				if (buflen < (bufl + (b - buf) + EXEC_INPUT_BUF)) {
					bufl += b - buf;
					buflen = bufl + EXEC_INPUT_BUF;
					buf = erealloc(buf, buflen);
					b = buf + bufl;
				} else {
					b += bufl;
				}
				continue;
			} else if (b != buf) {
				bufl += b - buf;
			}

			bufl = handle_line(type, array, buf, bufl);
			b = buf;
		}
		if (bufl) {
			if (buf != b) {
				/* Process remaining output */
				bufl = handle_line(type, array, buf, bufl);
			}

			/* Return last line from the shell command */
			bufl = strip_trailing_whitespace(buf, bufl);
			RETVAL_STRINGL(buf, bufl);
		} else { /* should return NULL, but for BC we return "" */
			RETVAL_EMPTY_STRING();
		}
	} else {
		ssize_t read;
		while ((read = php_stream_read(stream, buf, EXEC_INPUT_BUF)) > 0) {
			PHPWRITE(buf, read);
		}
	}

	pclose_return = php_stream_close(stream);
	efree(buf);

done:
#if PHP_SIGCHILD
	if (sig_handler) {
		signal(SIGCHLD, sig_handler);
	}
#endif
	if (d) {
		efree(d);
	}
	return pclose_return;
err:
	pclose_return = -1;
	RETVAL_FALSE;
	goto done;
}
/* }}} */

static void php_ibmi_exec_ex(INTERNAL_FUNCTION_PARAMETERS, int mode) /* {{{ */
{
	char *cmd;
	size_t cmd_len;
	zval *ret_array=NULL;
	int ret;
	zend_long flags = 0;

	ZEND_PARSE_PARAMETERS_START(1, (mode ? 2 : 3))
		Z_PARAM_STRING(cmd, cmd_len)
		Z_PARAM_OPTIONAL
		Z_PARAM_LONG(flags);
		if (!mode) {
			Z_PARAM_ZVAL(ret_array)
		}
	ZEND_PARSE_PARAMETERS_END();

	if (!cmd_len) {
		zend_argument_value_error(1, "cannot be empty");
		RETURN_THROWS();
	}
	if (strlen(cmd) != cmd_len) {
		zend_argument_value_error(1, "must not contain any null bytes");
		RETURN_THROWS();
	}

	if (!ret_array) {
		ret = php_ibmi_exec(mode, cmd, flags, NULL, return_value);
	} else {
		if (Z_TYPE_P(Z_REFVAL_P(ret_array)) == IS_ARRAY) {
			ZVAL_DEREF(ret_array);
			SEPARATE_ARRAY(ret_array);
		} else {
			ret_array = zend_try_array_init(ret_array);
			if (!ret_array) {
				RETURN_THROWS();
			}
		}

		ret = php_ibmi_exec(2, cmd, flags, ret_array, return_value);
	}
}
/* }}} */

/* {{{ Execute an external program */
PHP_FUNCTION(ibmi_cl_exec)
{
	php_ibmi_exec_ex(INTERNAL_FUNCTION_PARAM_PASSTHRU, 0);
}
/* }}} */

/* {{{ Execute an external program and display output */
PHP_FUNCTION(ibmi_cl_system)
{
	php_ibmi_exec_ex(INTERNAL_FUNCTION_PARAM_PASSTHRU, 1);
}
/* }}} */

/* {{{ Execute an external program and display raw output */
PHP_FUNCTION(ibmi_cl_passthru)
{
	/* TODO: This could just call systemCL directly for a fast path? */
	php_ibmi_exec_ex(INTERNAL_FUNCTION_PARAM_PASSTHRU, 3);
}
/* }}} */
