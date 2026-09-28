# STMicroelectronics STM32MP257 System Architecture

## Part Selection
**Selected Part:** STM32MP257 (STMicroelectronics)
- **Cores:** Dual-core Arm Cortex-A35 @ 1.5 GHz
- **Real-Time Domain:** Cortex-M33 @ 400 MHz
- **NPU:** Integrated Neural Processing Unit (1.35 TOPS)
- **GPU:** 3D GPU (VeriSilicon Vivante) & Image Signal Processor (ISP)
- **Package:** VFBGA436 (0.5 mm pitch) or TFBGA436 (0.8 mm pitch)

### Why This Was Chosen (The Pivot from NXP)
We initially bounced between the NXP i.MX 95 and i.MX 8M Plus. However, NXP's aggressive use of Non-Disclosure Agreements (NDAs) for hardware design guides, combined with CDN firewalls that block automated datasheet retrieval, makes open-source hardware design immensely frustrating. 

We pivoted to the **STM32MP257** because:
1. **World-Class Public Documentation:** ST's datasheets, reference manuals, and the massive STM32 Wiki are completely open and accessible.
2. **Superior Economics:** ST components are historically more cost-effective, and the PMIC requirements are generally simpler and cheaper.
3. **Robotics Dream Specs:** It features exactly what we need—an AI NPU (1.35 TOPS), an M33 Real-Time core, PCIe Gen2, USB 3.0, 3x CAN-FD, and Dual Gigabit Ethernet.

---

## High-Level Block Diagram

```mermaid
flowchart LR
    %% Color Definitions
    classDef external fill:#2d3436,stroke:#b2bec3,stroke-width:2px,color:#fff,rx:5px,ry:5px;
    classDef core fill:#0984e3,stroke:#74b9ff,stroke-width:2px,color:#fff,rx:5px,ry:5px;
    classDef memory fill:#00b894,stroke:#55efc4,stroke-width:2px,color:#fff,rx:5px,ry:5px;
    classDef io fill:#e17055,stroke:#fab1a0,stroke-width:2px,color:#fff,rx:5px,ry:5px;
    classDef pwr fill:#d63031,stroke:#ff7675,stroke-width:2px,color:#fff,rx:5px,ry:5px;

    %% Left Side: Power & Debug Inputs
    PWR_JACK(["Power Jack / VDC"]):::external
    DEBUG_USB(["Debug USB Type-C"]):::external
    
    %% Support ICs
    FTDI["FT2232HL USB-to-JTAG/UART"]:::io
    PMIC["STPMIC2 PMIC"]:::pwr

    %% The SoC
    subgraph SOC ["STM32MP257"]
        direction TB
        CPU["2x Cortex-A35 Cores"]:::core
        RT["M33 Real-Time Core"]:::core
        NPU["1.35 TOPS NPU"]:::core
    end

    %% Internal Subsystems (Grouped right of SoC core)
    RAM["LPDDR4 Memory"]:::memory
    FLASH["eMMC 5.1 & QSPI"]:::memory
    WIFI["SDIO WiFi/BT Module"]:::io
    
    %% Right Side: External Interfaces
    USB_PCIE(["USB Type-C & M.2 PCIe"]):::external
    ETH_CONN(["2x RJ45 w/ Magnetics"]):::external
    CAM_DISP(["Camera & Display Panels"]):::external
    ROBOT_IO(["3x CAN-FD & SPI Headers"]):::external

    %% Routing logic (Strict Left-to-Right to prevent tangling)
    PWR_JACK --> PMIC
    PMIC --> SOC
    
    DEBUG_USB --- FTDI
    FTDI -->|JTAG & UART| SOC

    SOC --- RAM
    SOC --- FLASH
    SOC --- WIFI

    SOC -->|PCIe Gen2 / USB 3.0| USB_PCIE
    SOC -->|RGMII| ETH_CONN
    SOC -->|MIPI| CAM_DISP
    SOC -->|I2C / SPI / CAN| ROBOT_IO
```

---

## Programming & Debugging Methodology

### 1. Initial Flashing (STM32CubeProgrammer)
When the STM32MP25 boots with a blank eMMC/Flash, it falls back to a serial bootloader mode via USB. We use the **STM32CubeProgrammer** to flash the Trusted Firmware-A (TF-A), U-Boot, and Linux rootfs directly to the eMMC.

### 2. Low-Level Debugging & Serial Console (FTDI)
- **Recommendation:** **We will integrate an FTDI FT2232HL (Dual Channel USB-to-UART/FIFO).** 
- **Why:** Ease-of-use is a massive priority. Putting an FTDI chip directly on the board allows developers to plug in a single USB cable and instantly get both a **Serial UART Console** (for Linux/U-Boot logs) and a **JTAG interface** (for bare-metal debugging).

## Recommended Supporting ICs & References

### 1. Power Management (PMIC)
- **Recommendation:** **STPMIC2** (ST's companion PMIC for the STM32MP2 series).
- **Why:** Handles the exact power-up/power-down sequencing required by the STM32MP25 without needing a massive array of discrete buck converters.

### 2. Main Memory (LPDDR4)
- **Recommendation:** **Micron MT53E1G32D2FW-046 IT:A** (4GB, 32-bit, Point-to-Point).

### 3. Mass Storage (eMMC 5.1)
- **Recommendation:** **FORESEE FEMDRW064G-88A19** (64GB, eMMC 5.1).
- **Why High Capacity:** The STM32MP257 has a single **PCIe Gen2 lane**. We are explicitly **reserving this PCIe lane** via a standard M.2 slot for high-bandwidth external hardware (Coral Edge TPU, NVMe SSD, WiFi 6). Because the PCIe lane is a modular expansion slot, the onboard eMMC must provide all the primary bulk storage for the OS. Therefore, a massive eMMC (64GB+) is strictly required.

### 4. Wireless (WiFi / Bluetooth)
- **Recommendation:** **Ampak AP6256** (or similar Murata 1MW SDIO module).
- **Why:** We want built-in WiFi, but we cannot use the PCIe lane because it is reserved for the modular M.2 expansion slot. The STM32MP25 features secondary SDMMC interfaces perfectly suited for SDIO WiFi/BT combos.

### 5. Configuration Boot Flash (QSPI/OSPI)
- **Recommendation:** **Winbond W25Q256JVFIQ** (32MB QSPI NOR).

### 6. High-Speed Switches / PHYs (Ethernet)
- **Ethernet PHY:** **Texas Instruments DP83867IRRGZR** (Gigabit RGMII PHY with excellent programmable delay and diagnostics).

### 7. CAN-FD Transceivers
- **Recommendation:** **Texas Instruments TCAN1044AVDRQ1**.
- **Why:** Supports up to 8 Mbps, features a dedicated VIO pin for direct 1.8V logic interfacing with the STM32MP257 without level shifters, and is highly stocked on LCSC.
