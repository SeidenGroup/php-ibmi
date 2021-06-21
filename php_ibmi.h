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

#ifndef PHP_IBMI_H
# define PHP_IBMI_H

extern zend_module_entry ibmi_module_entry;
# define phpext_ibmi_ptr &ibmi_module_entry

# define PHP_IBMI_VERSION "0.1.0"

# if defined(ZTS) && defined(COMPILE_DL_IBMI)
ZEND_TSRMLS_CACHE_EXTERN()
# endif

#endif	/* PHP_IBMI_H */
