import com.tinkerforge.IPConnection;
import com.tinkerforge.BrickletMultiTouchV2;

public class ExampleSimple {
	private static final String HOST = "localhost";
	private static final int PORT = 4223;

	// Change XYZ to the UID of your Multi Touch Bricklet 2.0
	private static final String UID = "XYZ";

	// Note: To make the example code cleaner we do not handle exceptions. Exceptions
	//       you might normally want to catch are described in the documentation
	public static void main(String args[]) throws Exception {
		IPConnection ipcon = new IPConnection(); // Create IP connection
		BrickletMultiTouchV2 mt = new BrickletMultiTouchV2(UID, ipcon); // Create device object

		ipcon.connect(HOST, PORT); // Connect to brickd
		// Don't use device before ipcon is connected

		// Get current touch state
		boolean[] state = mt.getTouchState(); // Can throw com.tinkerforge.TimeoutException

		System.out.println("Electrode 0: " + state[0]);
		System.out.println("Electrode 1: " + state[1]);
		System.out.println("Electrode 2: " + state[2]);
		System.out.println("Electrode 3: " + state[3]);
		System.out.println("Electrode 4: " + state[4]);
		System.out.println("Electrode 5: " + state[5]);
		System.out.println("Electrode 6: " + state[6]);
		System.out.println("Electrode 7: " + state[7]);
		System.out.println("Electrode 8: " + state[8]);
		System.out.println("Electrode 9: " + state[9]);
		System.out.println("Electrode 10: " + state[10]);
		System.out.println("Electrode 11: " + state[11]);
		System.out.println("Proximity: " + state[12]);

		System.out.println("Press key to exit"); System.in.read();
		ipcon.disconnect();
	}
}
