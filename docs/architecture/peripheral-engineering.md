# Peripheral Engineering Documentation

This document records the exact physical pin allocations, peripheral instances, bus topologies, context ownership, and hardware interface specifications established for the Universal Robotics SoC platform.

---

## 1. LPDDR4 Memory
- **Purpose, Use cases:** Main system memory for Cortex-A35 Linux OS, ROS 2, computer vision, and NPU inference models.
- **Selected component, Why selected:** Micron MT53E1G32D2FW (4 GB, 32-bit point-to-point, single package).
- **Bus, Bus speed, Voltage:** 32-bit point-to-point (dual 16-bit channels), 600 MHz clock (1200 MT/s), 1.1 V VDD2 / 0.6 V VDDQ.
- **Owner:** Cortex-A35 (TF-A BL2 initialization, U-Boot, Linux).
- **CubeMX resource:** `DDR_CTRL_PHY` (clocked via PLL2 @ 600 MHz: HSE 40 MHz, FBDIV=30, POSTDIV2=2).
- **Hardware Pins:** Dedicated high-density LPDDR4 BGA balls.
- **Protection, Termination:** Dynamic On-Die Termination (ODT).
- **Critical Layout:** Strict fly-by/point-to-point length matching, 40 Ω single-ended / 80 Ω differential impedance, uninterrupted GND reference planes.

## 2. eMMC Storage
- **Purpose, Use cases:** Primary non-volatile storage for bootloader, Linux OS kernel, device tree, and application rootfs.
- **Selected component, Why selected:** FORESEE FEMDRW064G (64 GB eMMC 5.1).
- **Bus, Bus speed, Voltage:** 8-bit wide MMC bus, HS200/HS400 mode target, 1.8 V / 3.3 V dual supply.
- **Owner:** Cortex-A35 (`BootROMA35`, `CortexA35NSSSBL` U-Boot, `CortexA35NSOS` Linux, patched `CortexA35SFSBLA` TF-A).
- **CubeMX resource:** `SDMMC2`.
- **Hardware Pins:**
  - `PE6`: SDMMC2_D6 (AF12)
  - `PE7`: SDMMC2_D7 (AF12)
  - `PE8`: SDMMC2_D2 (AF12)
  - `PE9`: SDMMC2_D5 (AF12)
  - `PE10`: SDMMC2_D4 (AF12)
  - `PE11`: SDMMC2_D1 (AF12)
  - `PE12`: SDMMC2_D3 (AF12)
  - `PE13`: SDMMC2_D0 (AF12)
  - `PE14`: SDMMC2_CK (AF12)
  - `PE15`: SDMMC2_CMD (AF12)
- **Protection, Termination:** Series damping resistors on clock/data lines (22 Ω near MPU).
- **Bring-up method:** TF-A BL2 eMMC probe, U-Boot `mmc dev 0; mmc info`, Linux `ext4` filesystem mount.

## 3. XSPI NOR Flash
- **Purpose, Use cases:** Secondary recovery firmware, board configuration parameters, secure boot keystore backup.
- **Selected component, Why selected:** Winbond W25Q256JVFIQ (32 MB Quad-SPI NOR Flash).
- **Bus, Bus speed, Voltage:** Quad-SPI Mode (1-4-4), up to 133 MHz, 1.8 V / 3.3 V.
- **Owner:** Cortex-A35 (`BootROMA35`, `CortexA35SFSBLA`, `CortexA35NSSSBL`).
- **CubeMX resource:** `OCTOSPI1` via `OCTOSPIM`.
- **Hardware Pins:**
  - `PD0`: OCTOSPIM_P1_CLK (AF10)
  - `PD4`: OCTOSPIM_P1_IO0 (AF10)
  - `PD5`: OCTOSPIM_P1_IO1 (AF10)
  - `PD6`: OCTOSPIM_P1_IO2 (AF10)
  - `PD7`: OCTOSPIM_P1_IO3 (AF10)
  - CS: Managed via OCTOSPI controller.

