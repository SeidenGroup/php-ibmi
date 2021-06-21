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

/* {{{ PHP_RINIT_FUNCTION */
PHP_RINIT_FUNCTION(ibmi)
{
#if defined(ZTS) && defined(COMPILE_DL_IBMI)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif

	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINIT_FUNCTION */
PHP_MINIT_FUNCTION(ibmi)
{
	/* no ini or global entries to init */

	/* systemcl.c */
	/* XXX: Convert to header */
	REGISTER_LONG_CONSTANT("IBMI_CL_EBCDIC_OUTPUT", IBMI_CL_EBCDIC_OUTPUT, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("IBMI_CL_SPAWN", IBMI_CL_SPAWN, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("IBMI_CL_NO_MESSAGES", IBMI_CL_NO_MESSAGES, CONST_CS | CONST_PERSISTENT);

	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION */
PHP_MINFO_FUNCTION(ibmi)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "ibmi support", "enabled");
	php_info_print_table_end();
}
/* }}} */

/* {{{ ibmi_module_entry */
zend_module_entry ibmi_module_entry = {
	STANDARD_MODULE_HEADER,
	"ibmi",					/* Extension name */
	ext_functions,					/* zend_function_entry */
	PHP_MINIT(ibmi),							/* PHP_MINIT - Module initialization */
	NULL,							/* PHP_MSHUTDOWN - Module shutdown */
	PHP_RINIT(ibmi),			/* PHP_RINIT - Request initialization */
	NULL,							/* PHP_RSHUTDOWN - Request shutdown */
	PHP_MINFO(ibmi),			/* PHP_MINFO - Module info */
	PHP_IBMI_VERSION,		/* Version */
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_IBMI
# ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
# endif
ZEND_GET_MODULE(ibmi)
#endif
