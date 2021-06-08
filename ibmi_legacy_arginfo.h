/* This is a generated file, edit the .stub.php file instead.
 * Stub hash: afa127565cdaa6295fa17df4251e1230962b9a9f */

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
