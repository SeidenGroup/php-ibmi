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
