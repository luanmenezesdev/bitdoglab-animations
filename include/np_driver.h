#ifndef NP_DRIVER_H
#define NP_DRIVER_H

#include <stdint.h>
#include "hardware/pio.h"

// Constantes da matriz
#define MATRIX_SIDE 5
#define MATRIX_LEDS (MATRIX_SIDE * MATRIX_SIDE)

// Controla brilho global dos LEDs (0-255)
extern uint8_t global_brightness;

// Inicializa a PIO e o buffer de LEDs
void npInit(uint pin);

// Atualiza os LEDs com os dados atuais
void npWrite(void);

// Seta cor RGB de um LED individual
void npSetLED(uint index, uint8_t r, uint8_t g, uint8_t b);

// Limpa todos os LEDs (apaga)
void npClear(void);

uint8_t rc_to_idx(uint8_t row, uint8_t col);

#endif
