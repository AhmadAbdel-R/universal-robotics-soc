# Universal Robotics Controller Calculations Framework

This directory contains the engineering calculations and analysis framework for the Universal Robotics Controller (STM32MP257). 

**CRITICAL RULE**: No values are fabricated. All missing values are marked as `TBD - REQUIRES <missing param>`. All calculations are strictly categorized by their status: CALCULATED, ESTIMATED, NEEDS DATASHEET, NEEDS SIMULATION, NEEDS MEASUREMENT.

## Master Calculation Index & Checklist

### INPUT POWER ([input-power.md](./input-power.md))
- [ ] battery envelope
- [ ] source impedance
- [ ] hot plug
- [ ] TVS
- [ ] fuse
- [ ] ideal diode
- [ ] eFuse
- [ ] source mux

### REGULATORS ([regulator-design.md](./regulator-design.md))

Reference: [TI SLVA477C buck power-stage calculation guide](./buck-power-stage-ti-slva477c.md), including the original TI PDF link and TPS54561 design checks.

- [ ] duty cycle
- [ ] inductor
- [ ] ripple
- [ ] CIN
- [ ] COUT
- [ ] transient
- [ ] efficiency
- [ ] switching losses
- [ ] thermal
- [ ] loop stability

### PDN (Power Delivery Network)
- [ ] load step
- [ ] target impedance
- [ ] capacitor derating
- [ ] SRF
- [ ] antiresonance
- [ ] plane impedance
- [ ] package/on-die boundary

### HIGH CURRENT ([high-current-path.md](./high-current-path.md))
- [ ] trace
- [ ] plane
- [ ] via
- [ ] connector
- [ ] fuse
- [ ] MOSFET
- [ ] shunt
- [ ] thermal

### SIGNAL INTEGRITY
- [ ] edge rate
- [ ] knee frequency
- [ ] impedance
- [ ] propagation delay
- [ ] via
- [ ] stub
- [ ] crosstalk
- [ ] fiber weave
- [ ] return path

### THERMAL
- [ ] SoC
- [ ] PMIC
- [ ] regulators
- [ ] MOSFET
- [ ] connectors
- [ ] copper
- [ ] enclosure

### POWER BUDGET ([power-budget.md](./power-budget.md))
### CONNECTOR DERATING ([connector-derating.md](./connector-derating.md))
