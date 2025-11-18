# nRF52840 PWM LED Controller

This project implements a PWM-based LED controller for nRF52840 Dongle with smooth blinking and button control.

## Features

- ✅ Software PWM with 1kHz frequency
- ✅ Smooth duty cycle transition 0% → 100% → 0%
- ✅ LED sequence: Red → Green → Blue → Red (ABCD pattern)
- ✅ Button double-click to start/stop blinking
- ✅ DFU firmware update support

## Requirements

- nRF52840 Dongle
- nRF5 SDK 17.1.0
- arm-none-eabi-gcc
- nrfutil

## Building

```bash
make clean
make

