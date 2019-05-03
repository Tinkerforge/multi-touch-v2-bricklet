#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_multi_touch_v2.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your Multi Touch Bricklet 2.0

// Callback function for touch state callback
void cb_touch_state(uint16_t state, void *user_data) {
	(void)user_data; // avoid unused parameter warning

	printf("Touch State: %u\n", state);
}

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

	// Register touch state callback to function cb_touch_state
	multi_touch_v2_register_callback(&mt,
	                                 MULTI_TOUCH_V2_CALLBACK_TOUCH_STATE,
	                                 (void *)cb_touch_state,
	                                 NULL);

	// Set period for touch state callback to 0.01s (10ms)
	multi_touch_v2_set_touch_state_callback_configuration(&mt, 10, true);

	printf("Press key to exit\n");
	getchar();
	multi_touch_v2_destroy(&mt);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
