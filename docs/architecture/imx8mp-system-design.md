# NXP i.MX 8M Plus System Architecture

## Part Selection
**Selected Part:** `MIMX8ML8CVNKZAB` (NXP i.MX 8M Plus)
- **Cores:** Quad-core Arm Cortex-A53 @ 1.6 GHz
- **Real-Time Domain:** Cortex-M7 @ 800 MHz
- **NPU:** Integrated Neural Processing Unit (2.3 TOPS)
- **Package:** 15 x 15 mm FC-PBGA
- **Pitch:** 0.5 mm
- **Temperature:** Industrial (-40°C to 105°C)

### Why This Was Chosen (The Pivot from i.MX 95)
We initially selected the i.MX 95, but ran into a critical "NDA Wall". NXP restricts the hardware design guides for their newest processors behind corporate logins, which makes open-source hardware design impossible. 

We pivoted to the **i.MX 8M Plus** because:
1. **100% Public Documentation:** The Reference Manuals, Datasheets, and Hardware Design Guides are completely open and accessible without an NDA.
2. **LCSC Native Stock:** It is physically stocked in LCSC's native catalog (`MIMX8ML8CVNKZAB`), eliminating complex Global Sourcing supply chain issues.
3. **Manufacturability:** While it has a tighter **0.5 mm pitch**, modern PCB fabs like JLCPCB offer free Via-in-Pad (POFV) on 6-layer boards, which allows us to route this BGA without resorting to ultra-expensive HDI blind/buried microvias.

