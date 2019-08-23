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

# Get current touch state
state = mt.get_touch_state

puts "Electrode 0: #{state[0]}"
puts "Electrode 1: #{state[1]}"
puts "Electrode 2: #{state[2]}"
puts "Electrode 3: #{state[3]}"
puts "Electrode 4: #{state[4]}"
puts "Electrode 5: #{state[5]}"
puts "Electrode 6: #{state[6]}"
puts "Electrode 7: #{state[7]}"
puts "Electrode 8: #{state[8]}"
puts "Electrode 9: #{state[9]}"
puts "Electrode 10: #{state[10]}"
puts "Electrode 11: #{state[11]}"
puts "Proximity: #{state[12]}"

puts 'Press key to exit'
$stdin.gets
ipcon.disconnect
