/* ibmi extension for PHP (c) 2021 Calvin Buckley */
#include "php_ibmi_int.h"

#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <as400_protos.h>

/* {{{ int ibmi_stat() */
PHP_FUNCTION(ibmi_stat)
{
	struct stat64_ILE ile_stat;
	char *filename, *objtype_first_space;
	size_t filename_len;
	int rc;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STRING(filename, filename_len)
	ZEND_PARSE_PARAMETERS_END();

	if (!filename_len) {
		zend_argument_value_error(1, "cannot be empty");
		RETURN_THROWS();
	}
	if (strlen(filename) != filename_len) {
		zend_argument_value_error(1, "must not contain any null bytes");
		RETURN_THROWS();
	}

	/* gotta love the foresight of POSIX */
	rc = statx(filename, (struct stat*)&ile_stat, sizeof(ile_stat), STX_XPFSS_PASE);
	if (rc == -1) {
		php_error_docref(NULL, E_WARNING, "%s", strerror(errno));
		RETURN_FALSE;
	}

	/* Truncate the string; IBM i fixed-length fields pad with spaces */
	objtype_first_space = strchr(ile_stat.st_objtype, ' ');
	if (objtype_first_space != NULL) {
		*objtype_first_space = '\0';
	}

	array_init(return_value);
	/*
	 * We don't add a numeric index, just associative. This can be changed
	 * if we want to more closely match the semantics of PHP stat.
	 */
	add_assoc_long(return_value, "codepage", ile_stat.st_codepage);
	add_assoc_stringl(return_value, "objtype", ile_stat.st_objtype, strlen(ile_stat.st_objtype));
	add_assoc_long(return_value, "ccsid", ile_stat.st_ccsid);
}
/* }}} */