## 4. PCIe Gen2 x1 Expansion
- **Purpose, Use cases:** High-speed NVMe SSD storage or external edge AI accelerator (e.g. Google Coral TPU, Hailo-8).
- **Selected component, Why selected:** M.2 Key-M socket (form factor 2242/2280).
- **Bus, Bus speed, Voltage:** PCIe Gen2 x1 (5.0 GT/s per direction), 3.3 V M.2 rail.
- **Owner:** Cortex-A35 (`CortexA35NSOS` Linux).
- **CubeMX resource:** `PCIE` (Root Complex) + `COMBOPHY`.
- **Hardware Pins:**
  - `COMBOPHY_RX1N`, `COMBOPHY_RX1P`: PCIe RX differential pair.
  - `COMBOPHY_TX1N`, `COMBOPHY_TX1P`: PCIe TX differential pair.
  - `COMBOPHY_REXT`: External reference resistor calibration.
- **Hardware Note:** The shared high-speed COMBOPHY is dedicated exclusively to PCIe Gen2; USB3DR operates in USB2-only mode.

## 5. USB 2.0 High-Speed OTG (Type-C)
- **Purpose, Use cases:** Primary developer interface, STM32CubeProgrammer USB DFU recovery, USB serial console, gadget mode.
- **Selected component, Why selected:** Standard 24-pin USB Type-C connector.
- **Bus, Bus speed, Voltage:** USB 2.0 High-Speed (480 Mbps), 5 V VBUS with ESD protection.
- **Owner:** Cortex-A35 (`USB3DR` in USB2-only mode). CC logic managed by Cortex-M33 (`UCPD1`).
- **CubeMX resource:** `USB3DR` + `UCPD1`.
- **Hardware Pins:**
  - `USB3DR_DP`, `USB3DR_DM`: USB 2.0 differential data pair.
  - `USB3DR_TXRTUNE`: Tuning resistor.
  - `UCPD1_CC1`, `UCPD1_CC2`: USB Type-C Configuration Channel lines.

## 6. USB 2.0 Host Interface
- **Purpose, Use cases:** External USB peripherals (cameras, flash drives, wireless dongles).
- **Selected component, Why selected:** USB Type-A or internal header via external protected power switch.
- **Bus, Bus speed, Voltage:** USB 2.0 High-Speed (480 Mbps).
- **Owner:** Cortex-A35 (`USBH_HS` in Linux).
- **CubeMX resource:** `USBH_HS`.
- **Hardware Pins:**
  - `USBH_HS_DP`, `USBH_HS_DM`: USB 2.0 host data pair.
  - `PJ0`: USBH_HS_VBUSEN (VBUS power switch enable).
  - `PJ2`: USBH_HS_OVRCUR (Overcurrent flag input).

## 7. Gigabit Ethernet 1 (ETH1)
- **Purpose, Use cases:** Primary high-bandwidth robotics network (LiDAR, ROS 2 DDS, industrial network).
- **Selected component, Why selected:** Texas Instruments DP83867IRRGZR Gigabit Ethernet PHY (1.8 V I/O).
- **Bus, Bus speed, Voltage:** RGMII (125 MHz DDR clock), 1.8 V I/O voltage.
- **Owner:** Cortex-A35 (`CortexA35NSOS` Linux).
- **CubeMX resource:** `ETH1` (ETHSW disabled).
- **Hardware Pins (14 total):**
  - `PA9`: ETH1_MDC (AF10)
  - `PF2`: ETH1_MDIO (AF10)
  - `PA11`: ETH1_RGMII_RX_CTL (AF10)
  - `PF1`: ETH1_RGMII_RXD0 (AF10)
  - `PC2`: ETH1_RGMII_RXD1 (AF10)
  - `PH12`: ETH1_RGMII_RXD2 (AF10)
  - `PH13`: ETH1_RGMII_RXD3 (AF10)
  - `PA14`: ETH1_RGMII_RX_CLK (AF10)
  - `PA13`: ETH1_RGMII_TX_CTL (AF10)
  - `PA15`: ETH1_RGMII_TXD0 (AF10)
  - `PC1`: ETH1_RGMII_TXD1 (AF10)
  - `PH10`: ETH1_RGMII_TXD2 (AF10)
  - `PH11`: ETH1_RGMII_TXD3 (AF10)
  - `PC0`: ETH1_RGMII_GTX_CLK (AF12)

