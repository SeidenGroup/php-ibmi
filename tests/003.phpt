--TEST--
ways to run CL commands
--SKIPIF--
<?php
if (!extension_loaded('ibmi')) {
    echo 'skip';
}
?>
--FILE--
<?php

$cmd = "QSH CMD('uname')";
// passthu just executes and displays to stdout
ibmi_cl_passthru($cmd, IBMI_CL_SPAWN);
// system executes and displays to stdout, and puts last line in ret
$last_line = ibmi_cl_system($cmd, IBMI_CL_NO_MESSAGES);
echo ($last_line == "OS400" ? "Yes" : "No") . "\n";
// exec will return stdout to a string. we'll just hope for the best with EBCDIC
// note that the message output is always in ASCII
$output = ibmi_cl_exec($cmd, IBMI_CL_EBCDIC_OUTPUT);
var_dump($output)

?>
--EXPECTF--
OS400
QSH0005: %s
OS400
Yes
string(%d) "%s"
