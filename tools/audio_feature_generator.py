#!/usr/bin/env python3
"""
TinyML Audio Feature Generator & Synthetic Vocal Synthesizer
Author: Herambeswar Mandadapu
"""

import math

def synthesize_vocal_tone(freq_hz=440.0, sample_rate=16000, duration_ms=32):
    num_samples = int(sample_rate * (duration_ms / 1000.0))
    samples = [int(12000.0 * math.sin(2.0 * math.pi * freq_hz * i / sample_rate)) for i in range(num_samples)]
    print(f"[*] Generated {len(samples)} Audio Samples @ {sample_rate} Hz (Tone: {freq_hz} Hz)")
    print(f"    Peak Amplitude: {max(samples)} | Min Amplitude: {min(samples)}")
    return samples

if __name__ == "__main__":
    print("====================================================")
    print(" 🎙️ TinyML Audio Synthetic Test Vector Generator")
    print("====================================================\n")
    synthesize_vocal_tone(440.0)
