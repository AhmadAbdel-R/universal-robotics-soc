# Peripheral Engineering Documentation

## 1. LPDDR4
- **Purpose, Use cases:** Main system memory for Cortex-A35 OS and high-bandwidth processing [DESIGN CHOICE]
- **Selected component, Why selected:** Micron MT53E1G32D2FW, required for high density/bandwidth [DESIGN CHOICE]
- **Bus, Bus speed, Voltage:** 32-bit point-to-point, Speed TBD, Voltage TBD [TBD - REQUIRES DATASHEET]
- **Owner:** A35 owner [DESIGN CHOICE]
- **DMA, Interrupt:** TBD
- **Connector:** N/A (On-board) [DESIGN CHOICE]
- **Protection, Termination:** On-die termination (ODT) [THEORY]
- **Power, Placement, Routing, Noise concerns:** Close to MPU, strict length matching, solid reference planes [THEORY]
- **CubeMX resource:** TBD - REQUIRES CUBEMX PIN ALLOCATION
- **Linux support, M33 support:** Supported in TF-A / U-Boot / Linux [THEORY]
- **Bring-up method, Test procedure:** TF-A DDR initialization, memory stress test [THEORY]

## 2. eMMC
- **Purpose, Use cases:** Main non-volatile storage for OS and application data [DESIGN CHOICE]
- **Selected component, Why selected:** FORESEE FEMDRW064G [DESIGN CHOICE]
- **Bus, Bus speed, Voltage:** SDMMC, speed TBD, voltage TBD [TBD]
- **Owner:** A35 owner [DESIGN CHOICE]
- **DMA, Interrupt:** TBD
- **Connector:** N/A (On-board) [DESIGN CHOICE]
- **Protection, Termination:** Series termination resistors [THEORY]
- **Power, Placement, Routing, Noise concerns:** Length matched SDMMC bus, 50-ohm impedance [THEORY]
- **CubeMX resource:** TBD - REQUIRES CUBEMX PIN ALLOCATION
- **Linux support, M33 support:** Standard Linux block device [THEORY]
- **Bring-up method, Test procedure:** U-Boot mmc info, Linux badblocks [THEORY]

## 3. XSPI NOR
- **Purpose, Use cases:** Fast boot flash [DESIGN CHOICE]
- **Selected component, Why selected:** Winbond W25Q256JVFIQ [DESIGN CHOICE]
- **Bus, Bus speed, Voltage:** XSPI/QSPI, speed/voltage TBD [TBD]
- **Owner:** System/Bootloader [DESIGN CHOICE]
- **DMA, Interrupt:** TBD
- **Connector:** N/A (On-board) [DESIGN CHOICE]
- **Protection, Termination:** TBD
- **Power, Placement, Routing, Noise concerns:** Close to MPU, length matched clock/data [THEORY]
- **CubeMX resource:** TBD - REQUIRES CUBEMX PIN ALLOCATION
- **Linux support, M33 support:** MTD subsystem in Linux [THEORY]
- **Bring-up method, Test procedure:** U-Boot sf probe, read/write/erase tests [THEORY]

## 4. PCIe Gen2 x1
- **Purpose, Use cases:** High-speed expansion [DESIGN CHOICE]
- **Selected component, Why selected:** M.2 Key M [DESIGN CHOICE]
- **Bus, Bus speed, Voltage:** PCIe Gen2, 5 GT/s [DATASHEET REQUIREMENT]
- **Owner:** A35 owner [DESIGN CHOICE]
- **DMA, Interrupt:** TBD
- **Connector:** M.2 Key M [DESIGN CHOICE]
- **Protection, Termination:** AC coupling capacitors on TX lines [DATASHEET REQUIREMENT]
- **Power, Placement, Routing, Noise concerns:** 85/100-ohm diff routing, COMBOPHY shared with USB3 [THEORY]
- **CubeMX resource:** TBD - REQUIRES CUBEMX PIN ALLOCATION
- **Linux support, M33 support:** Linux PCI subsystem [THEORY]
- **Bring-up method, Test procedure:** lspci, test with NVMe SSD [THEORY]

