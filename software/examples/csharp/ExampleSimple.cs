using System;
using Tinkerforge;

class Example
{
	private static string HOST = "localhost";
	private static int PORT = 4223;
	private static string UID = "XYZ"; // Change XYZ to the UID of your Multi Touch Bricklet 2.0

	static void Main()
	{
		IPConnection ipcon = new IPConnection(); // Create IP connection
		BrickletMultiTouchV2 mt = new BrickletMultiTouchV2(UID, ipcon); // Create device object

		ipcon.Connect(HOST, PORT); // Connect to brickd
		// Don't use device before ipcon is connected

		// Get current touch state
		bool[] state = mt.GetTouchState();

		Console.WriteLine("Electrode 0: " + state[0]);
		Console.WriteLine("Electrode 1: " + state[1]);
		Console.WriteLine("Electrode 2: " + state[2]);
		Console.WriteLine("Electrode 3: " + state[3]);
		Console.WriteLine("Electrode 4: " + state[4]);
		Console.WriteLine("Electrode 5: " + state[5]);
		Console.WriteLine("Electrode 6: " + state[6]);
		Console.WriteLine("Electrode 7: " + state[7]);
		Console.WriteLine("Electrode 8: " + state[8]);
		Console.WriteLine("Electrode 9: " + state[9]);
		Console.WriteLine("Electrode 10: " + state[10]);
		Console.WriteLine("Electrode 11: " + state[11]);
		Console.WriteLine("Proximity: " + state[12]);

		Console.WriteLine("Press enter to exit");
		Console.ReadLine();
		ipcon.Disconnect();
	}
}
