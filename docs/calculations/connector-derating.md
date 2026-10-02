# Connector Derating Methodology

This document establishes the methodology for determining the true current-carrying capacity and safe operating limits for all connectors in the Universal Robotics Controller.

## Why Advertised Current Ratings Are Insufficient

Connector datasheets often advertise a maximum current rating based on ideal, isolated laboratory conditions (e.g., a single pin carrying current in a 20°C ambient environment with large copper blocks sinking the heat). In a real robotics environment, this rating must be derated for:
- **Temperature Derating:** Operating ambient temperature limits and expected internal enclosure temperatures.
- **Contact Resistance Aging:** Increases in resistance due to oxidation, fretting wear, thermal cycling, and vibration.
- **PCB Copper Interface:** The thermal resistance of the PCB traces connecting to the pins (traces often cannot carry away heat as effectively as test fixtures).
- **Enclosure Effects:** Lack of airflow or tight geometric constraints.
- **Multi-contact Derating:** When multiple adjacent pins carry high current, mutual heating reduces the maximum safe current per pin.

## Connector Evaluation Template

For every connector used in the high-power or high-reliability paths, the following template must be completed.

### [Connector Family / ID]
**INPUTS:**
- Part Number: TBD - REQUIRES DATASHEET
- Advertised Current (per pin): TBD - REQUIRES DATASHEET
- Number of Active Power Pins: TBD - REQUIRES DATASHEET
- Max Ambient Temperature: TBD - REQUIRES MEASUREMENT

**ASSUMPTIONS / DERATING FACTORS:**
- Multi-pin derating factor: TBD - REQUIRES DATASHEET
- Aging margin factor: TBD - ESTIMATED
- Enclosure thermal restriction factor: TBD - REQUIRES SIMULATION

**EQUATION:**
$$I_{DERATED} = I_{ADVERTISED} \cdot F_{MULTIPIN} \cdot F_{AGING} \cdot F_{THERMAL}$$

**SUBSTITUTION:**
- $I_{ADVERTISED} =$ TBD
- $F_{MULTIPIN} =$ TBD
- $F_{AGING} =$ TBD
- $F_{THERMAL} =$ TBD

**RESULT:**
- Safe Operating Current per Pin: TBD - REQUIRES DATASHEET
- Total Safe Connector Current: TBD - REQUIRES DATASHEET

**MARGIN:** TBD
**SOURCE:** Manufacturer Derating Curves / Reliability Guidelines
**STATUS:** NEEDS DATASHEET

---

## Connector Families (from connector study)

| Connector Family | Location / Use | Advertised Current | Derated Current | Status |
| :--- | :--- | :--- | :--- | :--- |
| TBD - REQUIRES DATASHEET | Main Battery Input | TBD - REQUIRES DATASHEET | TBD - REQUIRES DATASHEET | NEEDS DATASHEET |
| TBD - REQUIRES DATASHEET | Motor/Actuator Output | TBD - REQUIRES DATASHEET | TBD - REQUIRES DATASHEET | NEEDS DATASHEET |
| TBD - REQUIRES DATASHEET | Sensor Expansion | TBD - REQUIRES DATASHEET | TBD - REQUIRES DATASHEET | NEEDS DATASHEET |
| TBD - REQUIRES DATASHEET | PoE / Network | TBD - REQUIRES DATASHEET | TBD - REQUIRES DATASHEET | NEEDS DATASHEET |
| TBD - REQUIRES DATASHEET | Internal Mezzanine | TBD - REQUIRES DATASHEET | TBD - REQUIRES DATASHEET | NEEDS DATASHEET |