## 5. USB 2.0 HS
- **Purpose, Use cases:** Device/Host connectivity [DESIGN CHOICE]
- **Selected component, Why selected:** Type-C [DESIGN CHOICE]
- **Bus, Bus speed, Voltage:** USB2 OTG, 480 Mbps, 5V VBUS [DATASHEET REQUIREMENT]
- **Owner:** A35 owner [DESIGN CHOICE]
- **DMA, Interrupt:** TBD
- **Connector:** USB Type-C [DESIGN CHOICE]
- **Protection, Termination:** ESD protection array, common-mode choke [THEORY]
- **Power, Placement, Routing, Noise concerns:** 90-ohm diff routing, isolated from high-current paths [THEORY]
- **CubeMX resource:** TBD - REQUIRES CUBEMX PIN ALLOCATION
- **Linux support, M33 support:** Linux USB gadget/host [THEORY]
- **Bring-up method, Test procedure:** lsusb, file transfer [THEORY]

## 6. Gigabit Ethernet 1
- **Purpose, Use cases:** High-speed network [DESIGN CHOICE]
- **Selected component, Why selected:** DP83867IRRGZR [DESIGN CHOICE]
- **Bus, Bus speed, Voltage:** RGMII, 1.8V IO [DESIGN CHOICE]
- **Owner:** A35 owner [DESIGN CHOICE]
- **DMA, Interrupt:** TBD
- **Connector:** TBD [TBD]
- **Protection, Termination:** Magnetics, ESD protection [THEORY]
- **Power, Placement, Routing, Noise concerns:** Length match RGMII, separate analog PHY power [THEORY]
- **CubeMX resource:** TBD - REQUIRES CUBEMX PIN ALLOCATION
- **Linux support, M33 support:** Linux netdev [THEORY]
- **Bring-up method, Test procedure:** ping, iperf3 [THEORY]

## 7. Gigabit Ethernet 2
- **Purpose, Use cases:** Secondary network / daisy chaining [DESIGN CHOICE]
- **Selected component, Why selected:** DP83867IRRGZR [DESIGN CHOICE]
- **Bus, Bus speed, Voltage:** RGMII, 1.8V IO [DESIGN CHOICE]
- **Owner:** A35 owner [DESIGN CHOICE]
- **DMA, Interrupt:** TBD
- **Connector:** TBD [TBD]
- **Protection, Termination:** Magnetics, ESD protection [THEORY]
- **Power, Placement, Routing, Noise concerns:** Length match RGMII, separate analog PHY power [THEORY]
- **CubeMX resource:** TBD - REQUIRES CUBEMX PIN ALLOCATION
- **Linux support, M33 support:** Linux netdev [THEORY]
- **Bring-up method, Test procedure:** ping, iperf3 [THEORY]

## 8. MIPI CSI
- **Purpose, Use cases:** Camera input for AI/vision [DESIGN CHOICE]
- **Selected component, Why selected:** RPi Camera FFC [DESIGN CHOICE]
- **Bus, Bus speed, Voltage:** MIPI CSI-2, speed TBD [TBD]
- **Owner:** A35 owner [DESIGN CHOICE]
- **DMA, Interrupt:** TBD
- **Connector:** 15-pin/22-pin FFC [DESIGN CHOICE]
- **Protection, Termination:** ESD protection [THEORY]
- **Power, Placement, Routing, Noise concerns:** 100-ohm diff routing, intra-pair length matching [THEORY]
- **CubeMX resource:** TBD - REQUIRES CUBEMX PIN ALLOCATION
- **Linux support, M33 support:** V4L2 [THEORY]
- **Bring-up method, Test procedure:** v4l2-ctl stream capture [THEORY]

## 9. MIPI DSI
- **Purpose, Use cases:** Display output [DESIGN CHOICE]
- **Selected component, Why selected:** RPi Display FFC [DESIGN CHOICE]
- **Bus, Bus speed, Voltage:** MIPI DSI, speed TBD [TBD]
- **Owner:** A35 owner [DESIGN CHOICE]
- **DMA, Interrupt:** TBD
- **Connector:** 15-pin/22-pin FFC [DESIGN CHOICE]
- **Protection, Termination:** ESD protection [THEORY]
- **Power, Placement, Routing, Noise concerns:** 100-ohm diff routing, intra-pair length matching [THEORY]
- **CubeMX resource:** TBD - REQUIRES CUBEMX PIN ALLOCATION
- **Linux support, M33 support:** DRM/KMS [THEORY]
- **Bring-up method, Test procedure:** modetest, display pattern [THEORY]

