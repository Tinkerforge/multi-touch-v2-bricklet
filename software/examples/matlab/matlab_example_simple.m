function matlab_example_simple()
    import com.tinkerforge.IPConnection;
    import com.tinkerforge.BrickletMultiTouchV2;

    HOST = 'localhost';
    PORT = 4223;
    UID = 'XYZ'; % Change XYZ to the UID of your Multi Touch Bricklet 2.0

    ipcon = IPConnection(); % Create IP connection
    mt = handle(BrickletMultiTouchV2(UID, ipcon), 'CallbackProperties'); % Create device object

    ipcon.connect(HOST, PORT); % Connect to brickd
    % Don't use device before ipcon is connected

    % Get current touch state
    state = mt.getTouchState();

    fprintf('Electrode 0: %i\n', state(1));
    fprintf('Electrode 1: %i\n', state(2));
    fprintf('Electrode 2: %i\n', state(3));
    fprintf('Electrode 3: %i\n', state(4));
    fprintf('Electrode 4: %i\n', state(5));
    fprintf('Electrode 5: %i\n', state(6));
    fprintf('Electrode 6: %i\n', state(7));
    fprintf('Electrode 7: %i\n', state(8));
    fprintf('Electrode 8: %i\n', state(9));
    fprintf('Electrode 9: %i\n', state(10));
    fprintf('Electrode 10: %i\n', state(11));
    fprintf('Electrode 11: %i\n', state(12));
    fprintf('Proximity: %i\n', state(13));

    input('Press key to exit\n', 's');
    ipcon.disconnect();
end
