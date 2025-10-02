#include <stdio.h>
#include "esp_stepper.h"

StepperMotor motor;

void app_main(void) {
    stepper_init(&motor, 27, 25, 26, 33);
    stepper_set_max_speed(&motor, 1300);
    stepper_set_acceleration(&motor, 1300);
    stepper_enable(&motor);
    stepper_set_target(&motor, 4000);
    stepper_run(&motor);
}
