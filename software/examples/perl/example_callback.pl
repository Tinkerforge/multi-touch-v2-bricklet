#!/usr/bin/perl

use strict;
use Tinkerforge::IPConnection;
use Tinkerforge::BrickletMultiTouchV2;

use constant HOST => 'localhost';
use constant PORT => 4223;
use constant UID => 'XYZ'; # Change XYZ to the UID of your Multi Touch Bricklet 2.0

# Callback subroutine for touch state callback
sub cb_touch_state
{
    my ($state) = @_;

    print "Touch State: $state\n";
}

my $ipcon = Tinkerforge::IPConnection->new(); # Create IP connection
my $mt = Tinkerforge::BrickletMultiTouchV2->new(&UID, $ipcon); # Create device object

$ipcon->connect(&HOST, &PORT); # Connect to brickd
# Don't use device before ipcon is connected

# Register touch state callback to subroutine cb_touch_state
$mt->register_callback($mt->CALLBACK_TOUCH_STATE, 'cb_touch_state');

# Set period for touch state callback to 0.01s (10ms)
$mt->set_touch_state_callback_configuration(10, 1);

print "Press key to exit\n";
<STDIN>;
$ipcon->disconnect();
