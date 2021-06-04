--TEST--
test1() Basic test
--SKIPIF--
<?php
if (!extension_loaded('ibmi')) {
    echo 'skip';
}
?>
--FILE--
<?php
$ret = test1();

var_dump($ret);
?>
--EXPECT--
The extension ibmi is loaded and working!
NULL
