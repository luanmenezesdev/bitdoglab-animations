#include <stdio.h>
#include "pico/stdlib.h"
#include "led_animation.h"
#include "np_driver.h"
#include "clock_animations.c"

#define LED_PIN 7

int main()
{
    stdio_init_all();
    npInit(LED_PIN);

    while (true)
    {
        uint64_t now = to_ms_since_boot(get_absolute_time());

        if (seconds_hand.start_time == 0)
            animation_start(&seconds_hand, now);
        if (minutes_hand.start_time == 0)
            animation_start(&minutes_hand, now);
        if (hours_hand.start_time == 0)
            animation_start(&hours_hand, now);

        npClear();
        animation_render(&hours_hand, now);
        animation_render(&minutes_hand, now);
        animation_render(&seconds_hand, now);
        npWrite();

        sleep_ms(16);
    }
}
