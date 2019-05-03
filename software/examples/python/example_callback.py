#!/usr/bin/env python
# -*- coding: utf-8 -*-

HOST = "localhost"
PORT = 4223
UID = "XYZ" # Change XYZ to the UID of your Multi Touch Bricklet 2.0

from tinkerforge.ip_connection import IPConnection
from tinkerforge.bricklet_multi_touch_v2 import BrickletMultiTouchV2

# Callback function for touch state callback
def cb_touch_state(state):
    print("Touch State: " + str(state))

if __name__ == "__main__":
    ipcon = IPConnection() # Create IP connection
    mt = BrickletMultiTouchV2(UID, ipcon) # Create device object

    ipcon.connect(HOST, PORT) # Connect to brickd
    # Don't use device before ipcon is connected

    # Register touch state callback to function cb_touch_state
    mt.register_callback(mt.CALLBACK_TOUCH_STATE, cb_touch_state)

    # Set period for touch state callback to 0.01s (10ms)
    mt.set_touch_state_callback_configuration(10, True)

    raw_input("Press key to exit\n") # Use input() in Python 3
    ipcon.disconnect()
