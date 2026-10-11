# Assistive Communication Device

A gesture-based communication device designed to help people with sensory impairments communicate through predefined hand gestures. The system converts gestures into text displayed on an LCD and audio played through a speaker.

## Features
- Hand movement and orientation sensing using the MPU-6050 IMU
- Finger-bending detection using a flex sensor
- Gesture processing using Arduino Nano
- Wireless command transmission using HC-05 Bluetooth modules
- Text output on an LCD and audio output through a speaker

## Hardware
- Arduino Nano and Arduino Uno
- MPU-6050 IMU
- Flex sensor
- 2 × HC-05 Bluetooth modules
- LCD with I2C interface
- SD card reader and SD card
- PAM8403 audio amplifier and speaker

## Working
1. The glove sensors capture hand movement and finger bending.
2. The Arduino Nano identifies one of six predefined gestures and transmits its command over Bluetooth.
3. The Arduino Uno receives the command and displays the corresponding message on the LCD.
4. The associated prerecorded audio message is played through the speaker.

## Documentation
Project report and presentation can be added to the `docs/` directory.

## Contributors
- Govind U
- S. Neha
- Sooraj A R

**Domain:** Embedded Systems, Sensors, Wireless Communication, Assistive Technology
