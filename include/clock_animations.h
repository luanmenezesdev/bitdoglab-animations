// clock_animations.h

#ifndef CLOCK_ANIMATIONS_H
#define CLOCK_ANIMATIONS_H

#include "led_animation.h"

extern Animation seconds_hand;
extern Animation minutes_hand;
extern Animation hours_hand;

void animation_start_at(Animation *anim, uint64_t now_ms, uint8_t start_value, uint8_t max_value);

#endif // CLOCK_ANIMATIONS_H
