# CubeMX Resource Budget

This table establishes the preliminary resource budget required for STM32CubeMX validation. Exact SPI/UART/TIMER instances (`TBD IN CUBEMX`) will be assigned based on pin-conflict analysis, alternate-function availability, and RIF (Resource Isolation Framework) ownership.

| Function | Peripheral Type | Preferred STM32 Peripheral | Software Owner | Required Signals | DMA Required | Interrupt Required | BootROM Constraint | Voltage Domain | Priority | Status | Potential Conflict | Notes |
|---|---|---|---|---|---|---|---|---|---|---|---|---|
| LPDDR4 | DDR | DDRCTRL | A35/Linux | 32-bit Data, CLK, CMD | N/A | N/A | YES | 1.1V / 0.55V | LOCKED | Pending | Pinout is fixed | Point-to-point 32-bit |
| eMMC 5.1 | SDMMC | SDMMC2 | A35/Linux | 8-bit Data, CLK, CMD | YES | YES | YES | 1.8V | LOCKED | Pending | BootROM pins | 64GB FORESEE |
| Boot Flash | XSPI | XSPI1 | A35/Linux | 4-bit Data, CLK, CS | YES | YES | YES | 3.3V | LOCKED | Pending | BootROM pins | W25Q256JV (Quad-SPI) |
| PCIe | PCIe | PCIe Gen2 | A35/Linux | TX/RX Diff, REFCLK, PERST | YES | YES | NO | High-Speed | LOCKED | Pending | Shares COMBOPHY | M.2 Key-M |
| USB 2.0 Device | USB HS | USB2 PHY | A35/Linux | DP/DM, VBUS | YES | YES | YES | 3.3V / 5V | LOCKED | Pending | BootROM pins | Type-C DFU/Recovery |
| USB 2.0 Host | USB HS | USB2 PHY | A35/Linux | DP/DM, VBUS | YES | YES | NO | 3.3V / 5V | PREFERRED | Pending | PHY limits | If supported by SoC |
| Ethernet 1 | ETH | ETH1 | A35/Linux | RGMII (TX/RX), MDIO/MDC | YES | YES | NO | 1.8V | LOCKED | Pending | Pin density | DP83867 |
| Ethernet 2 | ETH | ETH2 | A35/Linux | RGMII (TX/RX), MDIO/MDC | YES | YES | NO | 1.8V | LOCKED | Pending | Pin density | DP83867 |
| Camera | CSI | MIPI CSI | A35/Linux | CSI D0/D1, CLK | YES | YES | NO | High-Speed | LOCKED | Pending | None | RPi FFC |
| Display | DSI | MIPI DSI | A35/Linux | DSI D0-D3, CLK | YES | YES | NO | High-Speed | LOCKED | Pending | None | HDMI Bridge / RPi |
| Wi-Fi | SDIO | TBD IN CUBEMX | A35/Linux | 4-bit Data, CLK, CMD | YES | YES | NO | 1.8V / 3.3V | LOCKED | Pending | SDMMC limits | Murata Type 2AE |
| Wi-Fi Ctrl | GPIO | GPIO | A35/Linux | WL_REG_ON, HOST_WAKE | NO | YES | NO | 1.8V / 3.3V | LOCKED | Pending | None | |
| Bluetooth | UART | TBD IN CUBEMX | A35/Linux | TX, RX, CTS, RTS | YES | YES | NO | 1.8V / 3.3V | LOCKED | Pending | UART limits | Murata Type 2AE HCI |
| FDCAN 1 | FDCAN | FDCAN1 | M33 | TX, RX | YES | YES | NO | 1.8V | LOCKED | Pending | None | TCAN1044A |
| FDCAN 2 | FDCAN | FDCAN2 | M33 | TX, RX | YES | YES | NO | 1.8V | LOCKED | Pending | None | TCAN1044A |
| FDCAN 3 | FDCAN | FDCAN3 | M33 | TX, RX | YES | YES | NO | 1.8V | LOCKED | Pending | None | TCAN1044A |
| IMU SPI | SPI | TBD IN CUBEMX | M33 | SCLK, MOSI, MISO, CS | YES | YES | NO | 3.3V Sensor | LOCKED | Pending | Dedicated bus | ICM-42688-P |
| IMU INT1 | GPIO | GPIO | M33 | INT1 | NO | YES | NO | 3.3V Sensor | LOCKED | Pending | EXTI limits | |
| IMU INT2 | GPIO | GPIO | M33 | INT2 | NO | YES | NO | 3.3V Sensor | LOCKED | Pending | EXTI limits | |
| Sensor SPI | SPI | TBD IN CUBEMX | M33 | SCLK, MOSI, MISO | YES | YES | NO | 3.3V Sensor | LOCKED | Pending | None | Secondary Bus |
| Mag CS/INT | GPIO | GPIO | M33 | CS, DRDY | NO | YES | NO | 3.3V Sensor | LOCKED | Pending | None | MMC5983MA |
| Baro CS/INT | GPIO | GPIO | M33 | CS, INT | NO | YES | NO | 3.3V Sensor | LOCKED | Pending | None | BMP581 |
| High-G Accel | SPI/GPIO | TBD IN CUBEMX | M33 | CS, INT | NO | YES | NO | 3.3V Sensor | PREFERRED | Pending | None | ADXL372 (Optional) |
| ESC M1-M4 | Timer | TBD IN CUBEMX | M33 | CH1-CH4 | YES | NO | NO | TBD | LOCKED | Pending | Timer availability | PWM / DShot |
| ESC Telemetry | UART | TBD IN CUBEMX | M33 | RX | NO | YES | NO | TBD | LOCKED | Pending | UART limits | |
| ExpressLRS | UART | TBD IN CUBEMX | M33 | TX, RX | YES | YES | NO | TBD | LOCKED | Pending | UART limits | CRSF >420 kbaud |
| GNSS / GPS | UART | TBD IN CUBEMX | M33 | TX, RX | NO | YES | NO | TBD | LOCKED | Pending | UART limits | |
| GNSS PPS | Timer/EXTI | TBD IN CUBEMX | M33 | PPS (Input Capture) | NO | YES | NO | TBD | LOCKED | Pending | Timer capture | Low latency required |
| Encoder A/B/Z | Timer | TBD IN CUBEMX | M33 | TI1, TI2, Index | NO | YES | NO | TBD | LOCKED | Pending | Timer inputs | Incremental |
| STEP/DIR | Timer/GPIO | TBD IN CUBEMX | M33 | STEP, DIR, ENABLE | YES | NO | NO | TBD | LOCKED | Pending | Timer outputs | |
| Drive Fault | GPIO | GPIO | M33 | FAULT | NO | YES | NO | TBD | LOCKED | Pending | EXTI limits | |
| VBAT ADC | ADC | TBD IN CUBEMX | M33 | INx | YES | NO | NO | Analog | LOCKED | Pending | ADC channel | |
| Current ADC | ADC | TBD IN CUBEMX | M33 | INx | YES | NO | NO | Analog | LOCKED | Pending | ADC channel | INA240 / Shunt |
| Ext I2C/I3C | I2C/I3C | TBD IN CUBEMX | M33 / A35 | SDA, SCL, INT | NO | YES | NO | TBD | LOCKED | Pending | I2C limits | |
| Ext SPI | SPI | TBD IN CUBEMX | M33 / A35 | SCLK, MISO, MOSI, CS | NO | YES | NO | TBD | LOCKED | Pending | SPI limits | |
| IO-Link | UART | TBD IN CUBEMX | A35/Linux | TX, RX, EN, DIAG | NO | YES | NO | TBD | PREFERRED | Pending | UART limits | L6360 PHY |
| RS-485 | UART | TBD IN CUBEMX | M33 / A35 | TX, RX, DE/RE | NO | YES | NO | TBD | LOCKED | Pending | UART limits | THVD1450 |
| 24V Inputs | GPIO | GPIO | M33 / A35 | IN1-IN4 | NO | YES | NO | TBD | LOCKED | Pending | None | ISO1212 |
| 24V Outputs | GPIO | GPIO | M33 / A35 | OUT1, OUT2, DIAG | NO | YES | NO | TBD | LOCKED | Pending | None | TPS272C45 |
| Isolated CAN | FDCAN | FDCANx | M33 | TX, RX | YES | YES | NO | TBD | PREFERRED | Pending | Mux limits | ISO1042 Option |
| Ind. Analog | SPI | TBD IN CUBEMX | M33 / A35 | SCLK, MISO, MOSI, CS | YES | YES | NO | TBD | PREFERRED | Pending | SPI limits | ±10V / 4-20mA AFE |
| Load Cell | SPI | TBD IN CUBEMX | M33 | SCLK, MISO, MOSI, CS | NO | YES | NO | TBD | PREFERRED | Pending | SPI limits | ADS1235 Daughterboard |
| Resolver | SPI | TBD IN CUBEMX | M33 | SCLK, MISO, MOSI, CS | NO | YES | NO | TBD | PREFERRED | Pending | SPI limits | AD2S1210 Daughterboard |
| Debug JTAG | JTAG | JTAG | HW | TCK, TMS, TDI, TDO | NO | NO | NO | TBD | LOCKED | Pending | None | FT2232HL |
| Debug UART | UART | TBD IN CUBEMX | A35/Linux | TX, RX | NO | NO | YES | TBD | LOCKED | Pending | BootROM pins | Primary Linux Console |
| Boot Pins | GPIO | GPIO | HW | BOOT0, BOOT1, BOOT2 | NO | NO | YES | TBD | LOCKED | Pending | None | DIP Switch |
| HSE | OSC | RCC | HW | OSC_IN, OSC_OUT | NO | NO | YES | Analog | LOCKED | Pending | None | Main Crystal |
| LSE | OSC | RCC | HW | OSC32_IN, OSC32_OUT | NO | NO | NO | Analog | LOCKED | Pending | None | RTC Crystal |
| HDMI Ctrl | I2C | TBD IN CUBEMX | A35/Linux | SDA, SCL, INT | NO | YES | NO | TBD | PREFERRED | Pending | I2C limits | Bridge config |
| USB-C CC | I2C/UCPD | TBD IN CUBEMX | A35/Linux | CC1, CC2 | NO | NO | NO | TBD | LOCKED | Pending | UCPD logic | Type-C port |
