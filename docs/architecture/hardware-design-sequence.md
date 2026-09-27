# Hardware Design Sequence (STM32MP257)

Because the SoC acts as the central hub that influences every other subsystem, the hardware schematic capture and PCB layout must follow a strict sequential order. This document outlines the step-by-step roadmap for designing the universal robotics board around the NXP STM32MP257 (`STM32MP257`).

## Phase 1: Boot, Flashing, & Debugging
Before the processor can do anything, we must ensure it can be programmed from a factory-blank state.
- **Boot Mode Strapping (DIP Switches):** Design the resistor network and a physical multi-position **DIP Switch Array** for the `BOOT_MODE` pins. This allows developers to manually flip physical switches on the board to toggle between booting from eMMC, QSPI, or forcing the SoC into USB Serial Downloader mode.
- **Serial Downloader (USB1):** Route the primary USB OTG port (`USB1`) to a Type-C connector. This is mandatory for using NXP's Universal Update Utility (UUU) to flash the board initially.
- **FTDI Debugger (Onboard JTAG/UART):** Integrate the FT2232HL chip directly on the board. Route Channel A to the Cortex-M7/A53 JTAG chain, and Channel B to the primary Linux Serial Console (UART2 or UART4). This provides immediate out-of-the-box debug access.

## Phase 2: Configuration Memory (Bootloader)
To prevent the board from being "bricked" during Linux OS updates, the primary bootloader (U-Boot/ATF) will live on a separate, highly reliable flash chip.
- **Select QSPI / Octa-SPI NOR Flash:** Choose a supported NOR flash chip (e.g., Winbond or Macronix).
- **FlexSPI Interface:** Route the FlexSPI signals from the SoC to the NOR flash.

## Phase 3: Main Memory (LPDDR4)
The most complex and critical high-speed layout task.
- **Select Memory Standard:** The STM32MP257 utilizes LPDDR4 at 3200 MT/s.
- **Memory Topology:** Implement a **Point-to-Point topology** using a single 32-bit RAM chip. Do NOT use a Fly-by topology with dual 16-bit chips to preserve the 6-layer stackup simplicity.
- **Impedance & Length Matching:** Define the strict trace length matching rules (byte lanes, clock, strobes) and impedance targets (40-ohm SE, 80-ohm Diff).

## Phase 4: Mass Storage (eMMC)
- **Select eMMC 5.1 Chip:** Choose a massive high-capacity eMMC module (**64GB, 128GB, or 256GB**) for the Linux OS and data logging. This is strictly required because the PCIe lane is reserved for M.2 expansion rather than a hardwired NVMe SSD.
- **SDIO Routing:** Route the 8-bit eMMC data bus, clock, and command lines.

## Phase 5: High-Speed I/O
- **Networking (Dual Ethernet):** Route the two Gigabit Ethernet MACs (one with TSN) to RGMII PHYs (e.g., KSZ9131 or RTL8211F). Route the PHYs to standard **RJ45 connectors with integrated magnetics** for cost-effective, standard connectivity.
- **Expansion (M.2 PCIe):** Route the single PCIe Gen3 lane to an **M.2 Key-M Slot**. This preserves modularity, allowing users to plug in NVMe SSDs, Coral Edge TPUs, or M.2 WiFi 6 cards as needed.
- **Cameras:** Route the Dual MIPI-CSI interfaces to standard 15-pin FFC connectors or high-speed board-to-board connectors for robotics vision (e.g., IMX219 or IMX477 camera modules).

## Phase 6: Robotics & Low-Speed I/O
- **CAN-FD:** Route CAN interfaces to transceivers for real-time motor control.
- **Serial/I2C/SPI:** Route headers for sensors, IMUs, and external microcontrollers.

## Phase 7: Power Delivery (Power Budget & PMIC)
Power is purposely designed **last**. We cannot finalize the power architecture until we have selected the RAM, eMMC, PHYs, and external IO, because their voltage levels influence the total power budget.
- **Consolidate Voltage Rails:** Analyze the voltage requirements of all selected chips (e.g., 1.8V, 3.3V) and consolidate them to reduce the BOM count (using the repeating discrete supply strategy where possible).
- **Power Budgeting & Simulation:** Calculate the maximum current draw across all rails, establish a power budget, and simulate the thermal load.
- **Core PMIC Selection:** Select the core PMIC (e.g., STPMIC2) to handle the strict power-up/power-down sequencing required by the STM32MP257.
- **Decoupling:** Map out the exact placement of local decoupling capacitors for the BGA power rails.
