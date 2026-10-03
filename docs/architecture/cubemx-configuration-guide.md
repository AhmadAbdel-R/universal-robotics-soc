# STM32CubeMX Configuration Guide & Platform Allocation

**CLASSIFICATION: DESIGN CHOICE / CONFIGURATION RECORD**

This document serves as the engineering record and bring-up guide for the STM32CubeMX configuration (`hardware/stm32mp257/cubemx/cubemx.ioc`) targeting the **STM32MP257FAIx** (TFBGA436, 0.8 mm pitch) on the Universal Robotics SoC platform.

---

## 1. System Context & Execution Domains

The SoC is configured under the **Cortex-A35 Trusted Domain (A35-TD)** security model with an asymmetric multi-processing (AMP) workload partition:

*   **Cortex-A35 Domain (Dual-Core @ 1.5 GHz):**
    *   **Secure World:** Trusted Firmware-A (TF-A BL2) + OP-TEE OS (Secure OS).
    *   **Non-Secure World:** U-Boot (SSBL) + Linux OS (OpenSTLinux kernel 6.6 LTS, Yocto Scarthgap).
    *   **Responsibilities:** High-level robotics software (ROS 2), computer vision (DCMIPP/ISP, NPU), network communications (Dual GbE, Wi-Fi 802.11ac), display (LTDC/DSI), mass storage (eMMC), and PCIe expansion.
*   **Cortex-M33 Domain (Real-Time Core @ 400 MHz):**
    *   **Execution Mode:** Non-Secure Coprocessor (`m33copro`), TrustZone disabled on M33 context.
    *   **Firmware:** Bare-metal or FreeRTOS initialized via Linux `remoteproc` framework or standalone boot.
    *   **Responsibilities:** Hard real-time motor control (DShot/PWM), quadrature encoder decoding, stepper pulse generation, low-latency IMU sampling, vehicle telemetry (CRSF/ELRS), safety interlocks (BMS fault, E-STOP), and industrial fieldbus communications (CAN-FD, RS-485, IO-Link).

---

## 2. Clocks, Oscillators, and PLL Architecture

| Domain | Oscillator / Source | Frequency | Parameters | Target Consumer | Status |
| :--- | :--- | :--- | :--- | :--- | :--- |
| **HSE** | External Crystal Resonator | **40.000 MHz** | `RCC.HSE_VALUE=40000000` | Main system PLL reference | **CONFIRMED** |
| **LSE** | External Crystal Resonator | **32.768 kHz** | Low-power crystal mode | RTC, low-power state retention | **CONFIRMED** |
| **PLL2 (DDR)**| Sourced from HSE (40 MHz) | **VCO = 1200 MHz** | `FBDIV2 = 30`, `POSTDIV2_2 = 2`, `FRACN = 0` | DDR_CTRL_PHY clock = **600 MHz** | **CONFIRMED** |
| **M33 ICACHE**| Internal Cache Subsystem | **400 MHz** | 2-way set associative instruction cache enabled via `HAL_ICACHE_Enable()` | Cortex-M33 deterministic execution | **CONFIRMED** |

> **Clock Tuning Note:** DDR PHY operates at 600 MHz clock frequency. Detailed LPDDR4 training parameters, ODT profiles, and AC timing registers are held at default CubeMX generation and will be validated against physical DRAM silicon during board bring-up.

---

## 3. Storage, Memory, and Boot Architecture

### 3.1 Memory & Flash Storage Allocation

| Peripheral | Target Device | Bus Width / Mode | Pins / Channels | Context Ownership | Function |
| :--- | :--- | :--- | :--- | :--- | :--- |
| **DDR_CTRL_PHY**| Micron MT53E1G32D2FW (4 GB LPDDR4) | 32-bit (Dual 16-bit channels, 16 Gbit/channel) | Dedicated DDR BGA balls | TF-A / U-Boot / Linux | System RAM (point-to-point) |
| **SDMMC2** | FORESEE FEMDRW064G (64 GB eMMC 5.1)| 8-bit MMC bus | PE6–PE15 | BootROM, U-Boot, Linux, TF-A (Addon) | Primary OS & RootFS storage |
| **OCTOSPI1**| Winbond W25Q256JVFIQ (32 MB NOR) | Quad-SPI Mode (1-4-4) | PD0, PD4, PD5, PD6, PD7 | BootROM, TF-A, U-Boot | Secondary / Recovery / Config storage |
| **SDMMC3** | Murata / Ampak SDIO Wi-Fi | 4-bit SDIO | PB12–PB14, PD12–PD13, PI11 | Linux (`CortexA35NSOS`) | High-speed wireless data |

### 3.2 Boot Device Reconciliation & Analysis

