# Hardware Design Sequence (STM32MP257)

Because the SoC acts as the central hub that influences every other subsystem, the hardware schematic capture and PCB layout must follow a strict sequential order. This document outlines the step-by-step roadmap for designing the universal robotics board around the **STMicroelectronics STM32MP257**.

> **Essential Reference:** [AN5489: Getting started with STM32MP25xx hardware development (PDF)](https://www.st.com/resource/en/application_note/an5489-getting-started-with-stm32mp25xx-mpus-hardware-development-stmicroelectronics.pdf)

## 1. Architecture Freeze
Finalize all system requirements, peripheral selections, and memory topologies (e.g., LPDDR4 Point-to-Point, shared high-speed PHY allocation).

## 2. Exact STM32MP257 Package Selection
Lock in the physical constraints: **TFBGA436 (18 mm x 18 mm, 0.8 mm pitch, suffix AI)**.

## 3. CubeMX Platform Verification
Before entering KiCad, use **STM32CubeMX** to verify pin multiplexing, I/O voltage-domain compatibility, and Cortex-A35 vs Cortex-M33 resource ownership (RIF/resource isolation configuration). CubeMX is a verification tool; the architecture remains defined by this repository.

## 4. DDR Verification/Configuration
- **Reference:** [AN5724: Guidelines for DDR memory routing on STM32MP2 (PDF)](https://www.st.com/resource/en/application_note/an5724-guidelines-for-ddr-memory-routing-on-stm32mp2-mpus-stmicroelectronics.pdf)
- Use CubeMX to configure the **Point-to-Point, 32-bit single-rank LPDDR4** interface.

## 5. Boot / Recovery / Debug Verification
- **Boot Mode Strapping:** Assign `BOOT_MODE` pins for DIP switch toggling (eMMC, XSPI, or USB DFU).
- **Serial Downloader (USB):** Ensure Type-C USB assignment for **STM32CubeProgrammer**.
- **FTDI Debugger:** Verify JTAG and UART assignments for the onboard FT2232HL.

## 6. eMMC and NOR Boot Storage
- Verify **SDMMC2** for the 64GB eMMC 5.1 interface.
- Verify **XSPI** assignment for the Quad-SPI W25Q256JV NOR flash (3.3V IO bank).

## 7. PCIe / USB Shared-PHY Verification
Configure the shared 5 Gbit/s high-speed PHY:
- Allocate to **PCIe Gen2 x1** for the M.2 Key-M Slot.
- Verify fallback to **USB 2.0 High-Speed** for the Type-C port.

## 8. Ethernet / MIPI / CAN / Low-Speed IO Verification
- **Ethernet:** Allocate pins for dual Gigabit Ethernet MACs (RGMII 1.8V to DP83867 PHYs).
- **MIPI:** Assign MIPI-CSI (Camera) and MIPI-DSI (Display) to standard FFC connectors. Assign 24-bit RGB to the Sil9022A HDMI Bridge.
- **CAN-FD:** Verify FDCAN pin allocation for the 3x TCAN1044A transceivers.

## 9. Clock-Tree Validation
Use CubeMX to validate internal PLLs, external crystal frequencies, and clock distribution to all active peripherals.

## 10. Exported Pin Assignment Freeze
Export the final validated pinout CSV and Device Tree inputs from CubeMX. These become configuration-controlled design inputs.

## 11. Power Architecture Finalization
Analyze the voltage requirements of all verified IO banks. Select the core PMIC (e.g., **STPMIC25**) to handle power-up/power-down sequencing. Simulate thermal loads.

## 12. KiCad Schematic Capture
Translate the frozen CubeMX pin assignments, power requirements, and peripheral datasheets into formal schematics.

## 13. PCB Layout / SI
Perform layout, impedance matching, and Signal Integrity (SI) analysis. Determine the final PCB layer count based on comprehensive routing density constraints.