## 8. Gigabit Ethernet 2 (ETH2)
- **Purpose, Use cases:** Secondary network / daisy-chaining / vision sensor interface.
- **Selected component, Why selected:** Texas Instruments DP83867IRRGZR Gigabit Ethernet PHY (1.8 V I/O).
- **Bus, Bus speed, Voltage:** RGMII (125 MHz DDR clock), 1.8 V I/O voltage.
- **Owner:** Cortex-A35 (`CortexA35NSOS` Linux).
- **CubeMX resource:** `ETH2` (ETHSW disabled, independent MAC & MDIO).
- **Hardware Pins (14 total):**
  - `PG4`: ETH2_MDC (AF11)
  - `PC5`: ETH2_MDIO (AF10)
  - `PC3`: ETH2_RGMII_RX_CTL (AF10)
  - `PG0`: ETH2_RGMII_RXD0 (AF10)
  - `PC12`: ETH2_RGMII_RXD1 (AF10)
  - `PF9`: ETH2_RGMII_RXD2 (AF10)
  - `PC11`: ETH2_RGMII_RXD3 (AF10)
  - `PF6`: ETH2_RGMII_RX_CLK (AF10)
  - `PC4`: ETH2_RGMII_TX_CTL (AF10)
  - `PC7`: ETH2_RGMII_TXD0 (AF10)
  - `PC8`: ETH2_RGMII_TXD1 (AF10)
  - `PC9`: ETH2_RGMII_TXD2 (AF10)
  - `PC10`: ETH2_RGMII_TXD3 (AF10)
  - `PF7`: ETH2_RGMII_GTX_CLK (AF10)

## 9. MIPI CSI-2 Camera Interface
- **Purpose, Use cases:** High-resolution machine vision, SLAM, visual odometry.
- **Selected component, Why selected:** Raspberry Pi Camera compatible 15/22-pin FFC.
- **Bus, Bus speed, Voltage:** MIPI CSI-2 (2 data lanes + 1 clock lane, up to 1.5 Gbps/lane).
- **Owner:** Cortex-A35 (Linux V4L2 pipeline).
- **CubeMX resource:** `CSI` + `DCMIPP` (Pipe 1 active).
- **Hardware Pins:** Dedicated BGA balls `CSI_CKN/P`, `CSI_D0N/P`, `CSI_D1N/P`, `CSI_REXT`.

## 10. Display Subsystem (LTDC & DSIHOST)
- **Purpose, Use cases:** Local GUI display, HMI touch panel, HDMI monitor output.
- **Selected component, Why selected:** External DSI-to-HDMI bridge (ADV7535 / LT8912B / Sil9022A candidate).
- **Bus, Bus speed, Voltage:** Internal RGB888 to DSIHOST, 4 DSI data lanes (up to 1.0 Gbps/lane).
- **Owner:** Cortex-A35 (Linux DRM/KMS).
- **CubeMX resource:** `LTDC` (RGB888) + `DSIHOST` (Video Mode).
- **Hardware Pins:** Dedicated BGA balls `DSIHOST_CKN/P`, `DSIHOST_D0N/P` through `DSIHOST_D3N/P`.

## 11. Wi-Fi Wireless Interface
- **Purpose, Use cases:** Wireless telemetry, ROS 2 network bridge, web GUI.
- **Selected component, Why selected:** Murata Type 2AE or Ampak AP6256 module (tentative evaluation).
- **Bus, Bus speed, Voltage:** 4-bit SDIO up to 50 MHz, 1.8 V / 3.3 V I/O.
- **Owner:** Cortex-A35 (Linux `brcmfmac` / wireless stack).
- **CubeMX resource:** `SDMMC3`.
- **Hardware Pins:**
  - `PB14`: SDMMC3_D0 (AF10)
  - `PD13`: SDMMC3_D1 (AF10)
  - `PB12`: SDMMC3_D2 (AF10)
  - `PI11`: SDMMC3_D3 (AF10)
  - `PB13`: SDMMC3_CK (AF10)
  - `PD12`: SDMMC3_CMD (AF10)

