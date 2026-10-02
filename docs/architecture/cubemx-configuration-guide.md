# CubeMX Configuration Guide

**CLASSIFICATION: DESIGN CHOICE**

This document tracks the actual configuration established in the STM32CubeMX `.ioc` file for the universal robotics controller.

## Base Configuration

*   **PROJECT:** custom MCU/MPU project [DESIGN CHOICE]
*   **PROCESSOR:** STM32MP257F AI / 436-ball / 0.8mm package family [DESIGN CHOICE]
*   **MASTER MODE:** Cortex-A35 Master, M33 TrustZone disabled [DESIGN CHOICE]

## Memory Configuration (DDR)

*   **Type:** LPDDR4 [DESIGN CHOICE]
*   **Width:** 32-bit [DESIGN CHOICE]
*   **Density:** 16-Gbit density per 16-bit channel [DESIGN CHOICE]
*   **Total Capacity:** 32 Gbit total [CALCULATION]
*   **System Capacity:** 4 GB [CALCULATION]

## Clocks and Oscillators

*   **HSE (High-Speed External):** Crystal/Ceramic Resonator selected [DESIGN CHOICE]
*   **LSE (Low-Speed External):** Crystal/Ceramic Resonator selected [DESIGN CHOICE]

> **Note:** Exact oscillator numeric values are TBD - REQUIRES `.ioc` parameter verification. Do not claim exact numeric values unless confirmed by the `.ioc` configuration.

## CubeMX Screen Layout Overview

The STM32CubeMX interface is structured logically to aid in MPU configuration:

*   **LEFT:** Peripherals / Contexts (Resource selection and assignment to A35/M33) [THEORY]
*   **MIDDLE:** Configuration (Detailed peripheral parameters, DMA, NVIC) [THEORY]
*   **RIGHT:** BGA Pins (Visual layout of the physical package and pin muxing) [THEORY]
*   **RIF:** Ownership/Security (Resource Isolation Framework configuration) [THEORY]
*   **CLOCK:** Clock Tree (PLLs, dividers, and clock routing) [THEORY]

## CubeMX Resource Continuation Order

To ensure a systematic bring-up and configuration process, resources should be configured in the following order [DESIGN CHOICE]:

1.  Clocks
2.  DDR verification
3.  Boot
4.  eMMC
5.  XSPI
6.  PCIe / COMBOPHY
7.  USB
8.  Ethernet
9.  CSI
10. DSI
11. Wi-Fi
12. Bluetooth
13. CAN
14. IMU
15. sensor SPI
16. ESC timers
17. encoder timer
18. ELRS
19. GNSS/PPS
20. STEP/DIR
21. RS-485
22. IO-Link
23. ADC
24. industrial GPIO
25. debug
26. RIF
27. voltage-domain review
28. final clocks
29. pin export

**CRITICAL RULE:** Keep the `.ioc` file under source control. Do NOT commit fake results or unverified pin assignments.
