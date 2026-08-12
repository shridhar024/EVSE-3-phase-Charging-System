# EVSE Charger Controller

A modular embedded firmware project for an Electric Vehicle Supply Equipment (EVSE) charger.

## Overview

This project implements the control and monitoring functionality required for an EVSE charging system.

The firmware is designed using a layered architecture to improve modularity, maintainability, portability, and hardware abstraction.

## Features

- EVSE charging state management
- Voltage and current measurement
- Power and energy monitoring
- Temperature monitoring
- Contactor control and feedback
- RFID-based user authentication
- Control Pilot (CP) monitoring
- Fault and protection handling
- LCD user interface
- Modular BSP and driver architecture
- Hardware abstraction using STM32 HAL

## System Architecture

```text
Application
     │
     ▼
Service / Control Layer
     │
     ▼
Driver Layer
     │
     ▼
BSP Layer
     │
     ▼
STM32 HAL
     │
     ▼
Hardware