## 12. Bluetooth Interface
- **Purpose, Use cases:** Wireless sensors, gamepads, BLE commissioning.
- **Selected component, Why selected:** Integrated with Wi-Fi module.
- **Bus, Bus speed, Voltage:** Asynchronous UART with RTS/CTS hardware flow control (up to 3 Mbps).
- **Owner:** Cortex-A35 (Linux BlueZ / `hciattach`).
- **CubeMX resource:** `USART3`.
- **Hardware Pins:**
  - `PE3`: USART3_TX (AF6)
  - `PE1`: USART3_RX (AF6)
  - `PE5`: USART3_RTS (AF6)
  - `PE4`: USART3_CTS (AF6)

## 13. CAN-FD Bus 1
- **Purpose, Use cases:** Primary robotic actuator and servo CAN-FD bus.
- **Selected component, Why selected:** Texas Instruments TCAN1044AVDRQ1 (1.8 V VIO).
- **Bus, Bus speed, Voltage:** ISO 11898-2 CAN-FD (1 Mbps nominal, up to 5–8 Mbps data phase).
- **Owner:** Cortex-M33 real-time core.
- **CubeMX resource:** `FDCAN1` (Normal mode, Bit Rate Switching enabled).
- **Hardware Pins:**
  - `PB9`: FDCAN1_TX (AF9)
  - `PB11`: FDCAN1_RX (AF9)

## 14. CAN-FD Bus 2
- **Purpose, Use cases:** Sensor network / payload CAN-FD bus.
- **Selected component, Why selected:** Texas Instruments TCAN1044AVDRQ1 (1.8 V VIO).
- **Bus, Bus speed, Voltage:** ISO 11898-2 CAN-FD.
- **Owner:** Cortex-M33 real-time core.
- **CubeMX resource:** `FDCAN2` (Normal mode, Bit Rate Switching enabled).
- **Hardware Pins:**
  - `PJ15`: FDCAN2_TX (AF9)
  - `PI13`: FDCAN2_RX (AF9)

## 15. CAN-FD Bus 3
- **Purpose, Use cases:** Auxiliary / isolated vehicle bus (smart BMS or external robot chassis).
- **Selected component, Why selected:** Texas Instruments TCAN1044AVDRQ1 or ISO1042 isolated transceiver.
- **Bus, Bus speed, Voltage:** ISO 11898-2 CAN-FD.
- **Owner:** Cortex-M33 real-time core.
- **CubeMX resource:** `FDCAN3` (Normal mode, Bit Rate Switching enabled).
- **Hardware Pins:**
  - `PD2`: FDCAN3_TX (AF9)
  - `PD1`: FDCAN3_RX (AF9)

## 16. Primary IMU (Inertial Measurement Unit)
- **Purpose, Use cases:** Hard real-time flight / balancing stabilization at up to 8 kHz sample rates.
- **Selected component, Why selected:** TDK InvenSense ICM-42688-P (dedicated high-speed SPI bus).
- **Bus, Bus speed, Voltage:** SPI Master Full-Duplex (up to 24 MHz), 3V3_SENSOR low-noise LDO.
- **Owner:** Cortex-M33 real-time core.
- **CubeMX resource:** `SPI1` (Hardware NSS disabled).
- **Hardware Pins:**
  - `PE0`: SPI1_SCK (AF5)
  - `PF12`: SPI1_MISO (AF5)
  - `PI5`: SPI1_MOSI (AF5)
  - CS: Dedicated M33 GPIO (TBD).

## 17. Magnetometer & Barometer Sensor Bus
- **Purpose, Use cases:** Geomagnetic heading estimation (MMC5983MA) and barometric altitude (BMP581).
- **Selected component, Why selected:** MEMSIC MMC5983MA + Bosch BMP581.
- **Bus, Bus speed, Voltage:** Shared SPI Master Full-Duplex (up to 10 MHz), 3V3_SENSOR rail.
- **Owner:** Cortex-M33 real-time core.
- **CubeMX resource:** `SPI2` (Hardware NSS disabled).
- **Hardware Pins:**
  - `PB0`: SPI2_SCK (AF5)
  - `PB6`: SPI2_MISO (AF5)
  - `PB2`: SPI2_MOSI (AF5)
  - Chip Selects: Discrete GPIO lines for MAG and BARO.

