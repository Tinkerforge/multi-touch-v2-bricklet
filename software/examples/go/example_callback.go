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

	mt.RegisterTouchStateCallback(func(state [13]bool) {
		fmt.Printf("Electrode 0: %s\n", state[0])
		fmt.Printf("Electrode 1: %s\n", state[1])
		fmt.Printf("Electrode 2: %s\n", state[2])
		fmt.Printf("Electrode 3: %s\n", state[3])
		fmt.Printf("Electrode 4: %s\n", state[4])
		fmt.Printf("Electrode 5: %s\n", state[5])
		fmt.Printf("Electrode 6: %s\n", state[6])
		fmt.Printf("Electrode 7: %s\n", state[7])
		fmt.Printf("Electrode 8: %s\n", state[8])
		fmt.Printf("Electrode 9: %s\n", state[9])
		fmt.Printf("Electrode 10: %s\n", state[10])
		fmt.Printf("Electrode 11: %s\n", state[11])
		fmt.Printf("Proximity: %s\n", state[12])
		fmt.Println()
	})

	// Set period for touch state callback to 0.01s (10ms).
	mt.SetTouchStateCallbackConfiguration(10, true)

	fmt.Print("Press enter to exit.")
	fmt.Scanln()
}
