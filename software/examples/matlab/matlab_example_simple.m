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
    fprintf('Touch State: %i\n', state);

    input('Press key to exit\n', 's');
    ipcon.disconnect();
end
