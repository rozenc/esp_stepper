# ESP-Stepper

A lightweight, expressive stepper motor driver for ESP-IDF — inspired by AccelStepper, rebuilt for visibility and control.

## Features
- Target position control
- Max speed and acceleration
- Enable/disable outputs
- 8-step half-stepping sequence
- Designed for FreeRTOS task integration

## Example

```c
StepperMotor motor;
stepper_init(&motor, 27, 25, 26, 33);
stepper_set_max_speed(&motor, 1300);
stepper_set_acceleration(&motor, 1300);
stepper_enable(&motor);
stepper_set_target(&motor, 5000);
stepper_run(&motor);
