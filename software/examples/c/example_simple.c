#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_multi_touch_v2.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your Multi Touch Bricklet 2.0

int main(void) {
	// Create IP connection
	IPConnection ipcon;
	ipcon_create(&ipcon);

	// Create device object
	MultiTouchV2 mt;
	multi_touch_v2_create(&mt, UID, &ipcon);

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		return 1;
	}
	// Don't use device before ipcon is connected

	// Get current touch state
	bool state[13];
	if(multi_touch_v2_get_touch_state(&mt, state) < 0) {
		fprintf(stderr, "Could not get touch state, probably timeout\n");
		return 1;
	}

	printf("Touch State: %s\n", state ? "true" : "false");

	printf("Press key to exit\n");
	getchar();
	multi_touch_v2_destroy(&mt);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
