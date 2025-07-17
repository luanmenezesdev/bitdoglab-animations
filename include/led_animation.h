#ifndef LED_ANIMATION_H
#define LED_ANIMATION_H

#include <stdint.h>
#include <stdbool.h>

#define MAX_LEDS_PER_FRAME 25
#define RED 255, 0, 0
#define GREEN 0, 255, 0
#define BLUE 0, 0, 255

// Representa um LED aceso com cor RGB em coordenadas da matriz
typedef struct
{
    uint8_t row;
    uint8_t col;
    uint8_t r, g, b;
} FrameLED;

// Representa um quadro da animação (keyframe)
typedef struct
{
    float progress_pct; // Ex: 0.0, 25.0, 100.0
    FrameLED *leds;     // Lista de LEDs ativos neste frame
    uint8_t led_count;
} Keyframe;

// Animação composta de vários keyframes
typedef struct
{
    Keyframe *frames;
    uint8_t frame_count;
    uint32_t duration_ms; // Ex: 60000 para 1 min
    uint64_t start_time;  // Timestamp em ms
    bool loop;
} Animation;

// Atualiza o buffer de LEDs com base no tempo atual
void animation_render(Animation *anim, uint64_t now_ms);

// Helper opcional: seta a animação para começar "agora"
void animation_start(Animation *anim, uint64_t now_ms);

#endif
