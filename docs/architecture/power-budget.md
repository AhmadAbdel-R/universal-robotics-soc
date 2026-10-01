# Power Architecture and Budgeting

## 1. Power Tree Overview

To support universal robotics applications, the board accepts a wide-voltage DC input (12V - 24V nominal). This completely isolates the sensitive digital electronics from noisy, sagging battery voltages caused by motor transients.

The power tree is split into two stages:
1.  **Stage 1 (Front-End):** A high-power, wide-input 5V step-down (buck) converter.
2.  **Stage 2 (Core):** An STPMIC25 handling all precise low-voltage rails and boot sequencing.

### Stage 1: Front-End 5.0V Regulator
*   **Input:** 9V to 36V DC (Barrel Jack or Terminal Block)
*   **Output:** 5.0V System Bus
*   **Component:** Robust 5A/6A synchronous buck converter (e.g., TI TPS5450 or LMR33630).

### Stage 2: STPMIC25 Allocation

The STPMIC25 uses its internal NVM state machine to automatically handle the strict power-up sequencing required by the STM32MP257.

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

---

## 2. Power Consumption Calculations

To size the Stage 1 regulator, we must calculate the absolute maximum worst-case power draw of all components simultaneously.

### Core PMIC Loads (Stage 2 Output)
1.  **STM32MP257 (SoC):** ~4.0 Watts
    *   `VDDCORE` (0.82V): ~800mA max (0.65W)
    *   `VDDCPU` (0.82V): ~1500mA max (1.23W)
    *   `VDDGPU` (0.80V): ~1500mA max (1.20W)
    *   `VDDA18` / I/O: ~300mA max (0.54W)
2.  **LPDDR4 Memory (4GB Total):** ~2.34 Watts
    *   `VDD1` (1.8V): ~80mA (0.14W)
    *   `VDD2` (1.1V): ~1.2A (1.32W)
    *   `VDDQ` (1.1V): ~0.8A (0.88W)
3.  **2x Gigabit Ethernet PHYs (DP83867):** ~0.74 Watts
    *   `VDD1P0` (1.0V): ~216mA (0.22W)
    *   `VDDA2P5` (2.5V): ~172mA (0.43W)
    *   `VDDIO` (1.8V): ~48mA (0.09W)
4.  **WiFi/BT Module (AP6256):** ~1.04 Watts
    *   `VBAT` (3.3V): ~300mA TX Peak (1.00W)
    *   `VDDIO` (1.8V): ~20mA (0.04W)
5.  **QSPI Flash:** ~0.08 Watts

**Total PMIC Output Power:** ~8.2 Watts
**Total PMIC Input Power (Assuming 85% Efficiency):** ~9.65 Watts

### Raw 5.0V Loads (Direct from Stage 1)
1.  **3x CAN-FD Transceivers (TCAN1044A):** ~0.68 Watts
    *   `VCC` (5.0V): ~135mA max (0.68W)
2.  **External USB Ports (VBUS Delivery):** ~10.0 Watts
    *   USB 2.0 Port: 500mA max (2.5W)
    *   USB 3.0 Port: 1500mA max (7.5W)

### Total System Budget
*   **Total Expected Peak Power:** 9.65W (PMIC) + 10.68W (Raw 5V) = **20.33 Watts**
*   **Total 5.0V Current Required:** 20.33W / 5.0V = **4.06 Amps**

*Conclusion:* The front-end Stage 1 regulator must be sized for a continuous **5.0 Amps** (providing ~20% safety margin over absolute peak draw).

---

## 3. BOM Consolidation Strategy

To minimize assembly costs on LCSC/JLCPCB, we will enforce strict limits on the variety of passive components.

### Inductors (The "One Inductor" Rule)
Because all 7 Buck converters in the STPMIC25 switch at high frequencies (~2 MHz), they can all use the **exact same inductor value**.
*   **Selected Part:** 1.0 µH (or 0.47 µH), 3A+, 2016 metric (0806 imperial) footprint (e.g., Sunlord MWSA201612).
*   **Why:** Instead of stocking 4 different inductors, we buy one part number in bulk for all 7 bucks. This reduces the feeder count on the pick-and-place machine and secures high-volume pricing.

### Capacitors
We will restrict the decoupling and bulk capacitors to a maximum of 4 distinct part numbers:
1.  **0.1 µF (100nF) 0402 10V:** Local high-frequency decoupling for every IC pin.
2.  **1.0 µF 0402 10V:** Medium-frequency decoupling and LDO outputs.
3.  **10 µF 0603 10V:** Bulk decoupling for Buck outputs and heavy rails.
4.  **22 µF 0603 10V:** Input/Output bulk capacitance for the 5V main rail.

### Resistors (Pull-ups & Strapping)
*   Instead of placing individual 10kΩ or 4.7kΩ resistors for the I2C lines, SDIO lines (WiFi/eMMC), and Ethernet PHY strapping, we will use **0402x4 Resistor Arrays** (4 resistors in one 0804 package). This turns 4 pick-and-place operations into 1.

---

## 4. Thermal Considerations

*   **PMIC Heat Dissipation:** The STPMIC25 is a dense package managing ~8W of power conversion. The PCB must have a solid ground plane directly beneath it, connected by a 3x3 or 4x4 array of thermal vias to the inner ground layers.
*   **Inductor Spacing:** The 7 buck inductors will generate localized heat. During PCB layout, they must be spaced evenly around the perimeter of the PMIC rather than clustered tightly in a single row, to prevent creating a PCB "hotspot".
*   **SoC Heat:** The STM32MP257 Cortex-A35 + NPU will generate heat under heavy load. The PMIC should not be placed immediately adjacent to the SoC core; maintaining a 10-15mm separation between the SoC and the PMIC will distribute the thermal mass effectively across the copper planes.