## 18. Robotics Expansion SPI
- **Purpose, Use cases:** High-speed sensor daughterboards, external ADCs, or coprocessor interconnect.
- **Bus, Bus speed, Voltage:** SPI Master Full-Duplex (up to 25 MHz).
- **Owner:** Cortex-M33 real-time core.
- **CubeMX resource:** `SPI3` (Hardware NSS disabled).
- **Hardware Pins:**
  - `PB7`: SPI3_SCK (AF6)
  - `PB10`: SPI3_MISO (AF6)
  - `PE2`: SPI3_MOSI (AF6)

## 19. ESC Motor Outputs (DShot / PWM Engine)
- **Purpose, Use cases:** 4-channel deterministic motor control (DShot150/300/600, OneShot, or standard PWM).
- **Bus, Bus speed, Voltage:** Timer PWM with DMA burst engine.
- **Owner:** Cortex-M33 real-time core.
- **CubeMX resource:** `TIM1` (CH1–CH4).
- **Hardware Pins:**
  - `PD11`: S_TIM1_CH1 (AF2) - Motor 1
  - `PD10`: S_TIM1_CH2 (AF2) - Motor 2
  - `PD9`: S_TIM1_CH3 (AF2) - Motor 3
  - `PD8`: S_TIM1_CH4 (AF2) - Motor 4

## 20. Optical / Magnetic Quadrature Encoder
- **Purpose, Use cases:** Wheel or joint encoder position feedback with hardware quadrature decoding.
- **Bus, Bus speed, Voltage:** Timer Encoder Mode (TI1/TI2 on CH1/CH2).
- **Owner:** Cortex-M33 real-time core.
- **CubeMX resource:** `TIM2`.
- **Hardware Pins:**
  - `PH5`: S_TIM2_CH1 (AF3) - Phase A
  - `PF15`: S_TIM2_CH2 (AF3) - Phase B
  - Index Z: Separate GPIO with EXTI interrupt capability.

## 21. General Actuator / RC PWM Expansion
- **Purpose, Use cases:** Auxiliary servos, camera gimbal, gripper control, LED driver.
- **Bus, Bus speed, Voltage:** 4-channel hardware PWM outputs.
- **Owner:** Cortex-M33 real-time core.
- **CubeMX resource:** `TIM3` (CH1–CH4).
- **Hardware Pins:**
  - `PI6`: S_TIM3_CH1 (AF2) - PWM Out 1
  - `PI7`: S_TIM3_CH2 (AF2) - PWM Out 2
  - `PF13`: S_TIM3_CH3 (AF2) - PWM Out 3
  - `PF14`: S_TIM3_CH4 (AF2) - PWM Out 4

## 22. Industrial Stepper Motor STEP Pulse
- **Purpose, Use cases:** High-frequency, jitter-free STEP pulse generator for external stepper drives.
- **Bus, Bus speed, Voltage:** Hardware timer PWM output.
- **Owner:** Cortex-M33 real-time core.
- **CubeMX resource:** `TIM4` (CH1).
- **Hardware Pins:**
  - `PI10`: S_TIM4_CH1 (AF2) - STEP Pulse
  - Direction: Standard M33 GPIO `STEP_DIR` (TBD).

## 23. Industrial RS-485 Interface
- **Purpose, Use cases:** Modbus RTU, smart motor bus (e.g. Dynamixel / Robotis), industrial field equipment.
- **Selected component, Why selected:** Texas Instruments THVD1450 with hardware Driver Enable.
- **Bus, Bus speed, Voltage:** Differential RS-485 half-duplex (up to 10 Mbps).
- **Owner:** Cortex-M33 real-time core.
- **CubeMX resource:** `USART6` with hardware Driver Enable (`USART6_DE`).
- **Hardware Pins:**
  - `PJ5`: USART6_TX (AF7)
  - `PJ8`: USART6_RX (AF7)
  - `PG5`: USART6_DE (AF7)

## 24. GNSS Navigation Module
- **Purpose, Use cases:** Global positioning (u-blox / Quectel receiver) and microsecond timekeeping.
- **Bus, Bus speed, Voltage:** Asynchronous serial (9600 to 921600 baud) + PPS pulse capture.
- **Owner:** Cortex-M33 real-time core.
- **CubeMX resource:** `UART4`.
- **Hardware Pins:**
  - `PK4`: UART4_TX (AF8)
  - `PI15`: UART4_RX (AF8)
  - PPS: External timer capture pin `GNSS_PPS` (TBD).

