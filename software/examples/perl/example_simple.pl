#!/usr/bin/perl

use strict;
use Tinkerforge::IPConnection;
use Tinkerforge::BrickletMultiTouchV2;

use constant HOST => 'localhost';
use constant PORT => 4223;
use constant UID => 'XYZ'; # Change XYZ to the UID of your Multi Touch Bricklet 2.0

my $ipcon = Tinkerforge::IPConnection->new(); # Create IP connection
my $mt = Tinkerforge::BrickletMultiTouchV2->new(&UID, $ipcon); # Create device object

$ipcon->connect(&HOST, &PORT); # Connect to brickd
# Don't use device before ipcon is connected

# Get current touch state
my $state = $mt->get_touch_state();

print "Electrode 0: " . @{$state}[0] . "\n";
print "Electrode 1: " . @{$state}[1] . "\n";
print "Electrode 2: " . @{$state}[2] . "\n";
print "Electrode 3: " . @{$state}[3] . "\n";
print "Electrode 4: " . @{$state}[4] . "\n";
print "Electrode 5: " . @{$state}[5] . "\n";
print "Electrode 6: " . @{$state}[6] . "\n";
print "Electrode 7: " . @{$state}[7] . "\n";
print "Electrode 8: " . @{$state}[8] . "\n";
print "Electrode 9: " . @{$state}[9] . "\n";
print "Electrode 10: " . @{$state}[10] . "\n";
print "Electrode 11: " . @{$state}[11] . "\n";
print "Proximity: " . @{$state}[12] . "\n";

print "Press key to exit\n";
<STDIN>;
$ipcon->disconnect();
