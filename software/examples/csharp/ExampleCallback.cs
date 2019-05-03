using System;
using Tinkerforge;

class Example
{
	private static string HOST = "localhost";
	private static int PORT = 4223;
	private static string UID = "XYZ"; // Change XYZ to the UID of your Multi Touch Bricklet 2.0

	// Callback function for touch state callback
	static void TouchStateCB(BrickletMultiTouchV2 sender, int state)
	{
		Console.WriteLine("Touch State: " + state);
	}

	static void Main()
	{
		IPConnection ipcon = new IPConnection(); // Create IP connection
		BrickletMultiTouchV2 mt = new BrickletMultiTouchV2(UID, ipcon); // Create device object

		ipcon.Connect(HOST, PORT); // Connect to brickd
		// Don't use device before ipcon is connected

		// Register touch state callback to function TouchStateCB
		mt.TouchStateCallback += TouchStateCB;

		// Set period for touch state callback to 0.01s (10ms)
		mt.SetTouchStateCallbackConfiguration(10, true);

		Console.WriteLine("Press enter to exit");
		Console.ReadLine();
		ipcon.Disconnect();
	}
}
