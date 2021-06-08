--TEST--
if the CL commands run in the context of the process
--SKIPIF--
<?php
if (!extension_loaded('ibmi')) {
    echo 'skip';
}
?>
--FILE--
<?php

// while we normally use the normal ccsid functions, we'll see how the CL commands go
function print_ccsid_dspjob() {
	$cmd = "DSPJOB";
	// leading space to avoid capturing DFTCCSID. always spaces in a spool
	$regex = "/.* CCSID *([0-9]+).*/";
	$lines = [];
	ibmi_cl_exec($cmd, 0, $lines);
	foreach ($lines as $line) {
		$matches = [];
		if (preg_match($regex, $line, $matches)) {
			echo "Get CCSID " . $matches[1] . "\n";
		}
	}
}

function set_ccsid_chgjob($ccsid) {
	// vulnerable to injections. don't copy this for real code
	$cmd = "CHGJOB CCSID($ccsid)";
	// assume success
	ibmi_cl_exec($cmd);
	echo "Set CCSID $ccsid\n";
}

// we can't assume defaults
set_ccsid_chgjob(65535);
print_ccsid_dspjob();
set_ccsid_chgjob(37);
print_ccsid_dspjob();

?>
--EXPECT--
Set CCSID 65535
Get CCSID 65535
Set CCSID 37
Get CCSID 37