Under the A35 Trusted Domain model, the Yocto machine configuration (`hardware/stm32mp257/cubemx/cubemx.inc`) defines the boot medium build target via `BOOTDEVICE_LABELS`. Supported options in A35TD are:
*   `sdcard` (SDMMC1)
*   `emmc` (SDMMC2)
*   `nor-sdcard` (OCTOSPI1 + SDMMC1)
*   `nand-custom`

> **CRITICAL BOOT SPECIFICATION:**
> The repository formally locks **`BOOTDEVICE_LABELS:append = " emmc "`**.
> The board utilizes soldered onboard eMMC 5.1 without an external SD card socket.
> 
> **Reconciliation of CubeMX IOC vs Device Tree:**
> In the initial CubeMX pass, `CortexA35SFSBLA` (TF-A) retained an experimental assignment to `OCTOSPI1`, while `SDMMC2` was assigned to `BootROMA35`, `CortexA35NSSSBL` (U-Boot), and `CortexA35NSOS` (Linux).
> To prevent build failures where Yocto compiles TF-A for eMMC while the generated TF-A device tree lacks the `&sdmmc2` node, the device tree `CA35/DeviceTree/cubemx/tf-a/stm32mp257f-cubemx-mx.dts` has been augmented within the protected `USER CODE BEGIN pinctrl` and `USER CODE BEGIN addons` blocks:
> ```dts
> /* USER CODE BEGIN pinctrl */
> sdmmc2_pins_mx: sdmmc2_mx-0 { ... };
> /* USER CODE END pinctrl */
> 
> /* USER CODE BEGIN addons */
> &sdmmc2 {
>     pinctrl-names = "default";
>     pinctrl-0 = <&sdmmc2_pins_mx>;
>     status = "okay";
> };
> /* USER CODE END addons */
> ```
> **Next CubeMX GUI Pass Action:** In STM32CubeMX Pinout & Configuration -> Connectivity -> SDMMC2 -> Context Management, check `Cortex-A35 Secure FSBL` (TF-A) and uncheck `CortexA35SFSBLA` on OCTOSPI1 to natively synchronize `.ioc` metadata.

---

## 4. Comprehensive Peripheral Allocation Matrix

The table below documents every active peripheral in the current `.ioc` configuration:

