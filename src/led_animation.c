#include "led_animation.h"
#include "pico/stdlib.h"
#include "ws2818b.pio.h"

extern void npSetLED(uint index, uint8_t r, uint8_t g, uint8_t b);
extern void npClear(void);
extern void npWrite(void);

void animation_start(Animation *anim, uint64_t now_ms) {
    anim->start_time = now_ms;
}

void animation_render(Animation *anim, uint64_t now_ms) {
    if (anim->frame_count == 0) return;

    uint64_t elapsed = now_ms - anim->start_time;

    if (elapsed > anim->duration_ms) {
        if (anim->loop) {
            anim->start_time = now_ms;
            elapsed = 0;
        } else {
            elapsed = anim->duration_ms;
        }
    }

    float pct = (float)elapsed / anim->duration_ms * 100.0f;

    // Encontra o último frame com progress_pct <= pct
    Keyframe *current = &anim->frames[0];
    for (int i = 1; i < anim->frame_count; i++) {
        if (anim->frames[i].progress_pct > pct)
            break;
        current = &anim->frames[i];
    }

    npClear();
    for (int i = 0; i < current->led_count; i++) {
        FrameLED led = current->leds[i];
        npSetLED(led.index, led.r, led.g, led.b);
    }
    npWrite();
}
