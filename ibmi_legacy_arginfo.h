/* This is a generated file, edit the .stub.php file instead.
 * Stub hash: 19f1c7c37da92970418b05551ced7b65a5e302cd */

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

ZEND_BEGIN_ARG_INFO_EX(arginfo_ibmi_stat, 0, 0, 1)
	ZEND_ARG_INFO(0, filename)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_ibmi_xmlservice, 0, 0, 1)
	ZEND_ARG_INFO(0, input)
	ZEND_ARG_INFO(0, ctl)
	ZEND_ARG_INFO(0, ipc)
ZEND_END_ARG_INFO()


ZEND_FUNCTION(ibmi_get_job_ccsid);
ZEND_FUNCTION(ibmi_get_pase_ccsid);
ZEND_FUNCTION(ibmi_cl_exec);
ZEND_FUNCTION(ibmi_cl_system);
ZEND_FUNCTION(ibmi_cl_passthru);
ZEND_FUNCTION(ibmi_stat);
ZEND_FUNCTION(ibmi_xmlservice);


static const zend_function_entry ext_functions[] = {
	ZEND_FE(ibmi_get_job_ccsid, arginfo_ibmi_get_job_ccsid)
	ZEND_FE(ibmi_get_pase_ccsid, arginfo_ibmi_get_pase_ccsid)
	ZEND_FE(ibmi_cl_exec, arginfo_ibmi_cl_exec)
	ZEND_FE(ibmi_cl_system, arginfo_ibmi_cl_system)
	ZEND_FE(ibmi_cl_passthru, arginfo_ibmi_cl_passthru)
	ZEND_FE(ibmi_stat, arginfo_ibmi_stat)
	ZEND_FE(ibmi_xmlservice, arginfo_ibmi_xmlservice)
	ZEND_FE_END
};
