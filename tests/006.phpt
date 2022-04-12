--TEST--
IBM i XMLSERVICE
--SKIPIF--
<?php
if (!extension_loaded('ibmi')) {
    echo 'skip';
}
?>
--FILE--
<?php

$input = <<<EOF
<?xml version="1.0" encoding="ISO-8859-1" ?>
<script>
<sh>system dsplibl</sh>
</script>
EOF;

$output = ibmi_xmlservice($input, "*here");
var_dump($output);

?>
--EXPECTF--
