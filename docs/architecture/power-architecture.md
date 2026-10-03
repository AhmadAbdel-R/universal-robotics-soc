# Power Architecture

This is the master power architecture document for the universal robotics controller based on the STM32MP257.

## Battery Input Envelope

**DESIGN CHOICE**: The system targets 2S through 8S battery input.

| Chemistry | Series Count | Vcell Min | Vcell Nominal | Vcell Max | Pack Min | Pack Nominal | Pack Max | Expected Transient/Surge | Reverse Polarity Case | Expected Current | Connector Rating | Source Impedance |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| Li-ion/LiPo | 2S | 3.0V | 3.7V | 4.2V | 6.0V | 7.4V | 8.4V | TBD | TBD | TBD - REQUIRES <missing param> | TBD | TBD - REQUIRES <missing param> |
| Li-ion/LiPo | 3S | 3.0V | 3.7V | 4.2V | 9.0V | 11.1V | 12.6V | TBD | TBD | TBD - REQUIRES <missing param> | TBD | TBD - REQUIRES <missing param> |
| Li-ion/LiPo | 4S | 3.0V | 3.7V | 4.2V | 12.0V | 14.8V | 16.8V | TBD | TBD | TBD - REQUIRES <missing param> | TBD | TBD - REQUIRES <missing param> |
| Li-ion/LiPo | 5S | 3.0V | 3.7V | 4.2V | 15.0V | 18.5V | 21.0V | TBD | TBD | TBD - REQUIRES <missing param> | TBD | TBD - REQUIRES <missing param> |
| Li-ion/LiPo | 6S | 3.0V | 3.7V | 4.2V | 18.0V | 22.2V | 25.2V | TBD | TBD | TBD - REQUIRES <missing param> | TBD | TBD - REQUIRES <missing param> |
| Li-ion/LiPo | 7S | 3.0V | 3.7V | 4.2V | 21.0V | 25.9V | 29.4V | TBD | TBD | TBD - REQUIRES <missing param> | TBD | TBD - REQUIRES <missing param> |
| Li-ion/LiPo | 8S | 3.0V | 3.7V | 4.2V | 24.0V | 29.6V | 33.6V | TBD | TBD | TBD - REQUIRES <missing param> | TBD | TBD - REQUIRES <missing param> |
| LiFePO4 | 2S | 2.5V | 3.2V | 3.65V | 5.0V | 6.4V | 7.3V | TBD | TBD | TBD - REQUIRES <missing param> | TBD | TBD - REQUIRES <missing param> |
| LiFePO4 | 3S | 2.5V | 3.2V | 3.65V | 7.5V | 9.6V | 10.95V| TBD | TBD | TBD - REQUIRES <missing param> | TBD | TBD - REQUIRES <missing param> |
| LiFePO4 | 4S | 2.5V | 3.2V | 3.65V | 10.0V | 12.8V | 14.6V | TBD | TBD | TBD - REQUIRES <missing param> | TBD | TBD - REQUIRES <missing param> |
| LiFePO4 | 5S | 2.5V | 3.2V | 3.65V | 12.5V | 16.0V | 18.25V| TBD | TBD | TBD - REQUIRES <missing param> | TBD | TBD - REQUIRES <missing param> |
| LiFePO4 | 6S | 2.5V | 3.2V | 3.65V | 15.0V | 19.2V | 21.9V | TBD | TBD | TBD - REQUIRES <missing param> | TBD | TBD - REQUIRES <missing param> |
| LiFePO4 | 7S | 2.5V | 3.2V | 3.65V | 17.5V | 22.4V | 25.55V| TBD | TBD | TBD - REQUIRES <missing param> | TBD | TBD - REQUIRES <missing param> |
| LiFePO4 | 8S | 2.5V | 3.2V | 3.65V | 20.0V | 25.6V | 29.2V | TBD | TBD | TBD - REQUIRES <missing param> | TBD | TBD - REQUIRES <missing param> |
| Li-ion HV | 2S | 3.0V | 3.7V | 4.35V | 6.0V | 7.4V | 8.7V | TBD | TBD | TBD - REQUIRES <missing param> | TBD | TBD - REQUIRES <missing param> |
| Li-ion HV | 3S | 3.0V | 3.7V | 4.35V | 9.0V | 11.1V | 13.05V| TBD | TBD | TBD - REQUIRES <missing param> | TBD | TBD - REQUIRES <missing param> |
| Li-ion HV | 4S | 3.0V | 3.7V | 4.35V | 12.0V | 14.8V | 17.4V | TBD | TBD | TBD - REQUIRES <missing param> | TBD | TBD - REQUIRES <missing param> |
| Li-ion HV | 5S | 3.0V | 3.7V | 4.35V | 15.0V | 18.5V | 21.75V| TBD | TBD | TBD - REQUIRES <missing param> | TBD | TBD - REQUIRES <missing param> |
| Li-ion HV | 6S | 3.0V | 3.7V | 4.35V | 18.0V | 22.2V | 26.1V | TBD | TBD | TBD - REQUIRES <missing param> | TBD | TBD - REQUIRES <missing param> |
| Li-ion HV | 7S | 3.0V | 3.7V | 4.35V | 21.0V | 25.9V | 30.45V| TBD | TBD | TBD - REQUIRES <missing param> | TBD | TBD - REQUIRES <missing param> |
| Li-ion HV | 8S | 3.0V | 3.7V | 4.35V | 24.0V | 29.6V | 34.8V | TBD | TBD | TBD - REQUIRES <missing param> | TBD | TBD - REQUIRES <missing param> |