| Peripheral | Context Owner | Bus / Interface | Assigned Physical Pins | Signal Names | Target Hardware / Purpose |
| :--- | :--- | :--- | :--- | :--- | :--- |
| **PCIE** | A35 (Linux) | Gen2 x1 Root Complex | Dedicated COMBOPHY Balls | `RX1N/P`, `TX1N/P`, `REXT` | M.2 Key-M Socket (NVMe / TPU) |
| **USB3DR** | A35 (Linux) | USB 2.0 High-Speed OTG | Dedicated USB2 PHY Balls | `DM`, `DP`, `TXRTUNE` | Type-C Dev/Recovery (USB2 mode) |
| **UCPD1** | M33 (Real-Time)| USB Type-C CC Logic | Dedicated UCPD Balls | `UCPD1_CC1`, `UCPD1_CC2` | Type-C Cable & Role Detection |
| **USBH_HS** | A35 (Linux) | USB 2.0 Host | Dedicated USB2 PHY + PJ0, PJ2| `DP`, `DM`, `VBUSEN` (PJ0), `OVRCUR` (PJ2) | External USB-A Host / Protected Switch |
| **ETH1** | A35 (Linux) | RGMII (1000BASE-T) | PA9, PA11, PA13–PA15, PC0–PC2, PF1–PF2, PH10–PH13 | 12 RGMII + MDC (PA9), MDIO (PF2) | TI DP83867 Gigabit PHY #1 |
| **ETH2** | A35 (Linux) | RGMII (1000BASE-T) | PC3–PC5, PC7–PC12, PF6–PF7, PF9, PG0, PG4 | 12 RGMII + MDC (PG4), MDIO (PC5) | TI DP83867 Gigabit PHY #2 |
| **CSI** | A35 (Linux) | MIPI CSI-2 (2 Data + Clock)| Dedicated CSI Balls | `CKN/P`, `D0N/P`, `D1N/P`, `REXT` | Raspberry Pi Camera 15/22-pin FFC |
| **DCMIPP** | A35 (Linux) | Parallel / CSI Pipeline | Internal Interconnect | `VP_DCMIPP_VS_PIPE1` | Camera ISP & Video Stream Capture |
| **LTDC** | A35 (Linux) | RGB888 (24-bit internal)| Internal Interconnect | `VP_LTDC_DSIMode` | Display Controller engine |
| **DSIHOST** | A35 (Linux) | MIPI DSI (4 Data + Clock) | Dedicated DSI Balls | `CKN/P`, `D0N/P` through `D3N/P` | Video Mode output to DSI-to-HDMI bridge |
| **FDCAN1** | M33 (Real-Time)| CAN-FD (up to 8 Mbps) | PB11 (RX), PB9 (TX) | `FDCAN1_RX`, `FDCAN1_TX` | TI TCAN1044A Transceiver #1 |
| **FDCAN2** | M33 (Real-Time)| CAN-FD (up to 8 Mbps) | PI13 (RX), PJ15 (TX) | `FDCAN2_RX`, `FDCAN2_TX` | TI TCAN1044A Transceiver #2 |
| **FDCAN3** | M33 (Real-Time)| CAN-FD (up to 8 Mbps) | PD1 (RX), PD2 (TX) | `FDCAN3_RX`, `FDCAN3_TX` | TI TCAN1044A Transceiver #3 (Optional Iso) |
| **SPI1** | M33 (Real-Time)| Master Full-Duplex | PE0 (SCK), PF12 (MISO), PI5 (MOSI) | `SPI1_SCK`, `SPI1_MISO`, `SPI1_MOSI` | Dedicated IMU (ICM-42688-P) |
| **SPI2** | M33 (Real-Time)| Master Full-Duplex | PB0 (SCK), PB6 (MISO), PB2 (MOSI) | `SPI2_SCK`, `SPI2_MISO`, `SPI2_MOSI` | Secondary Sensors (MMC5983MA, BMP581) |
| **SPI3** | M33 (Real-Time)| Master Full-Duplex | PB7 (SCK), PB10 (MISO), PE2 (MOSI) | `SPI3_SCK`, `SPI3_MISO`, `SPI3_MOSI` | Exposed Robotics Expansion SPI |
| **I2C1** | A35 (Linux) | Standard I2C | PG13 (SCL), PI1 (SDA) | `I2C1_SCL`, `I2C1_SDA` | DSI-to-HDMI Bridge & Linux Board Mgmt |
| **I2C2** | M33 (Real-Time)| Standard I2C | PB5 (SCL), PB4 (SDA) | `I2C2_SCL`, `I2C2_SDA` | Onboard M33 Control / Sensor Bus |
| **I2C3** | M33 (Real-Time)| Standard I2C | PG1 (SCL), PH2 (SDA) | `I2C3_SCL`, `I2C3_SDA` | Exposed Robotics Expansion I2C |
| **USART2** | A35 (Linux) | Asynchronous Serial | PA4 (TX), PA10 (RX) | `USART2_TX`, `USART2_RX` | Linux Debug Console (FT2232HL Ch B) |
| **USART3** | A35 (Linux) | Async Serial w/ RTS/CTS | PE3 (TX), PE1 (RX), PE5 (RTS), PE4 (CTS)| `USART3_TX/RX/RTS/CTS` | Bluetooth HCI (Murata / Ampak module) |
| **UART4** | M33 (Real-Time)| Asynchronous Serial | PK4 (TX), PI15 (RX) | `UART4_TX`, `UART4_RX` | GNSS / GPS Receiver |
| **UART5** | M33 (Real-Time)| Asynchronous Serial | PG9 (TX), PG10 (RX) | `UART5_TX`, `UART5_RX` | ExpressLRS / CRSF Receiver (>420 kbaud) |
| **USART6** | M33 (Real-Time)| RS-485 with Hardware DE | PJ5 (TX), PJ8 (RX), PG5 (DE) | `USART6_TX`, `USART6_RX`, `USART6_DE` | Industrial RS-485 Transceiver (THVD1450) |
| **UART7** | M33 (Real-Time)| Asynchronous Serial | PD3 (TX), PH3 (RX) | `UART7_TX`, `UART7_RX` | Exposed Robotics Expansion UART |
| **TIM1** | M33 (Real-Time)| 4-Channel PWM Engine | PD11 (CH1), PD10 (CH2), PD9 (CH3), PD8 (CH4)| `TIM1_CH1` through `TIM1_CH4` | ESC 1-4 Motor Control (PWM / DShot Engine) |
| **TIM2** | M33 (Real-Time)| Quadrature Encoder Mode| PH5 (CH1), PF15 (CH2) | `TIM2_CH1`, `TIM2_CH2` | Optical / Magnetic Incremental Encoder A/B |
| **TIM3** | M33 (Real-Time)| 4-Channel PWM Output | PI6 (CH1), PI7 (CH2), PF13 (CH3), PF14 (CH4)| `TIM3_CH1` through `TIM3_CH4` | General Actuator / RC Servo Expansion |
| **TIM4** | M33 (Real-Time)| Single-Channel PWM | PI10 (CH1) | `TIM4_CH1` | Industrial Stepper STEP Pulse Generator |
| **DEBUG** | A35 (Linux) | JTAG 4-Pin Interface | Dedicated JTAG Balls | `JTCK`, `JTMS`, `JTDI`, `JTDO` | JTAG Debugging (FT2232HL Channel A) |

