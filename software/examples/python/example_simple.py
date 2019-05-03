#!/usr/bin/env python
# -*- coding: utf-8 -*-

HOST = "localhost"
PORT = 4223
UID = "XYZ" # Change XYZ to the UID of your Multi Touch Bricklet 2.0

from tinkerforge.ip_connection import IPConnection
from tinkerforge.bricklet_multi_touch_v2 import BrickletMultiTouchV2

if __name__ == "__main__":
    ipcon = IPConnection() # Create IP connection
    mt = BrickletMultiTouchV2(UID, ipcon) # Create device object

    ipcon.connect(HOST, PORT) # Connect to brickd
    # Don't use device before ipcon is connected

    # Get current touch state
    state = mt.get_touch_state()
    print("Touch State: " + str(state))

    raw_input("Press key to exit\n") # Use input() in Python 3
    ipcon.disconnect()
