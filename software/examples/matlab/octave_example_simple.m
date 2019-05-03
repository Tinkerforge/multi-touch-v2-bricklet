function octave_example_simple()
    more off;

    HOST = "localhost";
    PORT = 4223;
    UID = "XYZ"; % Change XYZ to the UID of your Multi Touch Bricklet 2.0

    ipcon = javaObject("com.tinkerforge.IPConnection"); % Create IP connection
    mt = javaObject("com.tinkerforge.BrickletMultiTouchV2", UID, ipcon); % Create device object

    ipcon.connect(HOST, PORT); % Connect to brickd
    % Don't use device before ipcon is connected

    % Get current touch state
    state = mt.getTouchState();
    fprintf("Touch State: %d\n", state);

    input("Press key to exit\n", "s");
    ipcon.disconnect();
end
