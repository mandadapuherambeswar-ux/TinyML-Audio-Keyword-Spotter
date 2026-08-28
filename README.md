# 🎙️ TinyML Audio Keyword Spotting & MFCC Feature Extractor

[![Language](https://img.shields.io/badge/Language-C99%20%2F%20TinyML-00599C?style=flat-square&logo=c&logoColor=white)](https://en.wikipedia.org/wiki/C99)
[![Framework](https://img.shields.io/badge/Architecture-Quantized%20Neural%20Network-E0234E?style=flat-square)](https://www.tensorflow.org/lite/microcontrollers)
[![Target](https://img.shields.io/badge/Target-ARM%20Cortex--M4%20(CMSIS--NN)-03234C?style=flat-square&logo=arm&logoColor=white)](https://www.arm.com/)
[![Latency](https://img.shields.io/badge/Inference%20Latency-%3C%2014%20ms%20%40%2084MHz-green?style=flat-square)](https://en.wikipedia.org/wiki/Edge_computing)
[![License](https://img.shields.io/badge/License-MIT-blue?style=flat-square)](LICENSE)

An ultra-compact, deterministic **TinyML Audio Keyword Spotting (KWS) Engine** for edge microcontrollers (**ARM Cortex-M4 / STM32F4**). Features real-time **Mel-Frequency Cepstral Coefficients (MFCC)** spectral feature extraction and an 8-bit quantized neural network classifier.

---

## 🔌 Hardware Circuit Diagram & Digital Audio Interface

```
               +3.3V Power Bus
                     |
 +-------------------+---------------------------------------------------+
 |                   |                                                   |
 |                  3V3                                                  |
 |                                                                       |
 |   [ STM32F401 BlackPill MCU ]                                         |
 |                                                                       |
 |       (I2S3 SCK)        (I2S3 WS)        (I2S3 SD)                    |
 |          PB3               PA15             PB5                       |
 +-----------+-----------------+----------------+------------------------+
             |                 |                |
             v                 v                v
 +-----------+-----------------+----------------+------------------------+
 |          SCK                WS               SD                       |
 |                                                                       |
 |               [ INMP441 / SPH0645 MEMS Microphone Module ]            |
 |                                                                       |
 |          VDD               GND              L/R                       |
 +-----------+-----------------+----------------+------------------------+
             |                 |                |
           +3.3V              GND              GND (Left Channel Mode)
```

---

## 🏛️ Edge AI Processing Pipeline

```mermaid
graph LR
    subgraph Audio ["Acoustic Input (16 kHz, 16-bit PCM)"]
        MIC["INMP441 MEMS Mic / I2S DMA Buffer (32 ms Frame)"]
    end

    subgraph Feature ["Digital Signal Processing (MFCC)"]
        W["Hanning Windowing"]
        F["FFT & Mel Filterbank (26 Filters)"]
        D["Log Compression & DCT-II"]
    end

    subgraph Inference ["TinyML Quantized Classifier"]
        L1["Dense Layer (32 Nodes + ReLU)"]
        L2["Softmax Classification"]
    end

    subgraph Output ["Edge Inference Output"]
        C["Class: 'YES' / 'NO' / 'UNKNOWN' / 'SILENCE'"]
    end

    MIC --> W
    W --> F
    F --> D
    D -->|13 MFCC Coeffs| L1
    L1 --> L2
    L2 --> C
```

---

## ⚡ Hardware Pinout Matrix

| Microphone Pin | MCU Pin | Alternate Function | Purpose |
| :--- | :--- | :--- | :--- |
| **INMP441 SCK**| `PB3`  | `AF6` (SPI3_SCK / I2S3_CK) | Audio Bit Clock (512 kHz) |
| **INMP441 WS** | `PA15` | `AF6` (SPI3_NSS / I2S3_WS) | Word Select / Frame Clock (16 kHz) |
| **INMP441 SD** | `PB5`  | `AF6` (SPI3_MOSI / I2S3_SD)| Serial Data Output from Microphone |
| **INMP441 L/R**| `GND`  | None (Hardware Tie)        | Left Audio Channel Select |
| **Status LED** | `PA5`  | GPIO Output                | Keyword Detected Indicator |

---

## 🛠️ Build & Verification

```bash
# Compile TinyML engine
gcc -Wall -Wextra -Iinclude src/mfcc_extractor.c src/nn_inference.c src/i2s_mic_driver.c src/main.c -lm -o tinyml_kws

# Run inference simulation
./tinyml_kws

# Generate synthetic audio feature vectors
python tools/audio_feature_generator.py
```

---

## 👤 Author
* **Herambeswar Mandadapu** – [@mandadapuherambeswar-ux](https://github.com/mandadapuherambeswar-ux)
* **LinkedIn:** [Herambeswar Mandadapu](https://linkedin.com/in/herambeswar-mandadapu-5a977a385)
