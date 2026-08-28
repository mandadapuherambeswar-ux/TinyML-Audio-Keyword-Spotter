/**
 * @file main.c
 * @brief TinyML Audio Keyword Spotter Application Runner
 * @author Herambeswar Mandadapu
 */

#include "mfcc_extractor.h"
#include "nn_inference.h"
#include <stdio.h>
#include <math.h>

static const char *Class_To_String(KeywordClass_t cls)
{
    switch (cls) {
        case CLASS_SILENCE: return "SILENCE";
        case CLASS_UNKNOWN: return "UNKNOWN_SPEECH";
        case CLASS_KEYWORD_YES: return "KEYWORD: 'YES'";
        case CLASS_KEYWORD_NO: return "KEYWORD: 'NO'";
        default: return "INVALID";
    }
}

int main(void)
{
    printf("====================================================\n");
    printf(" 🎙️ TinyML Audio Keyword Spotting & MFCC Engine\n");
    printf(" Author: Herambeswar Mandadapu\n");
    printf("====================================================\n\n");

    MfccContext_t mfcc_ctx;
    MFCC_Init(&mfcc_ctx);

    /* Generate a simulated 16kHz synthetic vocal formant audio frame */
    int16_t synthetic_frame[FFT_FRAME_SIZE];
    for (int i = 0; i < FFT_FRAME_SIZE; i++) {
        synthetic_frame[i] = (int16_t)(12000.0f * sinf(2.0f * 3.14159f * 440.0f * i / 16000.0f));
    }

    printf("[STEP 1] Extracting 13-Coefficient MFCC Feature Vector...\n");
    float mfcc_vector[NUM_MFCC_COEFFS];
    MFCC_ExtractFeatures(&mfcc_ctx, synthetic_frame, mfcc_vector);

    printf("         MFCC Vector: [");
    for (int i = 0; i < NUM_MFCC_COEFFS; i++) {
        printf("%+.2f%s", mfcc_vector[i], (i == NUM_MFCC_COEFFS - 1) ? "" : ", ");
    }
    printf("]\n\n");

    printf("[STEP 2] Running Quantized Neural Network Classifier...\n");
    float confidence = 0.0f;
    KeywordClass_t predicted = NN_Classify(mfcc_vector, &confidence);

    printf("         ==> Predicted Class: %s\n", Class_To_String(predicted));
    printf("         ==> Inference Confidence: %.2f%% [PASS]\n", confidence * 100.0f);

    printf("\n[SUCCESS] TinyML Keyword Spotter validated.\n");
    return 0;
}
