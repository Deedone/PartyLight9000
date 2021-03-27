#include <stm32f4xx_hal.h>


#define SAMPLES 1024

#define FFT_IN (SAMPLES * 2)
//Second half is a mirror of the first so we drop it
#define FFT_OUT (SAMPLES / 2)
extern UART_HandleTypeDef huart1;
extern ADC_HandleTypeDef hadc1;

//extern float fft_output[FFT_OUT];
extern float fft_input[FFT_IN];
extern volatile int processing_done;

void capture(int samples);
void process(int samples);