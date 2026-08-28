/**
 * @file nn_inference.h
 * @brief 8-Bit Quantized Neural Network Inference Engine
 * @author Herambeswar Mandadapu
 */

#ifndef NN_INFERENCE_H
#define NN_INFERENCE_H

#include <stdint.h>
#include <stddef.h>

#define NN_INPUT_FEATURES    13
#define NN_HIDDEN_NODES      32
#define NN_NUM_CLASSES       4  /* 0: Silence, 1: Unknown, 2: "YES", 3: "NO" */

typedef enum {
    CLASS_SILENCE = 0,
    CLASS_UNKNOWN = 1,
    CLASS_KEYWORD_YES = 2,
    CLASS_KEYWORD_NO = 3
} KeywordClass_t;

typedef struct {
    int8_t weights_fc1[NN_INPUT_FEATURES * NN_HIDDEN_NODES];
    int32_t bias_fc1[NN_HIDDEN_NODES];
    int8_t weights_fc2[NN_HIDDEN_NODES * NN_NUM_CLASSES];
    int32_t bias_fc2[NN_NUM_CLASSES];
} ModelWeights_t;

void NN_Init(void);
KeywordClass_t NN_Classify(const float *mfcc_features, float *out_confidence);

#endif /* NN_INFERENCE_H */
