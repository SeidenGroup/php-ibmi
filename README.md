# IBM i extension for PHP

This extension allows PHP programs to access IBM i specific facilities, such as:

* Run CL scripts directly, and get their output, using similar interfaces that
  already exist for `system`, `exec`, and `passthru`
  * This allows running CL scripts *in the context of the process*; for example,
    `CHGJOB` will actually apply to the current job.
* Get the current job and PASE CCSID, get the CCSID of files

While some of this was possible before, it required workarounds like calling into
QSH or the FFI extension (which may be restricted). Some of it wasn't even
possible at all.

## Documentation

### CCSID functions

#### `int ibmi_get_pase_ccsid()`

Returns the current ASCII/PASE CCSID for the job.

#### `int ibmi_get_job_ccsid()`

Returns the current EBCDIC/job CCSID.

### File functions

#### `array|false ibmi_stat(string $filename)`

Returns an array with entries `codepage`, `ccsid`, and `objtype`.
Their values are equal to the `st_objtype`, `st_codepage`, and `st_ccsid`
values returned by ILE [stat](https://www.ibm.com/docs/en/i/7.1?topic=ssw_ibm_i_71/apis/stat.htm).

Similar to the PHP function [stat](https://www.php.net/manual/en/function.stat.php).

### CL commands

These execute CL commands in the context of the job.

The command is run with the PASE function [systemCL](https://www.ibm.com/docs/en/i/7.2?topic=ssw_ibm_i_72/apis/pase_systemcl.htm).
The output is captured and read out in a separate file descriptor.

Flags that can be given to change behaviour are:

* `IBMI_CL_SPAWN`: A new job is spawned for the CL.
* `IBMI_CL_NO_MESSAGES`: Skip printing out IBM i messages i.e. "CPF0000".
* `IBMI_CL_EBCDIC_OUTPUT`: Do not convert output from EBCDIC (assumed) to ASCII/Unicode.

#### `string|false ibmi_cl_system(string $command, int $flags = 0)`

Executes and prints output to stdout, while returning the last line as a string.

Equivalent to the PHP function [system](https://www.php.net/manual/en/function.system.php).

#### `?bool ibmi_cl_passthru(string $command, int $flags = 0)`

Executes and prints output to stdout.

Equivalent to the PHP function [passthru](https://www.php.net/manual/en/function.passthru.php).

#### `string|false ibmi_cl_exec(string $command, int $flags = 0, array &$output = null)`

Executes and returns the last line as a string.

If `$output` is set, the array will be filled with each line of the output.

Equivalent to the PHP function [exec](https://www.php.net/manual/en/function.exec.php).

## Licensing

Please see `LICENSE`; this extension uses code from PHP and thus is kept under
the same license. Some files may be licensed under different, compatible
licenses; this will be marked in the header.

## Requirements

* PHP 7.3 or newer
* IBM i 7.2 or newer

## Building

There are no additional build options.

```sh
phpize --clean
phpize
# You may need to specify the build manually because autotools doesn't recognzie os400
./configure --prefix=$PREFIX --build=powerpc-ibm-aix
# libtool may only generate an .a file in modules, so force .so
make && cp .libs/ibmi.so modules/
make install
```

## Future plans

It would be useful to integrate other IBM i extensions, particularly those that
do upcalls; such as the ones for authentication and XMLSERVICE fast paths. Such
fast paths could benefit the Toolkit, in particular, if it provides enough of a
performance benefit.

Perhaps generic IBM i FFI could be considered, but this is a bit of a risk.
It would have to be disabled by default.
