/**
 * @file i2s_mic_driver.h
 * @brief I2S DMA MEMS Microphone Driver Header for TinyML Audio
 * @author Herambeswar Mandadapu
 */

#ifndef I2S_MIC_DRIVER_H
#define I2S_MIC_DRIVER_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#define I2S_AUDIO_BUFFER_SIZE  512

void I2S_Microphone_Init(uint32_t sample_rate_hz);
bool I2S_Microphone_ReadFrame(int16_t *out_frame, size_t sample_count);

#endif /* I2S_MIC_DRIVER_H */
