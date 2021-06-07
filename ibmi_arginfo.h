/* This is a generated file, edit the .stub.php file instead.
 * Stub hash: ddd21b8f698ca97641d4caf66dc37b447d6d68e9 */

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_ibmi_get_job_ccsid, 0, 0, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_ibmi_get_pase_ccsid arginfo_ibmi_get_job_ccsid

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_MASK_EX(arginfo_ibmi_cl_exec, 0, 1, MAY_BE_STRING|MAY_BE_FALSE)
	ZEND_ARG_TYPE_INFO(0, command, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, flags, IS_LONG, 0, "-1")
	ZEND_ARG_INFO_WITH_DEFAULT_VALUE(1, output, "null")
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_MASK_EX(arginfo_ibmi_cl_system, 0, 1, MAY_BE_STRING|MAY_BE_FALSE)
	ZEND_ARG_TYPE_INFO(0, command, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, flags, IS_LONG, 0, "0")
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_ibmi_cl_passthru, 0, 1, _IS_BOOL, 1)
	ZEND_ARG_TYPE_INFO(0, command, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, flags, IS_LONG, 0, "0")
ZEND_END_ARG_INFO()


ZEND_FUNCTION(ibmi_get_job_ccsid);
ZEND_FUNCTION(ibmi_get_pase_ccsid);
ZEND_FUNCTION(ibmi_cl_exec);
ZEND_FUNCTION(ibmi_cl_system);
ZEND_FUNCTION(ibmi_cl_passthru);


static const zend_function_entry ext_functions[] = {
	ZEND_FE(ibmi_get_job_ccsid, arginfo_ibmi_get_job_ccsid)
	ZEND_FE(ibmi_get_pase_ccsid, arginfo_ibmi_get_pase_ccsid)
	ZEND_FE(ibmi_cl_exec, arginfo_ibmi_cl_exec)
	ZEND_FE(ibmi_cl_system, arginfo_ibmi_cl_system)
	ZEND_FE(ibmi_cl_passthru, arginfo_ibmi_cl_passthru)
	ZEND_FE_END
};
