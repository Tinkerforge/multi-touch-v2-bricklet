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

    fprintf("Electrode 0: %d\n", state(1));
    fprintf("Electrode 1: %d\n", state(2));
    fprintf("Electrode 2: %d\n", state(3));
    fprintf("Electrode 3: %d\n", state(4));
    fprintf("Electrode 4: %d\n", state(5));
    fprintf("Electrode 5: %d\n", state(6));
    fprintf("Electrode 6: %d\n", state(7));
    fprintf("Electrode 7: %d\n", state(8));
    fprintf("Electrode 8: %d\n", state(9));
    fprintf("Electrode 9: %d\n", state(10));
    fprintf("Electrode 10: %d\n", state(11));
    fprintf("Electrode 11: %d\n", state(12));
    fprintf("Proximity: %d\n", state(13));

    input("Press key to exit\n", "s");
    ipcon.disconnect();
end
