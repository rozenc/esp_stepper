#ifndef ESP_STEPPER_H
#define ESP_STEPPER_H

#include <stdint.h>
#include <stdbool.h>

typedef struct {
    int pin1, pin2, pin3, pin4;
    int current_position;
    int target_position;
    int max_speed;
    int acceleration;
    bool enabled;
} StepperMotor;

void stepper_init(StepperMotor* motor, int p1, int p2, int p3, int p4);
void stepper_set_max_speed(StepperMotor* motor, int speed);
void stepper_set_acceleration(StepperMotor* motor, int accel);
void stepper_enable(StepperMotor* motor);
void stepper_disable(StepperMotor* motor);
void stepper_set_target(StepperMotor* motor, int target);
void stepper_run(StepperMotor* motor);

#endif
