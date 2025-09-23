Ultrasonic Distance Sensor (HC-SR04) on TM4C123
Project Overview

This project demonstrates how to interface the HC-SR04 ultrasonic distance sensor with the TM4C123GH6PM (Tiva-C LaunchPad) microcontroller.

Uses General Purpose Timer1A & Timer1B in 16-bit mode.

Generates a 10 µs trigger pulse to the ultrasonic sensor.

Captures the echo pulse width to measure distance.

Converts the time-of-flight to distance in centimeters.

Outputs the result over UART0 to a PC, viewable in a serial terminal (e.g., PuTTY, Tera Term).
