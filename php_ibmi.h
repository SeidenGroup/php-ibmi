/* ibmi extension for PHP (c) 2021 Calvin Buckley */

#ifndef PHP_IBMI_H
# define PHP_IBMI_H

extern zend_module_entry ibmi_module_entry;
# define phpext_ibmi_ptr &ibmi_module_entry

# define PHP_IBMI_VERSION "0.1.0"

# if defined(ZTS) && defined(COMPILE_DL_IBMI)
ZEND_TSRMLS_CACHE_EXTERN()
# endif

#endif	/* PHP_IBMI_H */
