var Tinkerforge = require('tinkerforge');

var HOST = 'localhost';
var PORT = 4223;
var UID = 'XYZ'; // Change XYZ to the UID of your Multi Touch Bricklet 2.0

var ipcon = new Tinkerforge.IPConnection(); // Create IP connection
var mt = new Tinkerforge.BrickletMultiTouchV2(UID, ipcon); // Create device object

ipcon.connect(HOST, PORT,
    function (error) {
        console.log('Error: ' + error);
    }
); // Connect to brickd
// Don't use device before ipcon is connected

ipcon.on(Tinkerforge.IPConnection.CALLBACK_CONNECTED,
    function (connectReason) {
        // Set period for touch state callback to 0.01s (10ms)
        mt.setTouchStateCallbackConfiguration(10, true);
    }
);

// Register touch state callback
mt.on(Tinkerforge.BrickletMultiTouchV2.CALLBACK_TOUCH_STATE,
    // Callback function for touch state callback
    function (state) {
        console.log('Electrode 0: ' + state[0]);
        console.log('Electrode 1: ' + state[1]);
        console.log('Electrode 2: ' + state[2]);
        console.log('Electrode 3: ' + state[3]);
        console.log('Electrode 4: ' + state[4]);
        console.log('Electrode 5: ' + state[5]);
        console.log('Electrode 6: ' + state[6]);
        console.log('Electrode 7: ' + state[7]);
        console.log('Electrode 8: ' + state[8]);
        console.log('Electrode 9: ' + state[9]);
        console.log('Electrode 10: ' + state[10]);
        console.log('Electrode 11: ' + state[11]);
        console.log('Proximity: ' + state[12]);
        console.log();
    }
);

console.log('Press key to exit');
process.stdin.on('data',
    function (data) {
        ipcon.disconnect();
        process.exit(0);
    }
);
