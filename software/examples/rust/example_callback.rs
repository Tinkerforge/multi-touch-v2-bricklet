use std::{error::Error, io, thread};
use tinkerforge::{ip_connection::IpConnection, multi_touch_v2_bricklet::*};

const HOST: &str = "localhost";
const PORT: u16 = 4223;
const UID: &str = "XYZ"; // Change XYZ to the UID of your Multi Touch Bricklet 2.0.

fn main() -> Result<(), Box<dyn Error>> {
    let ipcon = IpConnection::new(); // Create IP connection.
    let mt = MultiTouchV2Bricklet::new(UID, &ipcon); // Create device object.

    ipcon.connect((HOST, PORT)).recv()??; // Connect to brickd.
                                          // Don't use device before ipcon is connected.

    let touch_state_receiver = mt.get_touch_state_callback_receiver();

    // Spawn thread to handle received callback messages.
    // This thread ends when the `mt` object
    // is dropped, so there is no need for manual cleanup.
    thread::spawn(move || {
        for touch_state in touch_state_receiver {
            println!("Electrode 0: {}", touch_state[0]);
            println!("Electrode 1: {}", touch_state[1]);
            println!("Electrode 2: {}", touch_state[2]);
            println!("Electrode 3: {}", touch_state[3]);
            println!("Electrode 4: {}", touch_state[4]);
            println!("Electrode 5: {}", touch_state[5]);
            println!("Electrode 6: {}", touch_state[6]);
            println!("Electrode 7: {}", touch_state[7]);
            println!("Electrode 8: {}", touch_state[8]);
            println!("Electrode 9: {}", touch_state[9]);
            println!("Electrode 10: {}", touch_state[10]);
            println!("Electrode 11: {}", touch_state[11]);
            println!("Proximity: {}", touch_state[12]);
            println!();
        }
    });

    // Set period for touch state callback to 0.01s (10ms).
    mt.set_touch_state_callback_configuration(10, true);

    println!("Press enter to exit.");
    let mut _input = String::new();
    io::stdin().read_line(&mut _input)?;
    ipcon.disconnect();
    Ok(())
}
