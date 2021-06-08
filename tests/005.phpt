--TEST--
IBM i stat extensions
--SKIPIF--
<?php
if (!extension_loaded('ibmi')) {
    echo 'skip';
}
?>
--FILE--
<?php

$stat = ibmi_stat(__FILE__);
// Codepage/CCSID will be unpredictable, but I hope a normal file is still a
// stream file (*STMF)
echo "Codepage " . $stat["codepage"] . "\n";
echo "Object type " . $stat["objtype"] . "\n";
echo "CCSID " . $stat["ccsid"] . "\n";

?>
--EXPECTF--
Codepage %d
Object type *STMF
CCSID %d