---

## 5. Architectural Inconsistencies & Feasibility Verification

### 5.1 Dual Independent RGMII Verification
*   **Mux Feasibility:** Verified. ETH1 (PA/PC/PF/PH) and ETH2 (PC/PF/PG) share zero pin resources. Both interfaces have fully independent MDC/MDIO clock and data pairs.
*   **Switching Note:** The Ethernet Switch (`ETHSW`) remains **disabled**. Dual independent MAC addressing and routing are enforced.
*   **PHY Interrupts:** PHY interrupt generation was disabled in CubeMX to resolve an internal code generation collision. External interrupt lines (`ETH1_INT`, `ETH2_INT`) will be routed to general-purpose GPIOs on EXTI lines in the device tree during schematic capture.
*   **Internal Parameter Artifact:** In `cubemx.ioc`, `ETH1.MediaInterface=HAL_ETH_RMII_MODE` is an internal HAL template artifact. The pin multiplexing is verified as full 14-wire RGMII, and the Linux kernel driver binds to the device tree `pinctrl` and `phy-mode = "rgmii-id"`.

### 5.2 COMBOPHY & PCIe vs USB 3.0 Sharing
*   The STM32MP257 integrates a single 5 Gbit/s multi-protocol SerDes (`COMBOPHY`).
*   In this design, `COMBOPHY` is locked exclusively to **PCIe Gen2 x1 Root Complex** mode for the M.2 Key-M slot.
*   `USB3DR` is configured in `Dual_Role_mode_USB2`, restricting the USB-C interface to USB 2.0 High-Speed (480 Mbps). This prevents any hardware pin or silicon conflict.

### 5.3 Camera & Display Pipeline
*   Camera capture routes from the 2-lane MIPI CSI-2 D-PHY directly to `DCMIPP`.
*   Currently, `VP_DCMIPP_VS_PIPE1` is configured. If simultaneous high-resolution storage and scaled AI/display streaming are required, Pipe 2 will be activated in a subsequent CubeMX pass.
*   Display output is routed from LTDC (RGB888) directly through the internal DSIHOST block (4-lane video mode). An off-chip bridge translates DSI to standard HDMI.

---

## 6. Reserved Unassigned GPIO Budget (~74 Pins)

To ensure signal integrity, correct I/O bank voltage levels, and optimal PCB fanout, the following functional signals are intentionally reserved and **NOT** yet assigned to BGA balls:

### 6.1 Cortex-M33 Real-Time Signals
*   `STEP_DIR`: Stepper direction control output.
*   `ENCODER_Z`: Index pulse interrupt line (EXTI).
*   `GNSS_PPS`: Precision time-pulse capture for synchronization.
*   `INA229_ALERT`: Overcurrent / overvoltage alarm interrupt from digital power monitor.
*   `CAN1_STB`, `CAN2_STB`, `CAN3_STB`: Transceiver standby mode select lines.
*   `BMS_FAULT`: Hardware alert from external battery management system.
*   `BMS_ENABLE`: Master battery / actuator disconnect control.
*   `IMU_INT1`, `IMU_INT2`: Data-ready / FIFO watermark interrupts for ICM-42688-P.
*   `MAG_DRDY`: Magnetometer data ready interrupt.
*   `BARO_INT`: Barometer interrupt line.
*   `SPI1_CS_IMU`, `SPI2_CS_MAG`, `SPI2_CS_BARO`, `SPI3_CS_EXP`: Discrete SPI chip-selects.

### 6.2 Cortex-A35 Linux Domain Signals
*   `WIFI_EN`: Wireless module power enable.
*   `WIFI_HOST_WAKE`: Wireless out-of-band wake interrupt.
*   `BT_EN`: Bluetooth radio power enable.
*   `BT_HOST_WAKE`: Bluetooth wake interrupt.
*   `HDMI_BRIDGE_RST`: Hardware reset for external DSI-to-HDMI bridge.
*   `HDMI_BRIDGE_IRQ`: Interrupt request line from bridge IC.
*   `HDMI_HPD`: Hot-plug detect signal from HDMI connector.
*   `ETH1_INT`, `ETH2_INT`: Asynchronous link/speed interrupts from DP83867 PHYs.

> **Allocation Rule:** Ball assignments will occur during schematic symbol creation after cross-referencing ST's voltage domain tables (`VDDIO1` through `VDDIO4` supply voltages: 1.8 V vs 3.3 V).
