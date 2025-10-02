#include "esp_stepper.h"
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "esp_timer.h"

static const int step_sequence[8][4] = {
    {1,0,0,0}, {1,1,0,0}, {0,1,0,0}, {0,1,1,0},
    {0,0,1,0}, {0,0,1,1}, {0,0,0,1}, {1,0,0,1}
};

void stepper_init(StepperMotor* motor, int p1, int p2, int p3, int p4) {
    motor->pin1 = p1;
    motor->pin2 = p2;
    motor->pin3 = p3;
    motor->pin4 = p4;
    motor->current_position = 0;
    motor->target_position = 0;
    motor->max_speed = 1000;
    motor->acceleration = 100;
    motor->enabled = false;

    gpio_set_direction(p1, GPIO_MODE_OUTPUT);
    gpio_set_direction(p2, GPIO_MODE_OUTPUT);
    gpio_set_direction(p3, GPIO_MODE_OUTPUT);
    gpio_set_direction(p4, GPIO_MODE_OUTPUT);
}

void stepper_set_max_speed(StepperMotor* motor, int speed) {
    motor->max_speed = speed;
}

void stepper_set_acceleration(StepperMotor* motor, int accel) {
    motor->acceleration = accel;
}

void stepper_enable(StepperMotor* motor) {
    motor->enabled = true;
}

void stepper_disable(StepperMotor* motor) {
    motor->enabled = false;
    gpio_set_level(motor->pin1, 0);
    gpio_set_level(motor->pin2, 0);
    gpio_set_level(motor->pin3, 0);
    gpio_set_level(motor->pin4, 0);
}

void stepper_set_target(StepperMotor* motor, int target) {
    motor->target_position = target;
}

void stepper_run(StepperMotor* motor) {
    if (!motor->enabled) return;

    int dir = (motor->target_position > motor->current_position) ? 1 : -1;
    int steps = abs(motor->target_position - motor->current_position);
    int delay_us = 1000000 / motor->max_speed;

    for (int i = 0; i < steps; i++) {
        int seq = (motor->current_position + i * dir) % 8;
        if (seq < 0) seq += 8;

        gpio_set_level(motor->pin1, step_sequence[seq][0]);
        gpio_set_level(motor->pin2, step_sequence[seq][1]);
        gpio_set_level(motor->pin3, step_sequence[seq][2]);
        gpio_set_level(motor->pin4, step_sequence[seq][3]);

        motor->current_position += dir;
        ets_delay_us(delay_us);
    }

    stepper_disable(motor);
}
