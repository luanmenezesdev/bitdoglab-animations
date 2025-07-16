#include <stdio.h>
#include "pico/stdlib.h"
#include "led_animation.h"

// Define LEDs de cada keyframe
FrameLED frame0[] = {{3, 255, 0, 0}, {8, 255, 0, 0}, {13, 255, 0, 0}};
FrameLED frame1[] = {{4, 255, 0, 0}, {9, 255, 0, 0}, {13, 255, 0, 0}};
FrameLED frame2[] = {{13, 255, 0, 0}, {14, 255, 0, 0}, {15, 255, 0, 0}};
FrameLED frame3[] = {{3, 255, 0, 0}, {8, 255, 0, 0}, {13, 255, 0, 0}};

Keyframe seconds_frames[] = {
    {0.0f, frame0, 3},
    {8.3f, frame1, 3},
    {25.0f, frame2, 3},
    {100.0f, frame3, 3}};

Animation seconds_hand = {
    .frames = seconds_frames,
    .frame_count = 4,
    .duration_ms = 60000,
    .start_time = 0,
    .loop = true};

int main()
{
    stdio_init_all();

    while (true)
    {
        if (seconds_hand.start_time == 0)
        {
            animation_start(&seconds_hand, to_ms_since_boot(get_absolute_time()));
        }

        animation_render(&seconds_hand, to_ms_since_boot(get_absolute_time()));
    }
}
