// animations.h

#ifndef ANIMATIONS_H
#define ANIMATIONS_H

#include "led_animation.h"

extern Animation pulse_heart;
extern Animation seconds_hand;
extern Animation minutes_hand;
extern Animation hours_hand;
extern Animation embarcatech;

void animation_start_at(Animation *anim, uint64_t now_ms, float start_value, float max_value);

#endif // ANIMATIONS_H
