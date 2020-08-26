#include "bindings/hal_common.h"
#include "bindings/bricklet_multi_touch_v2.h"

#define UID "XYZ" // Change XYZ to the UID of your Multi Touch Bricklet 2.0

void check(int rc, const char* msg);

// Callback function for touch state callback
void touch_state_handler(TF_MultiTouchV2 *device, bool state[13], void *user_data) {
	(void)device; (void)user_data; // avoid unused parameter warning

	tf_hal_printf("Electrode 0: %s\n", state[0] ? "true" : "false");
	tf_hal_printf("Electrode 1: %s\n", state[1] ? "true" : "false");
	tf_hal_printf("Electrode 2: %s\n", state[2] ? "true" : "false");
	tf_hal_printf("Electrode 3: %s\n", state[3] ? "true" : "false");
	tf_hal_printf("Electrode 4: %s\n", state[4] ? "true" : "false");
	tf_hal_printf("Electrode 5: %s\n", state[5] ? "true" : "false");
	tf_hal_printf("Electrode 6: %s\n", state[6] ? "true" : "false");
	tf_hal_printf("Electrode 7: %s\n", state[7] ? "true" : "false");
	tf_hal_printf("Electrode 8: %s\n", state[8] ? "true" : "false");
	tf_hal_printf("Electrode 9: %s\n", state[9] ? "true" : "false");
	tf_hal_printf("Electrode 10: %s\n", state[10] ? "true" : "false");
	tf_hal_printf("Electrode 11: %s\n", state[11] ? "true" : "false");
	tf_hal_printf("Proximity: %s\n", state[12] ? "true" : "false");
	tf_hal_printf("\n");
}

TF_MultiTouchV2 mt;

void example_setup(TF_HalContext *hal) {
	// Create device object
	check(tf_multi_touch_v2_create(&mt, UID, hal), "create device object");

	// Register touch state callback to function touch_state_handler
	tf_multi_touch_v2_register_touch_state_callback(&mt,
	                                                touch_state_handler,
	                                                NULL);

	// Set period for touch state callback to 0.01s (10ms)
	tf_multi_touch_v2_set_touch_state_callback_configuration(&mt, 10, true);
}

void example_loop(TF_HalContext *hal) {
	// Poll for callbacks
	tf_hal_callback_tick(hal, 0);
}
