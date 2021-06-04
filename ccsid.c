/* ibmi extension for PHP (c) 2021 Calvin Buckley */

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include <as400_protos.h>

#include "php.h"
#include "ext/standard/info.h"
#include "php_ibmi.h"
#include "ibmi_arginfo.h"

/* For compatibility with older PHP versions */
#ifndef ZEND_PARSE_PARAMETERS_NONE
#define ZEND_PARSE_PARAMETERS_NONE() \
	ZEND_PARSE_PARAMETERS_START(0, 0) \
	ZEND_PARSE_PARAMETERS_END()
#endif

/* {{{ int ibmi_get_pase_ccsid() */
PHP_FUNCTION(ibmi_get_pase_ccsid)
{
	ZEND_PARSE_PARAMETERS_NONE();

	RETURN_LONG(Qp2paseCCSID());
}
/* }}} */

/* {{{ int ibmi_get_job_ccsid() */
PHP_FUNCTION(ibmi_get_job_ccsid)
{
	ZEND_PARSE_PARAMETERS_NONE();

	RETURN_LONG(Qp2jobCCSID());
}
/* }}} */
