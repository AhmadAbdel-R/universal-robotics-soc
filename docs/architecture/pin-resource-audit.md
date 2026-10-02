# Preliminary Pin & Resource Audit

This document outlines the conceptual pin and resource conflicts that must be resolved during the STM32CubeMX validation stage. It does NOT invent specific pin mappings, but rather highlights the severe bottlenecks and voltage domain constraints inherent to the STM32MP257 TFBGA436 package.

## Resource Classifications

### 1. LOCKED RESOURCES (No Muxing Flexibility)
These resources are physically tied to dedicated pins, balls, or pads on the STM32MP257. They cannot be moved.
- **LPDDR4 Interface:** Data, Address, Command, and Clock pins are absolutely fixed.
- **MIPI CSI-2:** Dedicated analog D-PHY pins.
- **MIPI DSI:** Dedicated analog D-PHY pins.
- **PCIe Gen2:** Dedicated high-speed COMBOPHY pins (shared with USB3, but allocated to PCIe).
- **USB 2.0 High-Speed:** Dedicated USB2 PHY analog pins.
- **Oscillators:** HSE (Main Crystal) and LSE (RTC Crystal) are fixed.

### 2. CUBEMX-DEPENDENT RESOURCES (Heavy Constraints)
These resources can technically be muxed, but their constraints are so severe that they effectively dictate the rest of the board.
- **BootROM Requirements:** The `SDMMC2` (eMMC), `XSPI1` (NOR Flash), and `USART` (Recovery Console) must be mapped to specific alternate functions (AF) recognized by the STM32 internal BootROM.
- **Dual Gigabit Ethernet (RGMII):** RGMII consumes 12+ pins *per MAC* (TXD0-3, RXD0-3, TX_CLK, RX_CLK, TX_CTL, RX_CTL) plus MDIO/MDC. Routing two RGMII interfaces consumes a massive portion of the digital I/O and heavily restricts available timer/UART AF mappings.
- **SDIO (Wi-Fi):** Requires a wide 4-bit bus + CLK/CMD. Must not conflict with the eMMC BootROM pins.

### 3. PREFERRED RESOURCES (Moderate Flexibility)
These peripherals have multiple instances and AF mappings, but we have specific requirements for them.
- **FDCAN (3x):** Requires TX/RX pairs. Usually flexible, but we need three instances.
- **Hardware Timers (M33 Motor Control):** The 4-in-1 ESC (M1-M4) and STEP/DIR interfaces require advanced or general-purpose timers capable of PWM, DShot, and DMA generation.
- **Timer Input Capture:** Incremental Encoders (A/B/Z) and GNSS PPS require timers with robust input capture capabilities.
- **ADCs:** VBAT, Current Sense, and Industrial Analog require dedicated analog input pins, which are often scarce.

### 4. FLEXIBLE RESOURCES (High Muxing Availability)
- **SPI / I2C / UART:** The STM32MP257 has numerous USART/UART, SPI, and I2C instances. Assigning the IMU, Magnetometer, Barometer, ELRS, and RS-485 interfaces will be a matter of filling the "gaps" left behind by RGMII and SDMMC.
- **General Purpose EXTI:** Interrupts for DRDY, IMU INT, and drive faults can usually be mapped to a wide variety of standard GPIOs.

## Likely Conceptual Conflicts

### 1. I/O Voltage Domain Compatibility
The most significant hurdle. The STM32MP257 divides its GPIOs into distinct voltage banks (e.g., `VDD`, `VDDIO1`, `VDDIO2`, `VDDIO3`, `VDDIO4`). 
- **Conflict:** You cannot mix 1.8V and 3.3V logic on the same I/O bank.
- **Impact:** We must group peripherals by voltage. E.g., The DP83867 Ethernet PHYs and eMMC require 1.8V. The XSPI NOR Flash and sensors (3V3_SENSOR) require 3.3V. CubeMX will throw errors if we accidentally assign a 3.3V SPI pin to a bank powered by 1.8V.

### 2. RGMII vs. Alternate Functions
Routing two RGMII MACs will consume ~26 pins. These pins often share alternate functions with high-speed SPI or critical timers. We must lock RGMII early in CubeMX.

### 3. ADC Availability vs. Digital Functions
Analog input pins are strictly limited to the ADC peripheral banks. These pins often double as high-value digital I/O. We must prioritize VBAT, Current Sense, and any direct analog sensors to the ADC pins before assigning digital functions.

### 4. High-Speed COMBOPHY Shared Constraint
The 5 Gbps COMBOPHY physically cannot drive PCIe Gen2 and USB 3.0 simultaneously. Our architecture deliberately allocates this to PCIe (M.2 Key-M). The Type-C port is therefore limited to the separate dedicated USB 2.0 PHY.

### 5. Cortex-M33 vs. Cortex-A35 RIF Ownership
The Resource Isolation Framework (RIF) dictates which core "owns" a peripheral.
- **Conflict:** We cannot easily share a single peripheral instance (e.g., `SPI1`) between the M33 and A35.
- **Resolution:** We must dedicate specific hardware instances. For example, `SPI1` is owned by M33 for the IMU, while `SPI2` might be owned by A35 for a high-speed Linux peripheral. EXTI lines and DMA channels must also be cleanly partitioned.
