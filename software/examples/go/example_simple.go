package main

import (
	"fmt"
	"github.com/Tinkerforge/go-api-bindings/ipconnection"
	"github.com/Tinkerforge/go-api-bindings/multi_touch_v2_bricklet"
)

const ADDR string = "localhost:4223"
const UID string = "XYZ" // Change XYZ to the UID of your Multi Touch Bricklet 2.0.

func main() {
	ipcon := ipconnection.New()
	defer ipcon.Close()
	mt, _ := multi_touch_v2_bricklet.New(UID, &ipcon) // Create device object.

	ipcon.Connect(ADDR) // Connect to brickd.
	defer ipcon.Disconnect()
	// Don't use device before ipcon is connected.

	// Get current touch state.
	state, _ := mt.GetTouchState()

	fmt.Printf("Electrode 0: \n", state[0])
	fmt.Printf("Electrode 1: \n", state[1])
	fmt.Printf("Electrode 2: \n", state[2])
	fmt.Printf("Electrode 3: \n", state[3])
	fmt.Printf("Electrode 4: \n", state[4])
	fmt.Printf("Electrode 5: \n", state[5])
	fmt.Printf("Electrode 6: \n", state[6])
	fmt.Printf("Electrode 7: \n", state[7])
	fmt.Printf("Electrode 8: \n", state[8])
	fmt.Printf("Electrode 9: \n", state[9])
	fmt.Printf("Electrode 10: \n", state[10])
	fmt.Printf("Electrode 11: \n", state[11])
	fmt.Printf("Proximity: \n", state[12])

	fmt.Print("Press enter to exit.")
	fmt.Scanln()
}
