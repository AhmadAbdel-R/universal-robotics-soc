# Hardware Design Sequence (STM32MP257)

Because the SoC acts as the central hub that influences every other subsystem, the hardware schematic capture and PCB layout must follow a strict sequential order. This document outlines the step-by-step roadmap for designing the universal robotics board around the **STMicroelectronics STM32MP257**.

> **Essential Reference:** [AN5489: Getting started with STM32MP25xx hardware development (PDF)](https://www.st.com/resource/en/application_note/an5489-getting-started-with-stm32mp25xx-mpus-hardware-development-stmicroelectronics.pdf)

## Phase 1: Boot, Flashing, & Debugging
Before the processor can do anything, we must ensure it can be programmed from a factory-blank state.
- **Boot Mode Strapping (DIP Switches):** Design the resistor network and a physical multi-position **DIP Switch Array** for the `BOOT_MODE` pins. This allows developers to manually flip physical switches on the board to toggle between booting from eMMC, QSPI, or forcing the SoC into USB Serial/DFU Downloader mode.
- **Serial Downloader (USB):** Route the primary USB interface to a Type-C connector. This is mandatory for using **STM32CubeProgrammer** to flash the board initially.
- **FTDI Debugger (Onboard JTAG/UART):** Integrate the FT2232HL chip directly on the board. Route Channel A to the STM32 JTAG chain, and Channel B to the primary Linux Serial Console (UART). This provides immediate out-of-the-box debug access.

## Phase 2: Configuration Memory (Bootloader)
To prevent the board from being "bricked" during Linux OS updates, the primary bootloader (TF-A and U-Boot) will live on a separate, highly reliable flash chip.
- **Select QSPI / Octa-SPI NOR Flash:** [Winbond W25Q256JVFIQ (32MB)](../../references/datasheets/W25Q256JVFIQ.pdf)
- **OCTOSPI Interface:** Route the OCTOSPI signals from the STM32MP257 to the NOR flash in Quad-SPI mode on a 3.3V IO bank.

## Phase 3: Main Memory (LPDDR4)
The most complex and critical high-speed layout task.
- **Reference Guide:** [AN5724: Guidelines for DDR memory routing on STM32MP2 (PDF)](https://www.st.com/resource/en/application_note/an5724-guidelines-for-ddr-memory-routing-on-stm32mp2-mpus-stmicroelectronics.pdf)
- **Selected Memory:** [Micron MT53E512M32D1ZW-046 IT:B (2GB, 32-bit)](https://www.lcsc.com/product-detail/LPDDR_Micron-Tech-MT53E512M32D1ZW-046-IT-B_C5330502.html)
- **Memory Topology:** Implement a **Point-to-Point topology** using a single 32-bit RAM chip. Do NOT use a multi-drop topology to preserve the 6-layer stackup simplicity.
- **Impedance & Length Matching:** Define the strict trace length matching rules (byte lanes, clock, strobes) and impedance targets (40-ohm SE, 80-ohm Diff).

## Phase 4: Mass Storage (eMMC)
- **Selected eMMC 5.1 Chip:** [FORESEE FEMDRW064G-88A19 (64GB)](https://www.lcsc.com/product-detail/eMMC_FORESEE-FEMDRW064G-88A19_C719927.html)
- **Design Logic:** A massive 64GB eMMC module is required for the Linux OS because the single PCIe Gen2 lane is strictly reserved for M.2 expansion.
- **SDMMC Routing:** Route the 8-bit eMMC data bus (`SDMMC2` interface), clock, and command lines following AN5489 guidelines.

## Phase 5: High-Speed I/O
- **Networking (Dual Ethernet):** Route the two Gigabit Ethernet MACs (one with TSN) to the selected [Texas Instruments DP83867IRRGZR RGMII PHYs](../../references/datasheets/DP83867IRRGZR.pdf). Route the PHYs to standard **RJ45 connectors with integrated magnetics**.
- **Expansion (M.2 PCIe):** Route the single PCIe Gen2 lane to an **M.2 Key-M Slot**. This preserves modularity, allowing users to plug in NVMe SSDs, Coral Edge TPUs, or M.2 WiFi 6 cards as needed.
- **Cameras/Display:** Route the MIPI-CSI and MIPI-DSI interfaces to standard 15-pin FFC connectors or high-speed board-to-board connectors for robotics vision and HMI.

## Phase 6: Robotics & Low-Speed I/O
- **CAN-FD:** Route the 3x FDCAN interfaces to [Texas Instruments TCAN1044AVDRQ1 Transceivers](../../references/datasheets/TCAN1044AVDRQ1.pdf). Use the separate `VIO` pin tied to 1.8V to interface natively with the STM32 without level shifters.
- **Serial/I2C/SPI:** Route headers for sensors, IMUs, and external microcontrollers.

## Phase 7: Power Delivery (Power Budget & PMIC)
Power is purposely designed **last**. We cannot finalize the power architecture until we have selected the RAM, eMMC, PHYs, and external IO, because their voltage levels influence the total power budget.
- **Consolidate Voltage Rails:** Analyze the voltage requirements of all selected chips (e.g., 1.8V, 3.3V) and consolidate them to reduce the BOM count.
- **Power Budgeting & Simulation:** Calculate the maximum current draw across all rails, establish a power budget, and simulate the thermal load.
- **Core PMIC Selection:** Select the core PMIC (e.g., **STPMIC25**) to handle the strict power-up/power-down sequencing required by the STM32MP257. *(See [AN5727: How to use STPMIC25](https://www.st.com/resource/en/application_note/an5727-how-to-use-stpmic25-for-a-wall-adapter-powered-application-on-stm32mp25-mpus-stmicroelectronics.pdf))*
- **Decoupling:** Map out the exact placement of local decoupling capacitors for the BGA power rails.
