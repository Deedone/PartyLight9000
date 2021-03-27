#include "sound.h"
#include "tm_stm32f4_fft.h"


uint16_t sound_buf[SAMPLES];
float fft_input[FFT_IN];
//float fft_output[FFT_OUT];
static unsigned char HEX[] = "0123456789ABCDEF";

TM_FFT_F32_t fft;
volatile int processing_done = 0;
void process(int samples) {
    TM_FFT_Init_F32(&fft, samples, 0);
    TM_FFT_SetBuffers_F32(&fft, fft_input, fft_input);
    for(int i = 0; i < samples; i++) {
        //Fill only real parts of the complex input
        fft_input[i * 2] = (float)sound_buf[i] - (float)2048.0;
        fft_input[i * 2 + 1] = 0;
    }
    TM_FFT_Process_F32(&fft);
    
#ifdef DEBUG_FFT
    for (int i = 0; i < 120; i++) {
        char cbuf[8] = {0};
        uint32_t x = fft_output[i];
        for(int j = 0; j < 8; j++) {
            cbuf[7 - j] = HEX[x & 0xF];
            x >>= 4;
        }
        HAL_UART_Transmit(&huart1, &cbuf[2], 6, 10);
    }
#endif


    
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc) {
    HAL_ADC_Stop_DMA(&hadc1);
    processing_done = 1;
}
void capture(int samples) {
    processing_done = 0;
    HAL_ADC_Start_DMA(&hadc1, (uint32_t*)sound_buf, SAMPLES);
    while(!processing_done);
}
