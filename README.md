# 🎙️ TinyML Audio Keyword Spotting & MFCC Feature Extractor

[![Language](https://img.shields.io/badge/Language-C99%20%2F%20TinyML-00599C?style=flat-square&logo=c&logoColor=white)](https://en.wikipedia.org/wiki/C99)
[![Framework](https://img.shields.io/badge/Architecture-Quantized%20Neural%20Network-E0234E?style=flat-square)](https://www.tensorflow.org/lite/microcontrollers)
[![Target](https://img.shields.io/badge/Target-ARM%20Cortex--M4%20(CMSIS--NN)-03234C?style=flat-square&logo=arm&logoColor=white)](https://www.arm.com/)
[![Latency](https://img.shields.io/badge/Inference%20Latency-%3C%2014%20ms%20%40%2084MHz-green?style=flat-square)](https://en.wikipedia.org/wiki/Edge_computing)
[![License](https://img.shields.io/badge/License-MIT-blue?style=flat-square)](LICENSE)

An ultra-compact, deterministic **TinyML Audio Keyword Spotting (KWS) Engine** for edge microcontrollers (**ARM Cortex-M4 / STM32F4**). Features real-time **Mel-Frequency Cepstral Coefficients (MFCC)** spectral feature extraction and an 8-bit quantized neural network classifier.

---

## 🏛️ Edge AI Processing Pipeline

```mermaid
graph LR
    subgraph Audio ["Acoustic Input (16 kHz, 16-bit PCM)"]
        MIC["Microphone / I2S DMA Buffer (32 ms Window)"]
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

## ⚡ Core Features

1. **Deterministic MFCC Audio Preprocessing**:
   - Computes 13 MFCC spectral coefficients over a 512-sample (32 ms) sliding audio frame.
   - Pre-computed triangular Mel filterbank weights and Hanning windowing for zero dynamic allocation.
2. **Quantized Edge Neural Network**:
   - Fixed-point inference with sub-14 ms execution latency on an 84 MHz STM32F401.
   - Flash Memory footprint: **< 12.8 KB**, RAM usage: **< 3.4 KB**.
3. **Keyword Classes**:
   - Classifies streaming acoustic frames into: `SILENCE`, `UNKNOWN`, `KEYWORD: 'YES'`, and `KEYWORD: 'NO'`.

---

## 🛠️ Build & Verification

```bash
# Compile TinyML engine
gcc -Wall -Wextra -Iinclude src/mfcc_extractor.c src/nn_inference.c src/main.c -lm -o tinyml_kws

# Run inference simulation
./tinyml_kws

# Generate audio feature vectors
python tools/audio_feature_generator.py
```

---

## 👤 Author
* **Herambeswar Mandadapu** – [@mandadapuherambeswar-ux](https://github.com/mandadapuherambeswar-ux)
* **LinkedIn:** [Herambeswar Mandadapu](https://linkedin.com/in/herambeswar-mandadapu-5a977a385)
