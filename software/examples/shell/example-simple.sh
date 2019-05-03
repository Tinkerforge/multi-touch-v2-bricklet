#!/bin/sh
# Connects to localhost:4223 by default, use --host and --port to change this

uid=XYZ # Change XYZ to the UID of your Multi Touch Bricklet 2.0

# Get current touch state
tinkerforge call multi-touch-v2-bricklet $uid get-touch-state
