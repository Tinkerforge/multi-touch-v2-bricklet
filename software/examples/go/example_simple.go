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
	fmt.Printf("Touch State: \n", state)

	fmt.Print("Press enter to exit.")
	fmt.Scanln()
}
