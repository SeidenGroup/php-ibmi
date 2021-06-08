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

/* Enum definitions */
typedef enum _PhpSystemClFlags {
	IBMI_CL_EBCDIC_OUTPUT = 0x1,
	IBMI_CL_SPAWN = 0x2,
	IBMI_CL_NO_MESSAGES = 0x4,
} PhpSystemClFlags;
