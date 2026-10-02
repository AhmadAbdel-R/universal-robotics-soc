# Input Power Characterization

This document details the input power boundaries and stability criteria for the Universal Robotics Controller.

## Source Characterization Template

For every power source used with the controller, the following parameters must be evaluated.

| Parameter | Value | Status |
| :--- | :--- | :--- |
| DC Voltage (Nominal) | TBD - REQUIRES BATTERY DATASHEET | NEEDS DATASHEET |
| Min/Max Voltage Envelope | TBD - REQUIRES BATTERY DATASHEET | NEEDS DATASHEET |
| Source Internal Resistance | TBD - REQUIRES MEASUREMENT | NEEDS MEASUREMENT |
| Cable Resistance | TBD - REQUIRES MEASUREMENT | NEEDS MEASUREMENT |
| Cable Inductance | TBD - REQUIRES MEASUREMENT | NEEDS MEASUREMENT |
| Connector Resistance | TBD - REQUIRES DATASHEET | NEEDS DATASHEET |
| Transient Voltage Envelope | TBD - REQUIRES MEASUREMENT | NEEDS MEASUREMENT |
| Source Current Limit | TBD - REQUIRES BATTERY DATASHEET | NEEDS DATASHEET |
| Adapter Current Limit | TBD - REQUIRES DATASHEET | NEEDS DATASHEET |

## Input Power Stability

Switching regulators act as constant-power loads to their input source. As input voltage drops, the input current increases to maintain the same output power, exhibiting a negative incremental input impedance.

### Incremental Input Resistance

**INPUTS:**
- $V_{IN}$: Input voltage to the converter (TBD - REQUIRES MEASUREMENT)
- $P$: Input power to the converter (TBD - REQUIRES MEASUREMENT)

**ASSUMPTIONS:**
- Constant output power load.
- Converter efficiency is roughly constant over the small operating region.

**EQUATION:**
$$R_{INCREMENTAL} \approx -\frac{V_{IN}^2}{P}$$

**SUBSTITUTION:**
- $V_{IN}$ = TBD
- $P$ = TBD

**RESULT:**
- $R_{INCREMENTAL}$ = TBD - REQUIRES MEASUREMENT

**MARGIN:** N/A
**SOURCE:** Middlebrook's Extra Element Theorem / Input Filter Design Principles
**STATUS:** NEEDS MEASUREMENT

### Middlebrook Impedance-Ratio Criterion

To prevent oscillation and instability between the input filter (or source impedance) and the switching converter, the output impedance of the source/filter must be strictly less than the input impedance of the converter across all frequencies.

$|Z_{OUT,SOURCE}| \ll |Z_{IN,CONVERTER}|$

**DESIGN CHOICE / CONSTRAINT:** 
- Source and filter output impedance must remain separated from the converter input impedance.
- Do NOT blindly add large LC filters at the input without verifying the resulting peaking does not violate the Middlebrook criterion. Damping networks (e.g., parallel RC) may be required.
