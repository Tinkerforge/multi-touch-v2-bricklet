function matlab_example_callback()
    import com.tinkerforge.IPConnection;
    import com.tinkerforge.BrickletMultiTouchV2;

    HOST = 'localhost';
    PORT = 4223;
    UID = 'XYZ'; % Change XYZ to the UID of your Multi Touch Bricklet 2.0

    ipcon = IPConnection(); % Create IP connection
    mt = handle(BrickletMultiTouchV2(UID, ipcon), 'CallbackProperties'); % Create device object

    ipcon.connect(HOST, PORT); % Connect to brickd
    % Don't use device before ipcon is connected

    % Register touch state callback to function cb_touch_state
    set(mt, 'TouchStateCallback', @(h, e) cb_touch_state(e));

    % Set period for touch state callback to 0.01s (10ms)
    mt.setTouchStateCallbackConfiguration(10, true);

    input('Press key to exit\n', 's');
    ipcon.disconnect();
end

% Callback function for touch state callback
function cb_touch_state(e)
    fprintf('Touch State: %i\n', e.state);
end
