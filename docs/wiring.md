# Wiring Guide

The project presentation gives the following example connections.

## IR sensors

| IR module | Arduino Uno |
|---|---|
| Left OUT | D2 |
| Right OUT | D3 |
| VCC | 5V |
| GND | GND |

## Motor driver

The presentation specifies four Arduino output pins as examples:

- D5
- D6
- D9
- D10

These should be connected to the four motor-driver input/control pins according to the specific L298N or L293D module being used.

The driver output terminals connect to the left and right DC motors.

## Power

The presentation lists:

- 7.4 V Li-ion battery, or
- 9 V battery

Use the power arrangement appropriate for the exact motor driver, Arduino supply method, motors, and battery. **Do not connect a battery directly to an Arduino or motor in a way that exceeds the component's ratings.**

### Common ground

A common GND must be maintained between:

- Arduino
- IR sensors
- motor driver
- motor-driver control ground

The presentation explicitly notes the importance of a common ground.
