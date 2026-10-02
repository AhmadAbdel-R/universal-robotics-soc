# Design Calculation Thermal Document

## Thermal Management Methodology

This document establishes the thermal analysis methodology for the Universal Robotics Controller.

> **[DESIGN CHOICE]** All thermal claims in this repository must be classified as one of:
> THEORY, CALCULATION, SIMULATION, MEASUREMENT, ASSUMPTION, or TBD.

---

## 1. Fundamental Thermal Model

The simplified thermal resistance model for an IC package is:

$$T_J = T_A + P_{DISS} \times \theta$$

where:
- $T_J$ = junction temperature (°C)
- $T_A$ = ambient temperature (°C)
- $P_{DISS}$ = power dissipation (W)
- $\theta$ = applicable thermal resistance (°C/W)

> **[IMPORTANT]** Do NOT blindly use $\theta_{JA}$ from a datasheet without matching PCB conditions.
> The datasheet $\theta_{JA}$ is measured on a specific JEDEC test board (e.g., JESD51-7 high effective thermal
> conductivity board or JESD51-5 1s0p board) which may differ substantially from the actual application PCB.

---

## 2. Thermal Resistance Parameters

| Parameter | Symbol | Meaning | Proper Use |
|-----------|--------|---------|------------|
| Junction-to-Ambient | $\theta_{JA}$ | Total thermal resistance from junction to ambient | Comparative use only; depends heavily on test board |
| Junction-to-Case (top) | $\theta_{JC(top)}$ | Resistance from junction to package top | Valid when heatsink is mounted on package top |
| Junction-to-Board | $\theta_{JB}$ | Resistance from junction through solder balls to board | Valid for board-dominated thermal paths |
| Junction-to-Top (psi) | $\Psi_{JT}$ | Thermal characterization parameter, NOT a true resistance | Use with measured package top temperature |
| Junction-to-Board (psi) | $\Psi_{JB}$ | Thermal characterization parameter | Use with measured board temperature |

> **[THEORY]** $\theta_{JA}$, $\theta_{JC}$, $\theta_{JB}$ are defined as thermal resistances under specific
> boundary conditions. $\Psi_{JT}$ and $\Psi_{JB}$ are characterization parameters that account for parallel
> thermal paths and are NOT interchangeable with the $\theta$ values.

### When to Use Each Parameter

- **$\theta_{JA}$**: Only for rough first-order comparison between packages. Never for final thermal validation.
- **$\theta_{JC(top)}$**: When a heatsink is mounted and top-side cooling dominates.
- **$\Psi_{JT}$**: When you can measure the package top temperature with a thermocouple or thermal camera:
  $T_J \approx T_{TOP} + \Psi_{JT} \times P_{DISS}$
- **Thermal simulation**: Preferred method for complex multi-source thermal scenarios.
- **Physical measurement**: Required for final validation.

---

## 3. Thermal Resistance Network

```
JUNCTION (T_J)
    |
    |--- θ_JC(top) ---> PACKAGE TOP ---> θ_CA ---> AMBIENT
    |
    |--- θ_JB -------> BOARD ---------> θ_BA ---> AMBIENT
    |
    |--- θ_JC(bot) ---> EXPOSED PAD --> PCB COPPER --> AMBIENT
```

For packages with exposed thermal pads (common in power ICs and QFN packages),
the dominant heat path is typically through the pad into the PCB copper.

---

## 4. PCB Thermal Design Factors

The PCB is a critical part of the thermal system. Factors affecting thermal performance:

| Factor | Effect |
|--------|--------|
| Copper weight (oz/ft²) | Heavier copper spreads heat more effectively |
| Number of copper layers | More layers provide parallel thermal paths |
| Thermal vias | Conduct heat from surface to inner planes |
| Copper pour area | Larger area improves spreading and convection |
| Component spacing | Thermal coupling between adjacent hot components |
| Airflow | Forced vs natural convection boundary conditions |
| Enclosure | May restrict airflow but provide conduction paths |

---

## 5. Calculation Templates

### 5.1 Regulator Thermal Estimate

```
INPUTS:
  P_DISS      = TBD - REQUIRES EFFICIENCY CALCULATION
  T_A_MAX     = TBD - REQUIRES ENCLOSURE SPECIFICATION
  θ_JA        = TBD - REQUIRES DATASHEET (note: JEDEC test board value)
  θ_JB        = TBD - REQUIRES DATASHEET
  Ψ_JT        = TBD - REQUIRES DATASHEET

ASSUMPTIONS:
  - PCB copper area differs from JEDEC test board
  - Actual θ_JA may be 20-50% higher than datasheet value on compact boards

EQUATION:
  T_J_ESTIMATE = T_A + P_DISS × θ_JA (first-order only)

SUBSTITUTION:
  TBD - REQUIRES REGULATOR SELECTION AND EFFICIENCY DATA

RESULT:  TBD
MARGIN:  TBD
SOURCE:  CALCULATION (first-order estimate)
STATUS:  NEEDS DATASHEET, NEEDS SIMULATION
```

### 5.2 MOSFET Thermal Estimate

```
INPUTS:
  I_RMS       = TBD - REQUIRES CURRENT SPECIFICATION
  R_DS(ON)    = TBD - REQUIRES MOSFET SELECTION
  T_J_TARGET  = typically 125°C maximum for commercial
  T_A         = TBD - REQUIRES ENCLOSURE SPECIFICATION

EQUATION:
  P_COND = I_RMS² × R_DS(ON) at T_J
  Note: R_DS(ON) increases with temperature, typically 1.5× to 2× from 25°C to 125°C

RESULT:  TBD
STATUS:  NEEDS MOSFET SELECTION, NEEDS CURRENT SPECIFICATION
```

### 5.3 Connector Thermal Estimate

```
INPUTS:
  I           = TBD - REQUIRES CURRENT SPECIFICATION
  R_CONTACT   = TBD - REQUIRES CONNECTOR SELECTION
  N_CONTACTS  = TBD

EQUATION:
  P_CONTACT = I² × R_CONTACT per contact
  ΔT depends on connector thermal resistance and environment

RESULT:  TBD
STATUS:  NEEDS CONNECTOR SELECTION, NEEDS CURRENT SPECIFICATION
```

---

## 6. Status

All thermal calculations in this document are at status: **TBD — NEEDS COMPONENT SELECTION AND POWER DATA**

Thermal validation requires:
1. Component power dissipation values (from efficiency calculations or datasheet)
2. Actual PCB stackup and copper geometry
3. Enclosure / airflow conditions
4. Thermal simulation using appropriate tools
5. Physical measurement with thermal camera and thermocouples

> **[DESIGN CHOICE]** No thermal design shall be called PASS until validated by simulation
> or measurement under representative operating conditions.
