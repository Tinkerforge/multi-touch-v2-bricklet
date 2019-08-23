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
    fprintf("Electrode 0: %d\n", e.state(1));
    fprintf("Electrode 1: %d\n", e.state(2));
    fprintf("Electrode 2: %d\n", e.state(3));
    fprintf("Electrode 3: %d\n", e.state(4));
    fprintf("Electrode 4: %d\n", e.state(5));
    fprintf("Electrode 5: %d\n", e.state(6));
    fprintf("Electrode 6: %d\n", e.state(7));
    fprintf("Electrode 7: %d\n", e.state(8));
    fprintf("Electrode 8: %d\n", e.state(9));
    fprintf("Electrode 9: %d\n", e.state(10));
    fprintf("Electrode 10: %d\n", e.state(11));
    fprintf("Electrode 11: %d\n", e.state(12));
    fprintf("Proximity: %d\n", e.state(13));
    fprintf("\n");
end
