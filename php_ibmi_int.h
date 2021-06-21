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

/* Internal header for sharing imports, since php_ibmi.h can be public */
#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

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

#if PHP_MAJOR_VERSION < 8
/*
 * Not the right semantics (returns false instead of throws) but matches other
 * functions' behaviour in 7.x. The ##__VA_ARGS__ trick is an extension that's
 * supported in GNU C. Since things built for the RPM world in PASE use GCC,
 * this is no problem.
 */
#define zend_argument_value_error(arg, msg, ...) php_error_docref(NULL, E_WARNING, "Argument %d " msg, arg  ##__VA_ARGS__)
#endif

#ifndef RETURN_THROWS
#define RETURN_THROWS() RETURN_FALSE
#endif

/* Enum definitions */
typedef enum _PhpSystemClFlags {
	IBMI_CL_EBCDIC_OUTPUT = 0x1,
	IBMI_CL_SPAWN = 0x2,
	IBMI_CL_NO_MESSAGES = 0x4,
} PhpSystemClFlags;
