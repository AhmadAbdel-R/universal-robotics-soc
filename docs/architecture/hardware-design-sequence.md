# Hardware Design Sequence (i.MX 8M Plus)

Because the SoC acts as the central hub that influences every other subsystem, the hardware schematic capture and PCB layout must follow a strict sequential order. This document outlines the step-by-step roadmap for designing the universal robotics board around the NXP i.MX 8M Plus (`MIMX8ML8CVNKZAB`).

## Phase 1: Boot, Flashing, & Debugging
Before the processor can do anything, we must ensure it can be programmed from a factory-blank state.
- **Boot Mode Strapping (DIP Switches):** Design the resistor network and a physical multi-position **DIP Switch Array** for the `BOOT_MODE` pins. This allows developers to manually flip physical switches on the board to toggle between booting from eMMC, QSPI, or forcing the SoC into USB Serial Downloader mode.
- **Serial Downloader (USB1):** Route the primary USB OTG port (`USB1`) to a Type-C connector. This is mandatory for using NXP's Universal Update Utility (UUU) to flash the board initially.
- **FTDI Debugger (Onboard JTAG/UART):** Integrate the FT2232HL chip directly on the board. Route Channel A to the Cortex-M7/A53 JTAG chain, and Channel B to the primary Linux Serial Console (UART2 or UART4). This provides immediate out-of-the-box debug access.

## Phase 2: Configuration Memory (Bootloader)
To prevent the board from being "bricked" during Linux OS updates, the primary bootloader (U-Boot/ATF) will live on a separate, highly reliable flash chip.
- **Select QSPI / Octa-SPI NOR Flash:** Choose a supported NOR flash chip (e.g., Winbond or Macronix).
- **FlexSPI Interface:** Route the FlexSPI signals from the SoC to the NOR flash.

## Phase 3: Main Memory (DDR)
The most complex and critical high-speed layout task.
- **Select Memory Standard:** Decide between LPDDR4x or LPDDR5 (LPDDR4x is generally cheaper and easier to route; LPDDR5 offers more bandwidth).
- **Memory Topology:** Implement a point-to-point topology for LPDDR4/5. 
- **Impedance & Length Matching:** Define the strict trace length matching rules (byte lanes, clock, strobes) and impedance targets (e.g., 40-ohm single-ended, 80-ohm differential).

## Phase 4: Mass Storage (eMMC)
- **Select eMMC 5.1 Chip:** Choose an industrial-grade eMMC module (e.g., 16GB or 32GB) for the Linux RootFS.
- **SDIO Routing:** Route the 8-bit eMMC data bus, clock, and command lines.

## Phase 5: High-Speed I/O
- **Networking:** Route the Gigabit Ethernet (TSN) and 10-Gigabit Ethernet MACs to appropriate PHYs.
- **Cameras:** Route MIPI-CSI interfaces for robotics vision.
- **Expansion:** Route PCIe Gen3 lanes (e.g., to an M.2 slot for NVMe or WiFi/AI accelerators).

## Phase 6: Robotics & Low-Speed I/O
- **CAN-FD:** Route CAN interfaces to transceivers for real-time motor control.
- **Serial/I2C/SPI:** Route headers for sensors, IMUs, and external microcontrollers.

## Phase 7: Power Delivery (Power Budget & PMIC)
Power is purposely designed **last**. We cannot finalize the power architecture until we have selected the RAM, eMMC, PHYs, and external IO, because their voltage levels influence the total power budget.
- **Consolidate Voltage Rails:** Analyze the voltage requirements of all selected chips (e.g., 1.8V, 3.3V) and consolidate them to reduce the BOM count (using the repeating discrete supply strategy where possible).
- **Power Budgeting & Simulation:** Calculate the maximum current draw across all rails, establish a power budget, and simulate the thermal load.
- **Core PMIC Selection:** Select the core PMIC (e.g., PCA9460) to handle the strict power-up/power-down sequencing required by the i.MX 8M Plus.
- **Decoupling:** Map out the exact placement of local decoupling capacitors for the BGA power rails.