## 25. ExpressLRS / CRSF Receiver
- **Purpose, Use cases:** Ultra-low-latency remote command and telemetry link.
- **Bus, Bus speed, Voltage:** High-speed asynchronous serial (420 kbaud / 921.6 kbaud).
- **Owner:** Cortex-M33 real-time core.
- **CubeMX resource:** `UART5`.
- **Hardware Pins:**
  - `PG9`: UART5_TX (AF8)
  - `PG10`: UART5_RX (AF8)

## 26. Expansion Serial Port
- **Purpose, Use cases:** External sensors, radio modems, or coprocessor communications.
- **Bus, Bus speed, Voltage:** Asynchronous serial.
- **Owner:** Cortex-M33 real-time core.
- **CubeMX resource:** `UART7`.
- **Hardware Pins:**
  - `PD3`: UART7_TX (AF8)
  - `PH3`: UART7_RX (AF8)

## 27. Linux Debug Console
- **Purpose, Use cases:** Low-level kernel boot logging, U-Boot interactive shell, system console.
- **Selected component, Why selected:** Dedicated channel routed to onboard FTDI FT2232HL.
- **Bus, Bus speed, Voltage:** Asynchronous serial (115200 baud default).
- **Owner:** Cortex-A35 (`CortexA35NSOS` Linux).
- **CubeMX resource:** `USART2`.
- **Hardware Pins:**
  - `PA4`: USART2_TX (AF6)
  - `PA10`: USART2_RX (AF6)

## 28. Board Management & Display I2C Bus
- **Purpose, Use cases:** Control channel for external DSI-to-HDMI bridge, camera sensor configuration.
- **Bus, Bus speed, Voltage:** Standard/Fast I2C (100/400 kHz), open-drain with pull-ups.
- **Owner:** Cortex-A35 (`CortexA35NSOS` Linux).
- **CubeMX resource:** `I2C1`.
- **Hardware Pins:**
  - `PG13`: I2C1_SCL (AF9)
  - `PI1`: I2C1_SDA (AF9)

## 29. Cortex-M33 Onboard Control I2C Bus
- **Purpose, Use cases:** Local telemetry, EEPROM, temperature sensing.
- **Bus, Bus speed, Voltage:** Standard/Fast I2C (100/400 kHz), open-drain.
- **Owner:** Cortex-M33 real-time core.
- **CubeMX resource:** `I2C2`.
- **Hardware Pins:**
  - `PB5`: I2C2_SCL (AF9)
  - `PB4`: I2C2_SDA (AF9)

## 30. Robotics Expansion I2C Bus
- **Purpose, Use cases:** External I2C sensor breakouts, OLED displays, payload controllers.
- **Bus, Bus speed, Voltage:** Standard/Fast I2C (100/400 kHz), open-drain.
- **Owner:** Cortex-M33 real-time core.
- **CubeMX resource:** `I2C3`.
- **Hardware Pins:**
  - `PG1`: I2C3_SCL (AF9)
  - `PH2`: I2C3_SDA (AF9)

## 31. Battery & Power Telemetry (INA229 Architecture)
- **Purpose, Use cases:** High-precision pack voltage, current, shunt voltage, and instantaneous power monitoring for 2S–8S battery systems.
- **Selected component, Why selected:** Texas Instruments INA229 (85 V, 20-bit delta-sigma digital power monitor with SPI/I2C and programmable alarm output).
- **Architectural Decision:** Internal STM32 ADC channels are intentionally **NOT** committed to the main battery power-monitoring path to avoid switching noise, ADC offset errors, and routing high-voltage divider paths near sensitive analog pins.
- **Owner:** Cortex-M33 real-time domain.
- **Bus:** SPI or I2C with dedicated `INA229_ALERT` interrupt line to M33.

## 32. JTAG Hardware Debug Interface
- **Purpose, Use cases:** Hardware in-circuit debugging, boundary scan, OpenOCD/GDB access via FT2232HL Channel A.
- **Bus, Bus speed, Voltage:** 4-wire JTAG interface.
- **Owner:** Cortex-A35 (`DEBUG` context).
- **Hardware Pins:** Dedicated BGA balls `JTCK-SWCLK`, `JTMS-SWDIO`, `JTDI`, `JTDO-TRACESWO`.
