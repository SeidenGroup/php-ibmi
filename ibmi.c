/* ibmi extension for PHP (c) 2021 Calvin Buckley */

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "php.h"
#include "ext/standard/info.h"
#include "php_ibmi.h"
#if PHP_MAJOR_VERSION >= 8
#include "ibmi_arginfo.h"
#else
#include "ibmi_legacy_arginfo.h"
#endif

/* {{{ PHP_RINIT_FUNCTION */
PHP_RINIT_FUNCTION(ibmi)
{
#if defined(ZTS) && defined(COMPILE_DL_IBMI)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif

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
	NULL,							/* PHP_MINIT - Module initialization */
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