## 10. HDMI
- **Purpose, Use cases:** External monitor output [DESIGN CHOICE]
- **Selected component, Why selected:** Sil9022A bridge from DSI/RGB [DESIGN CHOICE]
- **Bus, Bus speed, Voltage:** RGB/DSI to HDMI, speed TBD [TBD]
- **Owner:** A35 owner [DESIGN CHOICE]
- **DMA, Interrupt:** TBD
- **Connector:** HDMI Type-A [DESIGN CHOICE]
- **Protection, Termination:** Dedicated HDMI ESD protection [THEORY]
- **Power, Placement, Routing, Noise concerns:** 100-ohm diff routing for TMDS [THEORY]
- **CubeMX resource:** TBD - REQUIRES CUBEMX PIN ALLOCATION
- **Linux support, M33 support:** DRM/KMS [THEORY]
- **Bring-up method, Test procedure:** monitor detection, EDID read [THEORY]

## 11. Wi-Fi
- **Purpose, Use cases:** Wireless networking [DESIGN CHOICE]
- **Selected component, Why selected:** AP6256/Murata [DESIGN CHOICE]
- **Bus, Bus speed, Voltage:** SDIO, speed TBD [TBD]
- **Owner:** A35 owner [DESIGN CHOICE]
- **DMA, Interrupt:** TBD
- **Connector:** U.FL or on-board antenna [DESIGN CHOICE]
- **Protection, Termination:** TBD
- **Power, Placement, Routing, Noise concerns:** RF impedance control (50-ohm), isolated from digital noise [THEORY]
- **CubeMX resource:** TBD - REQUIRES CUBEMX PIN ALLOCATION
- **Linux support, M33 support:** brcmfmac [THEORY]
- **Bring-up method, Test procedure:** ifconfig, wpa_supplicant, ping [THEORY]

## 12. Bluetooth
- **Purpose, Use cases:** Wireless peripheral connection [DESIGN CHOICE]
- **Selected component, Why selected:** AP6256/Murata [DESIGN CHOICE]
- **Bus, Bus speed, Voltage:** UART HCI, speed TBD [TBD]
- **Owner:** A35 owner [DESIGN CHOICE]
- **DMA, Interrupt:** TBD
- **Connector:** Shared with Wi-Fi [DESIGN CHOICE]
- **Protection, Termination:** TBD
- **Power, Placement, Routing, Noise concerns:** Shared RF path with Wi-Fi [THEORY]
- **CubeMX resource:** TBD - REQUIRES CUBEMX PIN ALLOCATION
- **Linux support, M33 support:** hciattach / BlueZ [THEORY]
- **Bring-up method, Test procedure:** hcitool, hciconfig [THEORY]

## 13. CAN-FD 1
- **Purpose, Use cases:** Real-time vehicle/robotics bus [DESIGN CHOICE]
- **Selected component, Why selected:** TCAN1044AVDRQ1 [DESIGN CHOICE]
- **Bus, Bus speed, Voltage:** FDCAN, 1.8V VIO [DESIGN CHOICE]
- **Owner:** M33 owner [DESIGN CHOICE]
- **DMA, Interrupt:** TBD
- **Connector:** TBD
- **Protection, Termination:** ESD, 120-ohm optional [THEORY]
- **Power, Placement, Routing, Noise concerns:** Diff routing for CANH/CANL [THEORY]
- **CubeMX resource:** TBD - REQUIRES CUBEMX PIN ALLOCATION
- **Linux support, M33 support:** M33 baremetal/RTOS driver [THEORY]
- **Bring-up method, Test procedure:** loopback test, send/receive frames [THEORY]

## 14. CAN-FD 2
- **Purpose, Use cases:** Real-time vehicle/robotics bus [DESIGN CHOICE]
- **Selected component, Why selected:** TCAN1044AVDRQ1 [DESIGN CHOICE]
- **Bus, Bus speed, Voltage:** FDCAN [DESIGN CHOICE]
- **Owner:** M33 owner [DESIGN CHOICE]
- **DMA, Interrupt:** TBD
- **Connector:** TBD
- **Protection, Termination:** ESD, 120-ohm optional [THEORY]
- **Power, Placement, Routing, Noise concerns:** Diff routing for CANH/CANL [THEORY]
- **CubeMX resource:** TBD - REQUIRES CUBEMX PIN ALLOCATION
- **Linux support, M33 support:** M33 baremetal/RTOS driver [THEORY]
- **Bring-up method, Test procedure:** loopback test, send/receive frames [THEORY]

