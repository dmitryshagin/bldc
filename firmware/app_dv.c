#include "ch.h" // ChibiOS
#include "hal.h" // ChibiOS HAL
#include "mc_interface.h" // Motor control functions
#include "hw.h" // Pin mapping on this hardware
#include "timeout.h" // To reset the timeout
#define AVAILABLE_POWERS 3

// Diving Vehicle thread
static THD_FUNCTION(dv_thread, arg);
static THD_WORKING_AREA(dv_thread_wa, 2048); // 2kb stack for this thread

void app_dv_init(void) {
	// Set the UART TX pin as an input with pulldown
	palSetPadMode(HW_UART_TX_PORT, HW_UART_TX_PIN, PAL_MODE_INPUT_PULLDOWN);

	// Start the dv thread
	chThdCreateStatic(dv_thread_wa, sizeof(dv_thread_wa),
		NORMALPRIO, dv_thread, NULL);
}

static THD_FUNCTION(dv_thread, arg) {
	(void)arg;

	chRegSetThreadName("APP_DV");
	static bool need_to_change_power_in_future = false;
	static float power[AVAILABLE_POWERS] = {0.7, 1, 0.5};
	static int power_index = 0;

	for(;;) {

		if (palReadPad(HW_UART_TX_PORT, HW_UART_TX_PIN)) {
			mc_interface_set_duty(power[power_index]);
			need_to_change_power_in_future = true;
		} else {
			if(need_to_change_power_in_future){
				need_to_change_power_in_future = false;
				power_index=(power_index+1)%AVAILABLE_POWERS;
			}
			// If the button is not pressed, release the motor
			mc_interface_release_motor();
		}

		// Run this loop at 100Hz
		chThdSleepMilliseconds(10);

		// Reset the timeout
		timeout_reset();
	}
}
