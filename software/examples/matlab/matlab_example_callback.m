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
    fprintf('Electrode 0: %i\n', e.state(1));
    fprintf('Electrode 1: %i\n', e.state(2));
    fprintf('Electrode 2: %i\n', e.state(3));
    fprintf('Electrode 3: %i\n', e.state(4));
    fprintf('Electrode 4: %i\n', e.state(5));
    fprintf('Electrode 5: %i\n', e.state(6));
    fprintf('Electrode 6: %i\n', e.state(7));
    fprintf('Electrode 7: %i\n', e.state(8));
    fprintf('Electrode 8: %i\n', e.state(9));
    fprintf('Electrode 9: %i\n', e.state(10));
    fprintf('Electrode 10: %i\n', e.state(11));
    fprintf('Electrode 11: %i\n', e.state(12));
    fprintf('Proximity: %i\n', e.state(13));
    fprintf('\n');
end