**THEORY**: Components exposed to raw battery must have headroom above max steady-state for: hot plug, wiring inductance, regenerative loads, actuator braking, motor-controller transients, connector arcing, and supply overshoot. 

**DATASHEET REQUIREMENT**: The required transient rating must be determined from the actual environment.

## Power Architecture Block Diagram

```mermaid
flowchart TD
    BAT[BATTERY INPUT] --> IN_PROT[INPUT PROTECTION]
    IN_PROT --> IDEAL_DIODE[IDEAL DIODE / eFUSE]
    IDEAL_DIODE --> PROT_BUS[PROTECTED BATTERY BUS]
    
    PROT_BUS --> COMP_PATH[COMPUTE POWER PATH]
    PROT_BUS --> ACT_PATH[ACTUATOR POWER PATH]
    
    COMP_PATH --> ARB[source arbitration / PowerPath]
    ARB --> VIN_SYS[VIN_SYS]
    VIN_SYS --> PMIC[compute PMIC]
    PMIC --> STM32[STM32 / RAM / IO]
    
    ACT_PATH --> HIGH_CUR[high-current protection]
    HIGH_CUR --> ACT_PWR_RAW[ACT_PWR_RAW]
    ACT_PWR_RAW --> OUT[outputs]
```

**DESIGN CHOICE**: Compute and actuator paths must be separated. Actuators generate extreme electrical noise, large ground bounce, and severe voltage transients during braking or high-torque events. If compute and actuator share the same power regulation path, these transients can violate the PMIC input specifications or couple into sensitive STM32 rails, leading to brown-outs, spontaneous resets, or sensor data corruption.

## PowerPath Part Evaluation

**PROPOSED - NEEDS CALCULATION, NEEDS SIMULATION, NEEDS LCSC VERIFICATION**

### C1: LM7480 / LM7480-Q1 Class
- **Description**: 3-65V ideal-diode controller
- **External**: External back-to-back N-channel MOSFETs
- **Features**: reverse polarity protection, reverse current blocking, ideal-diode behavior, overvoltage protection, external MOSFET scalability
- **Note**: NOT automatically a complete source-priority mux. Evaluate for 2S-8S compute power path.

### C2: TPS4811-Q1 Class
- **Description**: Wide-voltage smart high-side controller
- **External**: External MOSFETs, current measurement, overcurrent/short-circuit protection
- **Note**: Evaluate for high-current actuator pass-through, protected battery output, power distribution, electronic fuse. Do NOT lock until LCSC sourcing verified.

### C3: Other Options

| Part | Manufacturer | VIN Range | Features | External FET | LCSC | Status |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| TBD - REQUIRES <missing param> | TI/ADI/ST/Infineon/MPS/onsemi | >=40V | Reverse-current blocking, programmable UVLO/OVP, inrush control | Yes | TBD | PROPOSED - NEEDS LCSC VERIFICATION |
| TBD - REQUIRES <missing param> | TI/ADI/ST/Infineon/MPS/onsemi | >=40V | Thermal protection, fault outputs | Yes | TBD | PROPOSED - NEEDS LCSC VERIFICATION |

*Research and selection of specific part numbers from other vendors are TBD.*

## Actuator Power Architecture

**DESIGN CHOICE**: `ACT_PWR_RAW` vs `ACT_PWR_REGULATED` distinction.
`ACT_PWR_RAW` is approximately battery voltage after protection (up to ~33.6V for 8S Li-ion or ~34.8V for 8S HV).

**THEORY**: Many servos CANNOT tolerate this voltage. 
Possible regulated actuator rails: 5V, 6V, 7.4V, 8.4V, 12V, configurable.

**TBD - REQUIRES <missing param>**: Do NOT select final regulator until servo voltage, current, power, and thermal constraints are defined. Evaluate whether regulated power belongs on motherboard, daughterboard, or external module.

