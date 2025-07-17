#include "led_animation.h"
#include "np_driver.h"

FrameLED heart_frame0[] = {{2, 2, RED}};
FrameLED heart_frame1[] = {{1, 1, RED}, {1, 3, RED},
                           {2, 1, RED}, {2, 2, RED}, {2, 3, RED},
                           {3, 2, RED}};
FrameLED heart_frame2[] = {{0, 0, RED}, {0, 1, RED}, {0, 3, RED}, {0, 4, RED},
                           {1, 0, RED}, {1, 1, RED}, {1, 2, RED}, {1, 3, RED}, {1, 4, RED},
                           {2, 0, RED}, {2, 1, RED}, {2, 2, RED}, {2, 3, RED}, {2, 4, RED},
                           {3, 1, RED}, {3, 2, RED}, {3, 3, RED},
                           {4, 2, RED}};

Keyframe heart_frames[] = {
    {0.00f, heart_frame0, sizeof(heart_frame0) / sizeof(FrameLED)},
    {33.33f, heart_frame1, sizeof(heart_frame1) / sizeof(FrameLED)},
    {66.67f, heart_frame2, sizeof(heart_frame2) / sizeof(FrameLED)},
    {100.00f, heart_frame0, sizeof(heart_frame0) / sizeof(FrameLED)}};

Animation pulse_heart = {
    .frames = heart_frames,
    .frame_count = sizeof(heart_frames) / sizeof(Keyframe),
    .duration_ms = 5000, // 5 seconds
    .start_time = 0,
    .loop = true};
