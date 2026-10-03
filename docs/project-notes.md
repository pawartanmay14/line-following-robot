# Project Notes

## Objective

Create a self-correcting autonomous robot that can navigate straight lines and curves without human intervention.

## Core concept

The robot uses closed-loop feedback. IR sensors observe the path and the Arduino changes motor behavior based on the sensor readings.

## Reflection principle

- White: strong IR reflection
- Black: weak/no IR reflection

## Algorithm from the presentation

1. Read IR sensor data.
2. Compare sensor values.
3. Left = 0 and Right = 0 -> straight.
4. Left = 1 (on line) -> slow left motor and speed up right motor to turn left.
5. Repeat every few milliseconds.

The presentation recommends PID control as an improvement for smoother operation at higher speeds.

## Limitations / calibration

The presentation does not provide:

- an exact L298N/L293D pin-by-pin wiring diagram,
- exact motor polarity,
- exact IR sensor model,
- exact sensor threshold/polarity,
- a complete right-turn branch in the stated algorithm.

Therefore, the Arduino sketch contains configurable assumptions for these details rather than claiming they were specified by the presentation.
