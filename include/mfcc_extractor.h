/**
 * @file mfcc_extractor.h
 * @brief Mel-Frequency Cepstral Coefficients (MFCC) Audio Feature Extractor
 * @author Herambeswar Mandadapu
 */

#ifndef MFCC_EXTRACTOR_H
#define MFCC_EXTRACTOR_H

#include <stdint.h>
#include <stddef.h>

#define AUDIO_SAMPLE_RATE_HZ     16000
#define FFT_FRAME_SIZE           512
#define NUM_MEL_FILTERS          26
#define NUM_MFCC_COEFFS          13

typedef struct {
    float hanning_window[FFT_FRAME_SIZE];
    float mel_energies[NUM_MEL_FILTERS];
    float mfcc_output[NUM_MFCC_COEFFS];
} MfccContext_t;

void MFCC_Init(MfccContext_t *ctx);
void MFCC_ExtractFeatures(MfccContext_t *ctx, const int16_t *audio_frame, float *out_mfcc);

#endif /* MFCC_EXTRACTOR_H */
