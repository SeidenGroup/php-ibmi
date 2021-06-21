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
