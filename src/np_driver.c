#include "np_driver.h"
#include "ws2818b.pio.h"
#include "pico/stdlib.h"

typedef struct
{
    uint8_t G, R, B;
} npLED_t;

static npLED_t leds[MATRIX_LEDS];
uint8_t global_brightness = 127;

static PIO np_pio;
static uint sm;

static inline uint8_t scale(uint8_t v, uint8_t factor)
{
    return (uint16_t)v * factor / 255;
}

void npInit(uint pin)
{
    uint offset = pio_add_program(pio0, &ws2818b_program);
    np_pio = pio0;

    sm = pio_claim_unused_sm(np_pio, false);
    if (sm < 0)
    {
        np_pio = pio1;
        sm = pio_claim_unused_sm(np_pio, true);
    }

    ws2818b_program_init(np_pio, sm, offset, pin, 800000.f);

    for (uint i = 0; i < MATRIX_LEDS; ++i)
    {
        leds[i].R = leds[i].G = leds[i].B = 0;
    }

    npWrite();
}

void npSetLED(uint index, uint8_t r, uint8_t g, uint8_t b)
{
    if (index >= MATRIX_LEDS)
        return;

    leds[index].R = scale(r, global_brightness);
    leds[index].G = scale(g, global_brightness);
    leds[index].B = scale(b, global_brightness);
}

void npClear()
{
    for (uint i = 0; i < MATRIX_LEDS; ++i)
    {
        npSetLED(i, 0, 0, 0);
    }
}

void npWrite()
{
    for (uint i = 0; i < MATRIX_LEDS; ++i)
    {
        pio_sm_put_blocking(np_pio, sm, leds[i].G);
        pio_sm_put_blocking(np_pio, sm, leds[i].R);
        pio_sm_put_blocking(np_pio, sm, leds[i].B);
    }
    sleep_us(100);
}

uint8_t rc_to_idx(uint8_t row, uint8_t col)
{
    uint8_t hw_row = MATRIX_SIDE - 1 - row;
    if (hw_row & 1)
        return hw_row * MATRIX_SIDE + col;
    else
        return hw_row * MATRIX_SIDE + (MATRIX_SIDE - 1 - col);
}
