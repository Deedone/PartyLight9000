#ifndef WS8212_H
#define WS8212_H

#include "stm32f4xx_hal.h"
#include <stdint.h>

#define NUMLED 120
#define LOW 29
#define HIGH 58

extern TIM_HandleTypeDef htim2;
extern DMA_HandleTypeDef hdma_tim2_ch3_up;
void ws8212_init(void);
void ws8212_update(void);
void ws8212_set(int index, uint8_t r, uint8_t g, uint8_t b);
void ws8212_setHSV(int index, uint16_t h, uint16_t s, uint16_t v);
void ws8212_fill( uint8_t r, uint8_t g, uint8_t b);
float noise2( float x, float y );

#endif