<?php

require_once('Tinkerforge/IPConnection.php');
require_once('Tinkerforge/BrickletMultiTouchV2.php');

use Tinkerforge\IPConnection;
use Tinkerforge\BrickletMultiTouchV2;

const HOST = 'localhost';
const PORT = 4223;
const UID = 'XYZ'; // Change XYZ to the UID of your Multi Touch Bricklet 2.0

$ipcon = new IPConnection(); // Create IP connection
$mt = new BrickletMultiTouchV2(UID, $ipcon); // Create device object

$ipcon->connect(HOST, PORT); // Connect to brickd
// Don't use device before ipcon is connected

// Get current touch state
$state = $mt->getTouchState();
echo "Touch State: $state\n";

echo "Press key to exit\n";
fgetc(fopen('php://stdin', 'r'));
$ipcon->disconnect();

?>
