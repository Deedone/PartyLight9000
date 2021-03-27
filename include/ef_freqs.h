

#ifndef EF_FREQS_H
#define EF_FREQS_H
#include <stm32f4xx_hal.h>


void freqs_process(float smooth, int samples, float speed);
void build_index(int samples);



#endif