## Emergency Actuator Disconnect

**DESIGN CHOICE**: Architecture where ACTUATOR POWER can be disconnected while COMPUTE remains alive. This enables ESTOP, fault shutdown, debugging, and maintaining a safe state. 
**DATASHEET REQUIREMENT**: The processor should observe actuator-power state. 

*Note: Do NOT claim functional safety certification. This design has not been evaluated for formal SIL/ASIL ratings.*

## USB-C Power Boundary

**DESIGN CHOICE**: USB-C development power defaults to COMPUTE ONLY.
**THEORY**: Must prevent battery->USB backfeed and actuator->USB backfeed to protect the developer's PC and the USB-C source.

## External Supply / Dock Power

**DESIGN CHOICE**: The system supports `DOCK_COMPUTE_ONLY` vs `DOCK_FULL_POWER` capability classes.

## Regenerative Energy

**THEORY**: Motors/actuators may return energy.
**DESIGN CHOICE**: System must account for reverse-current blocking, bus voltage rise, TVS/clamp, braking resistor, ESC behavior, and battery absorption.

## Battery Management (BMS) & Digital Telemetry Architecture

**DESIGN CHOICE**: The platform supports **2S through 8S battery systems** under the following architectural guidelines:

1. **External Pack BMS Preferred:** The compute motherboard does **NOT** integrate cell-balancing circuitry or high-current BMS switching FETs by default. High-current cell balancing and individual cell chemistry management are delegated to an external smart battery pack or dedicated power daughterboard.
2. **Motherboard Ingress Protection:** The motherboard implements:
   - Primary catastrophic fuse protection.
   - Solid-state reverse-polarity protection / ideal diode controller (e.g., LM7480 class).
   - Bidirectional transient voltage suppressors (TVS) sized for hot-plug and inductive flyback.
   - Electronic fuse / inrush current limiter for compute rails.
3. **Dedicated Digital Telemetry (INA229):**
   - High-voltage, high-accuracy power monitoring is provided by a dedicated digital power monitor (Texas Instruments **INA229** or equivalent 85 V, 20-bit delta-sigma monitor).
   - Interfaces via SPI or I2C directly to the Cortex-M33 real-time domain.
   - Features a dedicated hardware alert output (`INA229_ALERT`) connected to an M33 EXTI line for microsecond-scale overcurrent / under-voltage detection.
   - **Architectural Exclusion:** Internal STM32 ADC channels are intentionally **NOT** committed to primary battery/current sensing to avoid noise injection, reference drift, and high-voltage resistive divider routing near sensitive analog pins.
4. **BMS Hardware Supervisory Interface:**
   - `BMS_FAULT`: Active-low hardware alert input from external BMS to Cortex-M33, triggering immediate actuator safe-state or emergency disconnect.
   - `BMS_ENABLE`: Active-high output from Cortex-M33 to external pack contactor/switch.
   - **Smart BMS Communications:** Optional telemetry over `FDCAN3` (isolated CAN) or `UART7` for battery state-of-charge (SoC), cell voltages, and cycle health.
   - **Graceful Shutdown:** Cortex-M33 signals Cortex-A35 via IPC (RPMsg) to execute clean filesystem sync and unmount prior to pack depletion.
5. **Actuator Isolation:** The high-current actuator path (`ACT_PWR_RAW`) is physically separated from the compute PMIC input (`VIN_SYS`), preventing motor inrush and back-EMF from coupling into core compute rails.

## Power Tree Detail

```mermaid
flowchart TD
    subgraph Sources
        BAT[2S-8S Battery]
        EXT_DC[External DC / Dock]
        USB[USB-C Dev Input]
    end

    BAT --> PROT[Protection & Selection]
    EXT_DC --> PROT
    USB --> PROT_USB[USB Protection]
    PROT_USB --> ARB_COMPUTE

    PROT --> ARB_COMPUTE[Compute Arbitrator]
    PROT --> ARB_ACTUATOR[Actuator Path]

    ARB_COMPUTE --> VIN_SYS[VIN_SYS]
    VIN_SYS --> PMIC[Compute PMIC/Regulators]
    PMIC --> V_CPU[STM32 CPU Rails]
    PMIC --> V_MEM[LPDDR4 / eMMC]
    PMIC --> V_IO[IO / Sensors]

    ARB_ACTUATOR --> HIGH_CUR_PROT[High-Current Protection]
    HIGH_CUR_PROT --> ACT_PWR_RAW[ACT_PWR_RAW]
    ACT_PWR_RAW --> REG_ACT[Optional ACT_PWR_REGULATED]
```
