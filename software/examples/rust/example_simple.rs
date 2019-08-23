use std::{error::Error, io};

use tinkerforge::{ip_connection::IpConnection, multi_touch_v2_bricklet::*};

const HOST: &str = "localhost";
const PORT: u16 = 4223;
const UID: &str = "XYZ"; // Change XYZ to the UID of your Multi Touch Bricklet 2.0.

fn main() -> Result<(), Box<dyn Error>> {
    let ipcon = IpConnection::new(); // Create IP connection.
    let mt = MultiTouchV2Bricklet::new(UID, &ipcon); // Create device object.

    ipcon.connect((HOST, PORT)).recv()??; // Connect to brickd.
                                          // Don't use device before ipcon is connected.

    // Get current touch state.
    let state = mt.get_touch_state().recv()?;

    println!("Electrode 0: {}", state[0]);
    println!("Electrode 1: {}", state[1]);
    println!("Electrode 2: {}", state[2]);
    println!("Electrode 3: {}", state[3]);
    println!("Electrode 4: {}", state[4]);
    println!("Electrode 5: {}", state[5]);
    println!("Electrode 6: {}", state[6]);
    println!("Electrode 7: {}", state[7]);
    println!("Electrode 8: {}", state[8]);
    println!("Electrode 9: {}", state[9]);
    println!("Electrode 10: {}", state[10]);
    println!("Electrode 11: {}", state[11]);
    println!("Proximity: {}", state[12]);

    println!("Press enter to exit.");
    let mut _input = String::new();
    io::stdin().read_line(&mut _input)?;
    ipcon.disconnect();
    Ok(())
}