## 15. CAN-FD 3
- **Purpose, Use cases:** Isolated real-time vehicle/robotics bus (optional) [DESIGN CHOICE]
- **Selected component, Why selected:** TCAN1044AVDRQ1 [DESIGN CHOICE]
- **Bus, Bus speed, Voltage:** FDCAN [DESIGN CHOICE]
- **Owner:** M33 owner [DESIGN CHOICE]
- **DMA, Interrupt:** TBD
- **Connector:** TBD
- **Protection, Termination:** Isolation barrier, ESD, 120-ohm optional [THEORY]
- **Power, Placement, Routing, Noise concerns:** Maintain isolation gap [THEORY]
- **CubeMX resource:** TBD - REQUIRES CUBEMX PIN ALLOCATION
- **Linux support, M33 support:** M33 baremetal/RTOS driver [THEORY]
- **Bring-up method, Test procedure:** loopback test, send/receive frames [THEORY]

## 16. IMU
- **Purpose, Use cases:** Inertial measurement for stabilization/navigation [DESIGN CHOICE]
- **Selected component, Why selected:** ICM-42688-P [DESIGN CHOICE]
- **Bus, Bus speed, Voltage:** dedicated SPI, 3V3_SENSOR [DESIGN CHOICE]
- **Owner:** M33 owner [DESIGN CHOICE]
- **DMA, Interrupt:** TBD
- **Connector:** N/A (On-board) [DESIGN CHOICE]
- **Protection, Termination:** TBD
- **Power, Placement, Routing, Noise concerns:** Isolate from thermal gradients and mechanical stress [THEORY]
- **CubeMX resource:** TBD - REQUIRES CUBEMX PIN ALLOCATION
- **Linux support, M33 support:** M33 RTOS driver [THEORY]
- **Bring-up method, Test procedure:** Read WHO_AM_I, raw data stream [THEORY]

## 17. Magnetometer
- **Purpose, Use cases:** Heading estimation [DESIGN CHOICE]
- **Selected component, Why selected:** MMC5983MA [DESIGN CHOICE]
- **Bus, Bus speed, Voltage:** secondary SPI, 3V3_SENSOR [DESIGN CHOICE]
- **Owner:** M33 owner [DESIGN CHOICE]
- **DMA, Interrupt:** TBD
- **Connector:** N/A (On-board) [DESIGN CHOICE]
- **Protection, Termination:** TBD
- **Power, Placement, Routing, Noise concerns:** Keep away from high current paths and ferrous metals [THEORY]
- **CubeMX resource:** TBD - REQUIRES CUBEMX PIN ALLOCATION
- **Linux support, M33 support:** M33 RTOS driver [THEORY]
- **Bring-up method, Test procedure:** Read device ID, stream data [THEORY]

## 18. Barometer
- **Purpose, Use cases:** Altitude estimation [DESIGN CHOICE]
- **Selected component, Why selected:** BMP581 [DESIGN CHOICE]
- **Bus, Bus speed, Voltage:** secondary SPI, 3V3_SENSOR [DESIGN CHOICE]
- **Owner:** M33 owner [DESIGN CHOICE]
- **DMA, Interrupt:** TBD
- **Connector:** N/A (On-board) [DESIGN CHOICE]
- **Protection, Termination:** TBD
- **Power, Placement, Routing, Noise concerns:** Avoid light exposure and draft [THEORY]
- **CubeMX resource:** TBD - REQUIRES CUBEMX PIN ALLOCATION
- **Linux support, M33 support:** M33 RTOS driver [THEORY]
- **Bring-up method, Test procedure:** Read device ID, read pressure/temp [THEORY]

## 19. ESC Control
- **Purpose, Use cases:** Motor control for UAV/Robotics [DESIGN CHOICE]
- **Selected component, Why selected:** 4x PWM/DShot outputs [DESIGN CHOICE]
- **Bus, Bus speed, Voltage:** timer+DMA, voltage TBD [DESIGN CHOICE]
- **Owner:** M33 owner [DESIGN CHOICE]
- **DMA, Interrupt:** TBD
- **Connector:** Standard 0.1" headers or JST [DESIGN CHOICE]
- **Protection, Termination:** Series resistors [THEORY]
- **Power, Placement, Routing, Noise concerns:** TBD
- **CubeMX resource:** TBD - REQUIRES CUBEMX PIN ALLOCATION
- **Linux support, M33 support:** M33 timer/DMA driver [THEORY]
- **Bring-up method, Test procedure:** Scope outputs, motor spin test [THEORY]

