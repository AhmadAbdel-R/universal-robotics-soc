# Hardware Design Sequence (i.MX 95)

Because the SoC acts as the central hub that influences every other subsystem, the hardware schematic capture and PCB layout must follow a strict sequential order. This document outlines the step-by-step roadmap for designing the universal robotics board around the NXP i.MX 95 (`MIMX9536CVZXNAC`).

## Phase 1: Boot, Flashing, & Debugging
Before the processor can do anything, we must ensure it can be programmed from a factory-blank state.
- **Boot Mode Strapping:** Design the resistor network (pull-ups/pull-downs) and physical DIP switches for the `BOOT_MODE` pins. This defines whether the SoC boots from eMMC, QSPI, or falls back to USB.
- **Serial Downloader (USB1):** Route the primary USB OTG port (USB1) to a Type-C connector. This is mandatory for using NXP's Universal Update Utility (UUU) to flash the board initially.
- **JTAG / SWD Interface:** Route the JTAG boundary scan pins to a standard 10-pin Arm Cortex Debug header for bare-metal debugging of the real-time M7/M33 cores.

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
- **Core PMIC Selection:** Select the core PMIC (e.g., PCA9451A) to handle the strict power-up/power-down sequencing required by the i.MX 95.
- **Decoupling:** Map out the exact placement of local decoupling capacitors for the BGA power rails.
