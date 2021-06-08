/* ibmi extension for PHP (c) 2021 Calvin Buckley */
#include "php_ibmi_int.h"

#include <as400_protos.h>

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
