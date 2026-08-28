/**
 * @file mfcc_extractor.c
 * @brief MFCC Extraction Pipeline Implementation
 * @author Herambeswar Mandadapu
 */

#include "mfcc_extractor.h"
#include <math.h>
#include <string.h>

#define PI 3.14159265358979323846f

void MFCC_Init(MfccContext_t *ctx)
{
    if (!ctx) return;
    memset(ctx, 0, sizeof(MfccContext_t));

    /* Pre-compute Hanning Window coefficients */
    for (int i = 0; i < FFT_FRAME_SIZE; i++) {
        ctx->hanning_window[i] = 0.5f * (1.0f - cosf(2.0f * PI * i / (FFT_FRAME_SIZE - 1)));
    }
}

void MFCC_ExtractFeatures(MfccContext_t *ctx, const int16_t *audio_frame, float *out_mfcc)
{
    if (!ctx || !audio_frame || !out_mfcc) return;

    /* 1. Apply Windowing */
    float windowed[FFT_FRAME_SIZE];
    for (int i = 0; i < FFT_FRAME_SIZE; i++) {
        windowed[i] = ((float)audio_frame[i] / 32768.0f) * ctx->hanning_window[i];
    }

    /* 2. Compute Power Spectrum approximation */
    for (int m = 0; m < NUM_MEL_FILTERS; m++) {
        float energy = 0.001f;
        for (int k = m * 8; k < (m + 1) * 8 && k < (FFT_FRAME_SIZE / 2); k++) {
            energy += windowed[k] * windowed[k];
        }
        ctx->mel_energies[m] = logf(energy);
    }

    /* 3. Discrete Cosine Transform (DCT-II) */
    for (int i = 0; i < NUM_MFCC_COEFFS; i++) {
        float sum = 0.0f;
        for (int j = 0; j < NUM_MEL_FILTERS; j++) {
            sum += ctx->mel_energies[j] * cosf(PI * i * (j + 0.5f) / NUM_MEL_FILTERS);
        }
        out_mfcc[i] = sum;
    }
}
