#include <stdio.h>
#include "pico/stdlib.h"
#include "led_animation.h"

// Define LEDs de cada keyframe
FrameLED frame0[]  = {{13, 255, 0, 0},  {8, 255, 0, 0},  {3, 255, 0, 0}};  // 12h
FrameLED frame1[]  = {{13, 255, 0, 0},  {9, 255, 0, 0},  {4, 255, 0, 0}};  // 1h
FrameLED frame2[]  = {{13, 255, 0, 0},  {9, 255, 0, 0}, {10, 255, 0, 0}};  // 2h
FrameLED frame3[]  = {{13, 255, 0, 0}, {14, 255, 0, 0}, {15, 255, 0, 0}};  // 3h
FrameLED frame4[]  = {{13, 255, 0, 0}, {19, 255, 0, 0}, {20, 255, 0, 0}};  // 4h
FrameLED frame5[]  = {{13, 255, 0, 0}, {19, 255, 0, 0}, {24, 255, 0, 0}};  // 5h
FrameLED frame6[]  = {{13, 255, 0, 0}, {18, 255, 0, 0}, {23, 255, 0, 0}};  // 6h
FrameLED frame7[]  = {{13, 255, 0, 0}, {17, 255, 0, 0}, {22, 255, 0, 0}};  // 7h
FrameLED frame8[]  = {{13, 255, 0, 0}, {17, 255, 0, 0}, {16, 255, 0, 0}};  // 8h
FrameLED frame9[]  = {{13, 255, 0, 0}, {12, 255, 0, 0}, {11, 255, 0, 0}};  // 9h
FrameLED frame10[] = {{13, 255, 0, 0},  {7, 255, 0, 0},  {6, 255, 0, 0}};  // 10h
FrameLED frame11[] = {{13, 255, 0, 0},  {7, 255, 0, 0},  {2, 255, 0, 0}};  // 11h

Keyframe seconds_frames[] = {
    {0.0f,   frame0,  3},
    {8.3f,   frame1,  3},
    {16.7f,  frame2,  3},
    {25.0f,  frame3,  3},
    {33.3f,  frame4,  3},
    {41.7f,  frame5,  3},
    {50.0f,  frame6,  3},
    {58.3f,  frame7,  3},
    {66.7f,  frame8,  3},
    {75.0f,  frame9,  3},
    {83.3f,  frame10, 3},
    {91.7f,  frame11, 3},
    {100.0f, frame0,  3}  // Loop back to 12h
};

Animation seconds_hand = {
    .frames = seconds_frames,
    .frame_count = sizeof(seconds_frames) / sizeof(Keyframe),
    .duration_ms = 60000,
    .start_time = 0,
    .loop = true
};

int main() {
    stdio_init_all();

    while (true) {
        uint64_t now = to_ms_since_boot(get_absolute_time());

        if (seconds_hand.start_time == 0)
            animation_start(&seconds_hand, now);

        animation_render(&seconds_hand, now);
        sleep_ms(16); // evita busy loop (aprox 60 FPS)
    }
}
