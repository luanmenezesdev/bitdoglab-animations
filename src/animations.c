#include "led_animation.h"
#include "np_driver.h"
#include "animations/heart.c"
#include "animations/clock.c"
#include "animations/embarcatech.c"

void animation_start_at(Animation *anim, uint64_t now_ms, float start_value, float max_value)
{
    float progress_frac = start_value / max_value;
    uint64_t offset = (uint64_t)(progress_frac * anim->duration_ms);
    anim->start_time = now_ms - offset;
}
