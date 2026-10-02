# High-Current Pass-Through Architecture

This document outlines the architecture for the high-current actuator pass-through.

## Use Cases
**DESIGN CHOICE**: This path is intended for large RC servos, robotic arm actuators, linear actuators, motor controllers, and ESCs.

## Architecture
**DESIGN CHOICE**: 
`BATTERY -> main fuse/protection -> reverse polarity/ideal diode -> high-current protected switch/eFuse -> ACTUATOR POWER DISTRIBUTION -> individual protected outputs`

**DATASHEET REQUIREMENT / DESIGN CHOICE**: Do NOT route actuator current through STM32 PMIC, compute regulators, sensor rail, or thin signal-plane copper.

## Risk Analysis (Section G)
The following potential failure modes have been identified:
- **Thermal**: PCB trace overheating, via heating, connector overheating, contact resistance, copper neck-down.
- **Conduction**: MOSFET conduction loss, fuse heating, solder-joint heating.
- **Shorts/Reversal**: Battery short circuit, actuator short circuit, connector reverse insertion.
- **Back EMF/Transients**: Actuator regenerative energy, backfeeding, source cross-conduction.
- **Inrush**: Hot-plug arcing, large bulk-capacitor inrush.
- **Signal Integrity**: Ground bounce, sensor corruption, processor resets.
- **EMI/Noise**: Magnetic interference with magnetometer, EMI from high-current wiring.
- **Sensor Accuracy**: Thermal coupling into IMU/barometer.

## Implementation Options
- **Option 1**: PCB copper only (if current/copper/temp allow)
- **Option 2**: Heavy copper / multilayer parallel planes (2oz, 3oz, via arrays)
- **Option 3**: Bus bar / power distribution daughterboard

**TBD - REQUIRES <missing param>**: Do not choose until actuator current requirements are known.

## Ground Architecture
**THEORY / DESIGN CHOICE**: 
- Actuator current return must NOT pass through the sensitive processor/sensor return path.
- Maintain a low-impedance high-current path between power connectors.
- High-current return should not flow beneath IMU, magnetometer, barometer, RF, or high-speed interfaces.
- Use controlled current-return geometry.

## Per-Output Protection
**DESIGN CHOICE**: Each output may utilize a fuse, eFuse, resettable fuse, high-side switch, current sensing, short-circuit, or thermal protection.
**THEORY**: Failure on one actuator should not collapse the compute rail.

## Board Form-Factor Risk
**ASSUMPTION / DESIGN CHOICE**: Compact processor board and high-current distribution have conflicting layout requirements. 
**TBD - REQUIRES <missing param>**: Project remains open to single PCB vs compute+power daughterboard until current/dimensions are frozen.
