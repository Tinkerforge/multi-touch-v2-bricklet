#!/usr/bin/env ruby
# -*- ruby encoding: utf-8 -*-

require 'tinkerforge/ip_connection'
require 'tinkerforge/bricklet_multi_touch_v2'

include Tinkerforge

HOST = 'localhost'
PORT = 4223
UID = 'XYZ' # Change XYZ to the UID of your Multi Touch Bricklet 2.0

ipcon = IPConnection.new # Create IP connection
mt = BrickletMultiTouchV2.new UID, ipcon # Create device object

ipcon.connect HOST, PORT # Connect to brickd
# Don't use device before ipcon is connected

# Register touch state callback
mt.register_callback(BrickletMultiTouchV2::CALLBACK_TOUCH_STATE) do |state|
  puts "Touch State: #{state}"
end

# Set period for touch state callback to 0.01s (10ms)
mt.set_touch_state_callback_configuration 10, true

puts 'Press key to exit'
$stdin.gets
ipcon.disconnect
