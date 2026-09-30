# Power Architecture and Budgeting

## 1. Power Tree Overview

The system is powered by a central **STPMIC25** Power Management IC. The STPMIC25 is designed as the official companion chip to the STM32MP2 series and features 7 Buck converters and multiple LDOs. This allows us to power the entire SoC, Memory, and peripherals from a single 5V input, without needing external discrete regulators.

### 5V Main Input
The board will accept 5V from a DC barrel jack or a USB Type-C connector.

### STPMIC25 Allocation

| PMIC Output | Voltage | Expected Peak Load | Destination |
| :--- | :--- | :--- | :--- |
| **Buck 1** | 0.82V | ~2.0A | STM32MP257 `VDDCORE` |
| **Buck 2** | 0.82V | ~2.0A | STM32MP257 `VDDCPU` (Cortex-A35 cores) |
| **Buck 3** | 0.80V | ~1.5A | STM32MP257 `VDDGPU` (GPU & NPU) |
| **Buck 4** | 1.10V | ~1.5A | LPDDR4 Core (`VDD1`, `VDD2`, `VDDQ`) |
| **Buck 5** | 1.80V | ~1.5A | System 1.8V I/O (`VDD`, WiFi IO, Eth PHY IO, CAN IO) |
| **Buck 6** | 3.30V | ~1.0A | System 3.3V I/O (QSPI, USB hub if any, LEDs, misc) |
| **Buck 7** | 1.00V | ~0.5A | 2x Ethernet PHY Digital Core (`VDD1P0`) |
| **LDO 1** | 2.50V | ~150mA | 2x Ethernet PHY Analog (`VDDA2P5`) |
| **LDO 2** | 1.80V | ~100mA | STM32MP257 Analog (`VDDA18AON`) |
| **LDO 3** | 3.30V | ~100mA | STM32MP257 USB PHY (`VDD33USB`, `VDD33UCPD`) |
| **LDO 4** | 0.55V | ~10mA | LPDDR4 Reference Voltage (`VREFDDR`) |

*Note: The exact sequencing of these rails is handled entirely by the STPMIC25's internal NVM (Non-Volatile Memory) state machine. We will source the pre-programmed version of the STPMIC25 intended for the MP25 to ensure the correct boot sequence without MCU intervention.*

---

## 2. BOM Consolidation Strategy

To minimize assembly costs on LCSC/JLCPCB, we will enforce strict limits on the variety of passive components used in the power delivery network.

### Inductors (The "One Inductor" Rule)
Because all 7 Buck converters in the STPMIC25 switch at high frequencies (typically ~2 MHz), they can all use the **exact same inductor value**.
*   **Selected Part:** 1.0 µH (or 0.47 µH), 3A+, 2016 metric (0806 imperial) footprint (e.g., Sunlord MWSA201612 or Murata DFE201610E).
*   **Why:** Instead of stocking 4 different inductors for different rails, we buy one part number in bulk for all 7 bucks. This reduces the feeder count on the pick-and-place machine and gets us high-volume price breaks.

### Capacitors
We will restrict the decoupling and bulk capacitors to a maximum of 4 distinct part numbers:
1.  **0.1 µF (100nF) 0402 10V:** Local high-frequency decoupling for every IC pin.
2.  **1.0 µF 0402 10V:** Medium-frequency decoupling and LDO outputs.
3.  **10 µF 0603 10V:** Bulk decoupling for Buck outputs and heavy rails.
4.  **22 µF 0603 10V:** Input/Output bulk capacitance for the 5V main rail.

### Resistors (Pull-ups & Strapping)
*   Instead of placing individual 10kΩ or 4.7kΩ resistors for the I2C lines, SDIO lines (WiFi/eMMC), and Ethernet PHY strapping, we will use **0402x4 Resistor Arrays** (4 resistors in one 0804 package). This turns 4 pick-and-place operations into 1.

---

## 3. Thermal Considerations

*   **PMIC Heat Dissipation:** The STPMIC25 is a dense QFN/BGA package managing up to 10 Amps of total current. The PCB must have a solid ground plane directly beneath it, connected by a 3x3 or 4x4 array of thermal vias to the inner ground layers.
*   **Inductor Spacing:** The 7 buck inductors will generate localized heat. During PCB layout, they must be spaced evenly around the perimeter of the PMIC rather than clustered tightly in a single row, to prevent creating a PCB "hotspot".
*   **SoC Heat:** The STM32MP257 Cortex-A35 + NPU will generate heat under heavy load. The PMIC should not be placed immediately adjacent to the SoC core; maintaining a 10-15mm separation between the SoC and the PMIC will distribute the thermal mass effectively across the copper planes.