### Vendor Links & Sourcing Strategy
- **LCSC Page (Native Stock):** [LCSC MIMX8ML8CVNKZAB](https://www.lcsc.com/product-detail/Processors-Microcontrollers-MCUs_NXP-Semiconductors-MIMX8ML8CVNKZAB_C2849924.html)
- **NXP Product Page:** [i.MX 8M Plus Product Page](https://www.nxp.com/products/processors-and-microcontrollers/arm-processors/i-mx-applications-processors/i-mx-8-processors/i-mx-8m-plus-arm-cortex-a53-machine-learning-vision-multimedia-and-industrial-iot:i.MX8MPLUS)
- **Hardware Design Guide (Public PDF):** [i.MX 8M Plus Hardware Developer's Guide](https://www.nxp.com/docs/en/hardware-development/IMX8MPHDG.pdf)

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
    PMIC["PCA9460 PMIC"]:::pwr

    %% The SoC
    subgraph SOC ["NXP i.MX 8M Plus"]
        direction TB
        CPU["4x Cortex-A53 Cores"]:::core
        RT["M7 Real-Time Core"]:::core
        NPU["2.3 TOPS NPU"]:::core
    end

    %% Internal Subsystems (Grouped right of SoC core)
    RAM["LPDDR4 Memory"]:::memory
    FLASH["eMMC 5.1 & QSPI"]:::memory
    WIFI["SDIO WiFi/BT Module"]:::io
    
    %% Right Side: External Interfaces
    USB_PCIE(["USB Type-C & M.2 PCIe"]):::external
    ETH_CONN(["2x RJ45 w/ Magnetics"]):::external
    CAM_DISP(["Camera & Display Panels"]):::external
    ROBOT_IO(["CAN Bus & SPI Headers"]):::external

    %% Routing logic (Strict Left-to-Right to prevent tangling)
    PWR_JACK --> PMIC
    PMIC --> SOC
    
    DEBUG_USB --- FTDI
    FTDI -->|JTAG & UART| SOC

    SOC --- RAM
    SOC --- FLASH
    SOC --- WIFI

    SOC -->|PCIe / USB| USB_PCIE
    SOC -->|RGMII| ETH_CONN
    SOC -->|MIPI| CAM_DISP
    SOC -->|I2C / SPI / CAN| ROBOT_IO
```

---

## Programming & Debugging Methodology

### 1. Initial Flashing (The NXP USB Serial Downloader)
When the i.MX 8M Plus boots with a blank eMMC/Flash, its Boot ROM automatically falls back to **Serial Downloader Mode** (SDP). 
- **How it works:** The SoC enumerates as a USB HID device on a host PC connected to its `USB1` port. 
- **The Tool:** We use NXP's **Universal Update Utility (UUU)**. It pushes a temporary bootloader into internal RAM, executes it, and allows the host to permanently flash the full Linux OS to the eMMC.

### 2. Low-Level Debugging & Serial Console (FTDI)
- **Recommendation:** **We will integrate an FTDI FT2232HL (Dual Channel USB-to-UART/FIFO).** 
- **Why:** Ease-of-use is a massive priority. Putting an FTDI chip directly on the board allows developers to plug in a single USB cable and instantly get both a **Serial UART Console** (for Linux/U-Boot logs) and a **JTAG interface** (for bare-metal debugging).

## Recommended Supporting ICs & References

### 1. Power Management (PMIC)
- **Recommendation:** **NXP PCA9460** or **PCA9450C** (Companion PMICs for i.MX 8M Plus).
- **Datasheet Ref:** See [i.MX 8M Plus Hardware Developer's Guide (PDF)](https://www.nxp.com/docs/en/hardware-development/IMX8MPHDG.pdf), **Section 4.2 (Power Management)**.
- **Why:** The processor requires complex power-up sequencing. A dedicated companion PMIC handles this internally via pre-programmed OTP memory.

### 2. Main Memory (LPDDR4)
- **Recommendation:** **Micron MT53E series** (e.g., 2GB or 4GB LPDDR4) or equivalent Samsung memory.
- **Datasheet Ref:** See [i.MX 8M Plus Hardware Developer's Guide (PDF)](https://www.nxp.com/docs/en/hardware-development/IMX8MPHDG.pdf), **Section 3.1 (LPDDR4 Routing Guidelines)** for exact impedance, length matching, and skew rules.

### 3. Mass Storage (eMMC 5.1)
- **Recommendation:** **SanDisk/Western Digital iNAND** or **Kioxia THGBM series** (64GB, 128GB, or 256GB).
- **Datasheet Ref:** See [i.MX 8M Plus Datasheet (PDF)](https://www.nxp.com/docs/en/data-sheet/IMX8MPIEC.pdf), **Section 3.9 (uSDHC Electrical Characteristics)** for clock margins.
- **Why High Capacity:** The i.MX 8M Plus has only a single **PCIe Gen3 lane**. We are explicitly **reserving this PCIe lane** via a standard M.2 slot for high-bandwidth external hardware. This allows the user to plug in a Coral Edge TPU for AI, an M.2 WiFi 6 card, an external GPU, OR an **external M.2 NVMe SSD** if they need terabytes of storage. Because the PCIe lane is a modular expansion slot rather than a hardwired SSD, the onboard eMMC must provide all the primary bulk storage for the OS. Therefore, a massive eMMC (64GB+) is strictly required.

### 5. Wireless (WiFi / Bluetooth)
- **Recommendation:** **Ampak AP6256** (or similar Murata 1MW SDIO module).
- **Why:** We want built-in WiFi, but we cannot use the PCIe lane because it is reserved for the modular M.2 expansion slot. The i.MX 8M Plus features a secondary SDIO interface (`uSDHC2`) which is perfectly suited for high-speed 802.11ac WiFi and Bluetooth 5.0 combos.

### 6. Configuration Boot Flash (QSPI)
- **Recommendation:** **Macronix MX25L** or **Winbond W25Q series**.
- **Datasheet Ref:** See [i.MX 8M Plus Reference Manual (PDF)](https://www.nxp.com/docs/en/reference-manual/IMX8MPRM.pdf), **Chapter 6 (System Boot)** for the exact boot strapping pin configurations.

### 7. High-Speed Switches / PHYs (Ethernet)
- **Ethernet PHY:** **Microchip KSZ9131** or **Realtek RTL8211F** (Gigabit PHYs with RGMII). These are natively supported by the mainline Linux kernel.
