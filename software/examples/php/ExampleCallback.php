<?php

require_once('Tinkerforge/IPConnection.php');
require_once('Tinkerforge/BrickletMultiTouchV2.php');

use Tinkerforge\IPConnection;
use Tinkerforge\BrickletMultiTouchV2;

const HOST = 'localhost';
const PORT = 4223;
const UID = 'XYZ'; // Change XYZ to the UID of your Multi Touch Bricklet 2.0

// Callback function for touch state callback
function cb_touchState($state)
{
    echo "Touch State: $state\n";
}

$ipcon = new IPConnection(); // Create IP connection
$mt = new BrickletMultiTouchV2(UID, $ipcon); // Create device object

$ipcon->connect(HOST, PORT); // Connect to brickd
// Don't use device before ipcon is connected

// Register touch state callback to function cb_touchState
$mt->registerCallback(BrickletMultiTouchV2::CALLBACK_TOUCH_STATE, 'cb_touchState');

// Set period for touch state callback to 0.01s (10ms)
$mt->setTouchStateCallbackConfiguration(10, TRUE);

echo "Press ctrl+c to exit\n";
$ipcon->dispatchCallbacks(-1); // Dispatch callbacks forever

?>
