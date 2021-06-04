--TEST--
get job and PASE CCSID
--SKIPIF--
<?php
if (!extension_loaded('ibmi')) {
    echo 'skip';
}
?>
--FILE--
<?php

// Since this is locale dependent, just test if these are integers

$job = ibmi_get_job_ccsid(); // likely, but not always 37
$pase = ibmi_get_pase_ccsid(); // likely, but not always 437/819/1208

var_dump($job);
var_dump($pase);
?>
--EXPECTF--
int(%d)
int(%d)