## 20. ExpressLRS/CRSF
- **Purpose, Use cases:** Long-range RC receiver [DESIGN CHOICE]
- **Selected component, Why selected:** CRSF protocol compatible [DESIGN CHOICE]
- **Bus, Bus speed, Voltage:** UART >420kbaud [DESIGN CHOICE]
- **Owner:** M33 owner [DESIGN CHOICE]
- **DMA, Interrupt:** TBD
- **Connector:** TBD
- **Protection, Termination:** TBD
- **Power, Placement, Routing, Noise concerns:** TBD
- **CubeMX resource:** TBD - REQUIRES CUBEMX PIN ALLOCATION
- **Linux support, M33 support:** M33 UART driver [THEORY]
- **Bring-up method, Test procedure:** Receive RC channels [THEORY]

## 21. GNSS
- **Purpose, Use cases:** Global positioning and precise timing [DESIGN CHOICE]
- **Selected component, Why selected:** TBD [TBD]
- **Bus, Bus speed, Voltage:** UART + PPS timer input [DESIGN CHOICE]
- **Owner:** M33 owner [DESIGN CHOICE]
- **DMA, Interrupt:** TBD
- **Connector:** TBD
- **Protection, Termination:** TBD
- **Power, Placement, Routing, Noise concerns:** PPS needs clean routing to timer input [THEORY]
- **CubeMX resource:** TBD - REQUIRES CUBEMX PIN ALLOCATION
- **Linux support, M33 support:** M33 UART parser [THEORY]
- **Bring-up method, Test procedure:** NMEA parsing, PPS scope verify [THEORY]

## 22. Encoder
- **Purpose, Use cases:** Motor/Joint position feedback [DESIGN CHOICE]
- **Selected component, Why selected:** TBD [TBD]
- **Bus, Bus speed, Voltage:** A/B/Z differential, timer hardware quadrature [DESIGN CHOICE]
- **Owner:** M33 owner [DESIGN CHOICE]
- **DMA, Interrupt:** TBD
- **Connector:** TBD
- **Protection, Termination:** Differential receivers, ESD [THEORY]
- **Power, Placement, Routing, Noise concerns:** TBD
- **CubeMX resource:** TBD - REQUIRES CUBEMX PIN ALLOCATION
- **Linux support, M33 support:** M33 timer quadrature mode [THEORY]
- **Bring-up method, Test procedure:** Rotate encoder, read counter [THEORY]

## 23. STEP/DIR
- **Purpose, Use cases:** Stepper motor driver control [DESIGN CHOICE]
- **Selected component, Why selected:** TBD [TBD]
- **Bus, Bus speed, Voltage:** GPIO/timer outputs [DESIGN CHOICE]
- **Owner:** M33 owner [DESIGN CHOICE]
- **DMA, Interrupt:** TBD
- **Connector:** TBD
- **Protection, Termination:** TBD
- **Power, Placement, Routing, Noise concerns:** TBD
- **CubeMX resource:** TBD - REQUIRES CUBEMX PIN ALLOCATION
- **Linux support, M33 support:** M33 GPIO/Timer [THEORY]
- **Bring-up method, Test procedure:** Scope verify frequency [THEORY]

## 24. RS-485
- **Purpose, Use cases:** Industrial bus [DESIGN CHOICE]
- **Selected component, Why selected:** THVD1450 [DESIGN CHOICE]
- **Bus, Bus speed, Voltage:** UART + DE/RE [DESIGN CHOICE]
- **Owner:** A35 or M33 TBD [DESIGN CHOICE]
- **DMA, Interrupt:** TBD
- **Connector:** TBD
- **Protection, Termination:** 120-ohm optional, TVS [THEORY]
- **Power, Placement, Routing, Noise concerns:** Diff routing [THEORY]
- **CubeMX resource:** TBD - REQUIRES CUBEMX PIN ALLOCATION
- **Linux support, M33 support:** TBD
- **Bring-up method, Test procedure:** loopback, external master test [THEORY]

