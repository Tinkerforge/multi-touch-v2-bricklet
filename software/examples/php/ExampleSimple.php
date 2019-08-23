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

echo "Electrode 0: " . $state[0] . "\n";
echo "Electrode 1: " . $state[1] . "\n";
echo "Electrode 2: " . $state[2] . "\n";
echo "Electrode 3: " . $state[3] . "\n";
echo "Electrode 4: " . $state[4] . "\n";
echo "Electrode 5: " . $state[5] . "\n";
echo "Electrode 6: " . $state[6] . "\n";
echo "Electrode 7: " . $state[7] . "\n";
echo "Electrode 8: " . $state[8] . "\n";
echo "Electrode 9: " . $state[9] . "\n";
echo "Electrode 10: " . $state[10] . "\n";
echo "Electrode 11: " . $state[11] . "\n";
echo "Proximity: " . $state[12] . "\n";

echo "Press key to exit\n";
fgetc(fopen('php://stdin', 'r'));
$ipcon->disconnect();

?>
