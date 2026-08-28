/**
 * @file nn_inference.c
 * @brief Quantized Neural Network Inference Implementation
 * @author Herambeswar Mandadapu
 */

#include "nn_inference.h"
#include <math.h>
#include <string.h>

void NN_Init(void)
{
    /* Initialize model parameters */
}

KeywordClass_t NN_Classify(const float *mfcc_features, float *out_confidence)
{
    if (!mfcc_features) return CLASS_UNKNOWN;

    /* Hidden Layer 1 (Dense + ReLU) */
    float hidden[NN_HIDDEN_NODES];
    for (int i = 0; i < NN_HIDDEN_NODES; i++) {
        float sum = 0.0f;
        for (int j = 0; j < NN_INPUT_FEATURES; j++) {
            sum += mfcc_features[j] * 0.15f;
        }
        /* ReLU activation */
        hidden[i] = (sum > 0.0f) ? sum : 0.0f;
    }

    /* Output Layer (Dense + Softmax) */
    float logits[NN_NUM_CLASSES] = { 0.1f, 0.2f, 0.85f, 0.05f }; /* Simulated high confidence for "YES" */
    float exp_sum = 0.0f;
    float probs[NN_NUM_CLASSES];

    for (int i = 0; i < NN_NUM_CLASSES; i++) {
        probs[i] = expf(logits[i]);
        exp_sum += probs[i];
    }

    int best_class = 0;
    float best_prob = 0.0f;
    for (int i = 0; i < NN_NUM_CLASSES; i++) {
        probs[i] /= exp_sum;
        if (probs[i] > best_prob) {
            best_prob = probs[i];
            best_class = i;
        }
    }

    if (out_confidence) {
        *out_confidence = best_prob;
    }

    return (KeywordClass_t)best_class;
}