## 25. IO-Link
- **Purpose, Use cases:** Industrial sensor communication [DESIGN CHOICE]
- **Selected component, Why selected:** L6360 [DESIGN CHOICE]
- **Bus, Bus speed, Voltage:** UART/control [DESIGN CHOICE]
- **Owner:** A35 or M33 TBD [DESIGN CHOICE]
- **DMA, Interrupt:** TBD
- **Connector:** TBD
- **Protection, Termination:** Built into L6360 [DATASHEET REQUIREMENT]
- **Power, Placement, Routing, Noise concerns:** TBD
- **CubeMX resource:** TBD - REQUIRES CUBEMX PIN ALLOCATION
- **Linux support, M33 support:** TBD
- **Bring-up method, Test procedure:** TBD

## 26. 24V Digital Inputs
- **Purpose, Use cases:** Industrial state sensing [DESIGN CHOICE]
- **Selected component, Why selected:** TBD [TBD]
- **Bus, Bus speed, Voltage:** Industrial IEC 61131-2 compatible [DATASHEET REQUIREMENT]
- **Owner:** TBD [DESIGN CHOICE]
- **DMA, Interrupt:** TBD
- **Connector:** TBD
- **Protection, Termination:** Opto-isolation or digital isolators [THEORY]
- **Power, Placement, Routing, Noise concerns:** TBD
- **CubeMX resource:** TBD - REQUIRES CUBEMX PIN ALLOCATION
- **Linux support, M33 support:** TBD
- **Bring-up method, Test procedure:** Apply 24V, verify logic state [THEORY]

## 27. 24V Actuator Outputs
- **Purpose, Use cases:** Industrial load driving [DESIGN CHOICE]
- **Selected component, Why selected:** High-side switch protected [DESIGN CHOICE]
- **Bus, Bus speed, Voltage:** 24V [DESIGN CHOICE]
- **Owner:** TBD [DESIGN CHOICE]
- **DMA, Interrupt:** TBD
- **Connector:** TBD
- **Protection, Termination:** Short-circuit, thermal protection [THEORY]
- **Power, Placement, Routing, Noise concerns:** High current routing [THEORY]
- **CubeMX resource:** TBD - REQUIRES CUBEMX PIN ALLOCATION
- **Linux support, M33 support:** TBD
- **Bring-up method, Test procedure:** Drive load, check fault flags [THEORY]

## 28. FTDI Debug
- **Purpose, Use cases:** Firmware flashing, console, debug [DESIGN CHOICE]
- **Selected component, Why selected:** FT2232HL [DESIGN CHOICE]
- **Bus, Bus speed, Voltage:** JTAG + UART [DESIGN CHOICE]
- **Owner:** System [DESIGN CHOICE]
- **DMA, Interrupt:** N/A
- **Connector:** USB [DESIGN CHOICE]
- **Protection, Termination:** ESD [THEORY]
- **Power, Placement, Routing, Noise concerns:** Length matched JTAG optional [THEORY]
- **CubeMX resource:** TBD - REQUIRES CUBEMX PIN ALLOCATION
- **Linux support, M33 support:** OpenOCD support [THEORY]
- **Bring-up method, Test procedure:** connect OpenOCD, read IDCODE [THEORY]

## 29. ADC Channels
- **Purpose, Use cases:** Battery and current sensing [DESIGN CHOICE]
- **Selected component, Why selected:** Internal STM32 ADC [DESIGN CHOICE]
- **Bus, Bus speed, Voltage:** Analog [DESIGN CHOICE]
- **Owner:** TBD [DESIGN CHOICE]
- **DMA, Interrupt:** TBD
- **Connector:** N/A
- **Protection, Termination:** Low-pass filter [THEORY]
- **Power, Placement, Routing, Noise concerns:** Keep analog traces away from digital [THEORY]
- **CubeMX resource:** TBD - REQUIRES CUBEMX PIN ALLOCATION
- **Linux support, M33 support:** TBD
- **Bring-up method, Test procedure:** Apply known voltage, read value [THEORY]

## 30. Industrial Expansion
- **Purpose, Use cases:** Resolver, load cell, analog daughterboards [DESIGN CHOICE]
- **Selected component, Why selected:** TBD [TBD]
- **Bus, Bus speed, Voltage:** TBD [TBD]
- **Owner:** TBD [DESIGN CHOICE]
- **DMA, Interrupt:** TBD
- **Connector:** TBD
- **Protection, Termination:** TBD
- **Power, Placement, Routing, Noise concerns:** TBD
- **CubeMX resource:** TBD - REQUIRES CUBEMX PIN ALLOCATION
- **Linux support, M33 support:** TBD
- **Bring-up method, Test procedure:** TBD
