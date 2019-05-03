#!/bin/sh
# Connects to localhost:4223 by default, use --host and --port to change this

uid=XYZ # Change XYZ to the UID of your Multi Touch Bricklet 2.0

# Handle incoming touch state callbacks
tinkerforge dispatch multi-touch-v2-bricklet $uid touch-state &

# Set period for touch state callback to 0.01s (10ms)
tinkerforge call multi-touch-v2-bricklet $uid set-touch-state-callback-configuration 10 true

echo "Press key to exit"; read dummy

kill -- -$$ # Stop callback dispatch in background
