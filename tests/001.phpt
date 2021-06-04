--TEST--
Check if ibmi is loaded
--SKIPIF--
<?php
if (!extension_loaded('ibmi')) {
    echo 'skip';
}
?>
--FILE--
<?php
echo 'The extension "ibmi" is available';
?>
--EXPECT--
The extension "ibmi" is available
