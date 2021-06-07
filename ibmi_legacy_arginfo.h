/* This is a generated file, edit the .stub.php file instead.
 * Stub hash: ddd21b8f698ca97641d4caf66dc37b447d6d68e9 */

ZEND_BEGIN_ARG_INFO_EX(arginfo_ibmi_get_job_ccsid, 0, 0, 0)
ZEND_END_ARG_INFO()

#define arginfo_ibmi_get_pase_ccsid arginfo_ibmi_get_job_ccsid

ZEND_BEGIN_ARG_INFO_EX(arginfo_ibmi_cl_exec, 0, 0, 1)
	ZEND_ARG_INFO(0, command)
	ZEND_ARG_INFO(0, flags)
	ZEND_ARG_INFO(1, output)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_ibmi_cl_system, 0, 0, 1)
	ZEND_ARG_INFO(0, command)
	ZEND_ARG_INFO(0, flags)
ZEND_END_ARG_INFO()

#define arginfo_ibmi_cl_passthru arginfo_ibmi_cl_system


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
