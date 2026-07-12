# 🔵 AeroLink

<p align="center">
  <b>The most advanced open-source Wi-Fi extender with a stunning glassmorphism dashboard.</b>
</p>

<p align="center">
  <img src="https://img.shields.io/badge/BY-Aarav-000000?style=for-the-badge&logo=github" alt="By Aarav">
  <img src="https://img.shields.io/badge/ESP32-NATIVE-FF6F00?style=for-the-badge&logo=espressif" alt="ESP32">
  <img src="https://img.shields.io/badge/LICENCE-MIT-00C853?style=for-the-badge" alt="MIT">
</p>

---

AeroLink transforms your ESP32 into a powerful wireless range extender with a **premium, modern web interface**. Built from the ground up by **Aarav** ([@agra-aarav15](https://github.com/agra-aarav15)).

> *"Not just a router — it's a statement."*

---

## 💰 Why AeroLink?

| Commercial Extender | AeroLink (ESP32) |
|---------------------|------------------|
| $50–$150+ | **~$6–$15** (ESP32 board) |
| Locked firmware | **100% open source** |
| Basic UI | **Glassmorphism dashboard** |
| Cloud-dependent | **Runs fully local** |
| Vendor abandonware | **You own it forever** |

**Best Wi-Fi extender per dollar on the planet.** Built by Aarav, for everyone.

---

## ✨ Features

| Feature | Description |
|---------|-------------|
| 🌐 **Wi-Fi Extension** | Extend your existing Wi-Fi network seamlessly |
| 🎨 **Glassmorphism UI** | Pure black + frosted glass dashboard with smooth animations |
| 📡 **Network Scanner** | Scan and connect to available networks |
| 🛡️ **Firewall (ACL)** | Fine-grained access control rules |
| 🔀 **Port Forwarding** | Map external ports to internal devices |
| 📊 **DHCP Reservations** | Assign static IPs to connected devices |
| 🔧 **OTA Updates** | Update firmware over-the-air from the web dashboard |
| 📱 **Mobile-First** | Beautiful on phones, tablets, and desktops |
| 🏠 **Home Assistant** | MQTT integration with HA auto-discovery |
| 🔌 **Ethernet Uplink** | WT32-ETH01 support for wired uplinks |

## 📱 Supported Hardware

| Board | Status |
|-------|--------|
| ESP32 | ✅ Full Support |
| ESP32-S3 | ✅ Full Support |
| ESP32-C3 | ✅ Full Support |
| ESP32-C5 | ✅ Full Support |
| ESP32-C6 | ✅ Full Support |
| WT32-ETH01 | ✅ Ethernet Uplink |

## 🚀 Quick Start

### Method 1: USB Flash (Direct)
```bash
# Install esptool
pip install esptool

# Flash AeroLink at 0x20000 (works best)
esptool.py --port /dev/ttyUSB0 --baud 460800 write_flash \
  0x0 bootloader.bin \
  0x8000 partition-table.bin \
  0xe000 ota_data_initial.bin \
  0x20000 aerolink.bin
```

### Method 2: GitHub Actions (Phone Friendly — No PC needed!)
1. Fork this repo → **Actions** → **Build AeroLink Firmware** → **Run workflow**
2. Wait ~3 min → Click build → Download **aerolink-firmware** zip
3. Extract `aerolink.bin` → Flash via ESP Flash Tool app on phone at **0x20000**
4. Done! Connect to "AeroLink" WiFi → open `192.168.4.1`

> **Note:** After first flash, future updates via **⚙️ Config → OTA Update** in the web dashboard.

---

## 🏗️ Build from Source

### ESP-IDF v5.5+
```bash
git clone https://github.com/agra-aarav15/AeroLink.git
cd AeroLink
idf.py set-target esp32
idf.py build
idf.py -p /dev/ttyUSB0 flash monitor
```

### PlatformIO
```bash
pio run -e esp32dev -t upload
```

## 📂 Project Structure

```
AeroLink/
├── components/
│   ├── http_server/         # Web server + dashboard UI
│   │   └── pages/           # All dashboard page templates
│   ├── cmd_router/          # Router command interface
│   ├── cmd_system/          # System command interface
│   ├── acl/                 # Access control lists
│   ├── dhcpserver/          # Custom DHCP server
│   ├── remote_console/      # Remote telnet console
│   ├── oled_display/        # OLED display support
│   ├── pcap_capture/        # Packet capture
│   ├── syslog/              # Syslog client
│   └── mqtt_ha/             # MQTT Home Assistant
├── main/                    # Main application (aerolink.c)
├── include/                 # Header files
├── .github/workflows/       # CI/CD build pipeline
└── README.md
```

## 📜 Licence

MIT Licence — see [LICENCE](LICENCE) for details.

## 🙏 Credits

| Role | Name |
|------|------|
| Creator & Developer | [Aarav](https://github.com/agra-aarav15) |
| Framework | [Espressif ESP-IDF](https://github.com/espressif/esp-idf) |

---

<p align="center">
  <b>Built with ❤️ by <a href="https://github.com/agra-aarav15">Aarav</a></b><br>
  <sub>AeroLink — The Future of Wi-Fi Extension</sub>
</p>