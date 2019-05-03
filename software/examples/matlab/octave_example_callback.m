function octave_example_callback()
    more off;

    HOST = "localhost";
    PORT = 4223;
    UID = "XYZ"; % Change XYZ to the UID of your Multi Touch Bricklet 2.0

    ipcon = javaObject("com.tinkerforge.IPConnection"); % Create IP connection
    mt = javaObject("com.tinkerforge.BrickletMultiTouchV2", UID, ipcon); % Create device object

    ipcon.connect(HOST, PORT); % Connect to brickd
    % Don't use device before ipcon is connected

    % Register touch state callback to function cb_touch_state
    mt.addTouchStateCallback(@cb_touch_state);

    % Set period for touch state callback to 0.01s (10ms)
    mt.setTouchStateCallbackConfiguration(10, true);

    input("Press key to exit\n", "s");
    ipcon.disconnect();
end

% Callback function for touch state callback
function cb_touch_state(e)
    fprintf("Touch State: %d\n", e.state);
end
