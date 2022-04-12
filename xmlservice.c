/*
   +----------------------------------------------------------------------+
   | Copyright (c) Seiden Group                                           |
   +----------------------------------------------------------------------+
   | This source file is subject to version 3.01 of the PHP license,      |
   | that is bundled with this package in the file LICENSE, and is        |
   | available through the world-wide-web at the following url:           |
   | https://www.php.net/license/3_01.txt                                 |
   | If you did not receive a copy of the PHP license and are unable to   |
   | obtain it through the world-wide-web, please send a note to          |
   | license@php.net so we can mail you a copy immediately.               |
   +----------------------------------------------------------------------+
   | Author: Calvin Buckley <calvin@cmpct.info>                           |
   +----------------------------------------------------------------------+
 */

#include "php_ibmi_int.h"

#include <as400_protos.h>

/* XXX: Should these be configurable? */
static const char *srvpgm = "QXMLSERV/XMLSTOREDP";
static const char *procedure_symbol = "RUNASCII";

static int mypid = -1;
static unsigned long long activation_mark = -1;
static ILEpointer procedure __attribute__ ((aligned (16))) = {0};

static const arg_type_t signature[] = {
	ARG_MEMPTR,
	ARG_MEMPTR,
	ARG_MEMPTR,
	ARG_MEMPTR,
	ARG_MEMPTR,
	ARG_MEMPTR,
	ARG_MEMPTR,
	ARG_MEMPTR,
	ARG_MEMPTR,
	ARG_MEMPTR,
	ARG_END
};

static bool should_initialize_ffi(void)
{
	/* Forking invalidates ILEpointers/actmarks */
	if (mypid == -1) {
		mypid = getpid();
	} else if (mypid != getpid()) {
		return true;
	}

	return activation_mark == -1;
}

static bool initialize_ffi(void)
{
	activation_mark = _ILELOADX(srvpgm, ILELOAD_LIBOBJ);
	if (activation_mark == -1) {
		php_error_docref(NULL, E_ERROR, "Couldn't load service program %s", srvpgm);
		return false;
	}
	if (_ILESYMX(&procedure, activation_mark, procedure_symbol) == -1) {
		php_error_docref(NULL, E_ERROR, "Couldn't load symbol %s", procedure_symbol);
		return false;
	}
	return true;
}

/* {{{ string ibmi_xmlservice() */
PHP_FUNCTION(ibmi_xmlservice)
{
	char *input = NULL, *ctl = NULL, *ipc = NULL;
	size_t input_len, ctl_len, ipc_len;
	int ebcdic_ccsid = 0/*Qp2jobCCSID()*/, pase_ccsid = Qp2paseCCSID();

	ZEND_PARSE_PARAMETERS_START(1, 3)
		Z_PARAM_STRING(input, input_len)
		Z_PARAM_OPTIONAL
		Z_PARAM_STRING(ctl, ctl_len)
		Z_PARAM_STRING(ipc, ipc_len)
	ZEND_PARSE_PARAMETERS_END();

	/* XXX: Allow defaults to be set for these */
	if (ctl == NULL) {
		ctl = "";
	}
	if (ipc == NULL) {
		ipc = "";
	}

	if (should_initialize_ffi() && !initialize_ffi()) {
		RETURN_FALSE; /* throws? */
	}

	size_t output_len = 16 * 1024 * 1024;
	char *output = (char*)emalloc(output_len);
	if (!output) {
		RETURN_FALSE; /* throws? */
	}

	struct {
		ILEarglist_base base;
		ILEpointer ppIPCSP;
		ILEpointer szIPCSP;
		ILEpointer ppCtlSP;
		ILEpointer szCtlSP;
		ILEpointer ppIClob;
		ILEpointer szIClob;
		ILEpointer ppOClob;
		ILEpointer szOClob;
		ILEpointer ccsidPASE;
		ILEpointer ccsidILE;
	} arglist __attribute__ ((aligned (16)));

	ILEpointer IPCSP __attribute__ ((aligned (16)));
	ILEpointer CtlSP __attribute__ ((aligned (16)));
	ILEpointer IClob __attribute__ ((aligned (16)));
	ILEpointer OClob __attribute__ ((aligned (16)));
	_SETSPP(&IPCSP, ipc);
	_SETSPP(&CtlSP, ctl);
	_SETSPP(&IClob, input);
	_SETSPP(&OClob, output);
	arglist.ppIPCSP.s.addr   = (address64_t)(intptr_t) &IPCSP;
	arglist.szIPCSP.s.addr   = (address64_t)(intptr_t) &ipc_len;
	arglist.ppCtlSP.s.addr   = (address64_t)(intptr_t) &CtlSP;
	arglist.szCtlSP.s.addr   = (address64_t)(intptr_t) &ctl_len;
	arglist.ppIClob.s.addr   = (address64_t)(intptr_t) &IClob;
	arglist.szIClob.s.addr   = (address64_t)(intptr_t) &input_len;
	arglist.ppOClob.s.addr   = (address64_t)(intptr_t) &OClob;
	arglist.szOClob.s.addr   = (address64_t)(intptr_t) &output_len;
	arglist.ccsidPASE.s.addr = (address64_t)(intptr_t) &pase_ccsid;
	arglist.ccsidILE.s.addr  = (address64_t)(intptr_t) &ebcdic_ccsid;

	int rc = _ILECALL(&procedure, &arglist.base, signature, RESULT_UINT8);
fprintf(stderr, "!rc!%x!\n", rc, arglist.base.result.s_uint8.r_uint8);
	if (rc != ILECALL_NOERROR) {
		RETURN_FALSE;
	} else if (arglist.base.result.s_uint8.r_uint8 == 0xF0) {
		RETURN_FALSE;
	}

	RETURN_STRINGL(output, strlen(output));
}
/* }}} */
