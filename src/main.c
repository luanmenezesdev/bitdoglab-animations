#include <stdio.h>
#include "pico/stdlib.h"
#include "led_animation.h"
#include "np_driver.h"
#include "animations.h"
#include "pico/cyw43_arch.h"
#include "lwip/pbuf.h"
#include "lwip/tcp.h"
#include "lwip/dns.h"
#include "lwip/init.h"
#include <string.h>

#define LED_PIN 7

int main()
{
    stdio_init_all();
    npInit(LED_PIN);
    npClear();

    while (true)
    {
        uint64_t now = to_ms_since_boot(get_absolute_time());

        if (embarcatech.start_time == 0)
            animation_start(&embarcatech, now);

        npClear();
        animation_render(&embarcatech, now);
        npWrite();

        sleep_ms(16);
    }

    return 0;
}
