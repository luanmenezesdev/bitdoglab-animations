#include "led_animation.h"
#include "np_driver.h"

#define RED 255, 0, 0
#define GREEN 0, 255, 0
#define BLUE 0, 0, 255

FrameLED seconds_frame0[] = {{2, 2, RED}, {1, 2, RED}, {0, 2, RED}};
FrameLED seconds_frame1[] = {{2, 2, RED}, {1, 3, RED}, {0, 3, RED}};
FrameLED seconds_frame2[] = {{2, 2, RED}, {1, 3, RED}, {0, 4, RED}};
FrameLED seconds_frame3[] = {{2, 2, RED}, {1, 3, RED}, {1, 4, RED}};
FrameLED seconds_frame4[] = {{2, 2, RED}, {2, 3, RED}, {2, 4, RED}};
FrameLED seconds_frame5[] = {{2, 2, RED}, {3, 3, RED}, {3, 4, RED}};
FrameLED seconds_frame6[] = {{2, 2, RED}, {3, 3, RED}, {4, 4, RED}};
FrameLED seconds_frame7[] = {{2, 2, RED}, {3, 3, RED}, {4, 3, RED}};
FrameLED seconds_frame8[] = {{2, 2, RED}, {3, 2, RED}, {4, 2, RED}};
FrameLED seconds_frame9[] = {{2, 2, RED}, {3, 1, RED}, {4, 1, RED}};
FrameLED seconds_frame10[] = {{2, 2, RED}, {3, 1, RED}, {4, 0, RED}};
FrameLED seconds_frame11[] = {{2, 2, RED}, {3, 1, RED}, {3, 0, RED}};
FrameLED seconds_frame12[] = {{2, 2, RED}, {2, 1, RED}, {2, 0, RED}};
FrameLED seconds_frame13[] = {{2, 2, RED}, {1, 1, RED}, {1, 0, RED}};
FrameLED seconds_frame14[] = {{2, 2, RED}, {1, 1, RED}, {0, 0, RED}};
FrameLED seconds_frame15[] = {{2, 2, RED}, {1, 1, RED}, {0, 1, RED}};

FrameLED minutes_frame0[] = {{2, 2, GREEN}, {1, 2, GREEN}, {0, 2, GREEN}};
FrameLED minutes_frame1[] = {{2, 2, GREEN}, {1, 3, GREEN}, {0, 3, GREEN}};
FrameLED minutes_frame2[] = {{2, 2, GREEN}, {1, 3, GREEN}, {0, 4, GREEN}};
FrameLED minutes_frame3[] = {{2, 2, GREEN}, {1, 3, GREEN}, {1, 4, GREEN}};
FrameLED minutes_frame4[] = {{2, 2, GREEN}, {2, 3, GREEN}, {2, 4, GREEN}};
FrameLED minutes_frame5[] = {{2, 2, GREEN}, {3, 3, GREEN}, {3, 4, GREEN}};
FrameLED minutes_frame6[] = {{2, 2, GREEN}, {3, 3, GREEN}, {4, 4, GREEN}};
FrameLED minutes_frame7[] = {{2, 2, GREEN}, {3, 3, GREEN}, {4, 3, GREEN}};
FrameLED minutes_frame8[] = {{2, 2, GREEN}, {3, 2, GREEN}, {4, 2, GREEN}};
FrameLED minutes_frame9[] = {{2, 2, GREEN}, {3, 1, GREEN}, {4, 1, GREEN}};
FrameLED minutes_frame10[] = {{2, 2, GREEN}, {3, 1, GREEN}, {4, 0, GREEN}};
FrameLED minutes_frame11[] = {{2, 2, GREEN}, {3, 1, GREEN}, {3, 0, GREEN}};
FrameLED minutes_frame12[] = {{2, 2, GREEN}, {2, 1, GREEN}, {2, 0, GREEN}};
FrameLED minutes_frame13[] = {{2, 2, GREEN}, {1, 1, GREEN}, {1, 0, GREEN}};
FrameLED minutes_frame14[] = {{2, 2, GREEN}, {1, 1, GREEN}, {0, 0, GREEN}};
FrameLED minutes_frame15[] = {{2, 2, GREEN}, {1, 1, GREEN}, {0, 1, GREEN}};

FrameLED hours_frame0[] = {{2, 2, BLUE}, {1, 2, BLUE}, {0, 2, BLUE}};
FrameLED hours_frame1[] = {{2, 2, BLUE}, {1, 3, BLUE}, {0, 3, BLUE}};
FrameLED hours_frame2[] = {{2, 2, BLUE}, {1, 3, BLUE}, {1, 4, BLUE}};
FrameLED hours_frame3[] = {{2, 2, BLUE}, {2, 3, BLUE}, {2, 4, BLUE}};
FrameLED hours_frame4[] = {{2, 2, BLUE}, {3, 3, BLUE}, {3, 4, BLUE}};
FrameLED hours_frame5[] = {{2, 2, BLUE}, {3, 3, BLUE}, {4, 3, BLUE}};
FrameLED hours_frame6[] = {{2, 2, BLUE}, {3, 2, BLUE}, {4, 2, BLUE}};
FrameLED hours_frame7[] = {{2, 2, BLUE}, {3, 1, BLUE}, {4, 1, BLUE}};
FrameLED hours_frame8[] = {{2, 2, BLUE}, {3, 1, BLUE}, {3, 0, BLUE}};
FrameLED hours_frame9[] = {{2, 2, BLUE}, {2, 1, BLUE}, {2, 0, BLUE}};
FrameLED hours_frame10[] = {{2, 2, BLUE}, {1, 1, BLUE}, {1, 0, BLUE}};
FrameLED hours_frame11[] = {{2, 2, BLUE}, {1, 1, BLUE}, {0, 1, BLUE}};

Keyframe seconds_frames[] = {
    {0.00f, seconds_frame0, 3},
    {6.25f, seconds_frame1, 3},
    {12.50f, seconds_frame2, 3},
    {18.75f, seconds_frame3, 3},
    {25.00f, seconds_frame4, 3},
    {31.25f, seconds_frame5, 3},
    {37.50f, seconds_frame6, 3},
    {43.75f, seconds_frame7, 3},
    {50.00f, seconds_frame8, 3},
    {56.25f, seconds_frame9, 3},
    {62.50f, seconds_frame10, 3},
    {68.75f, seconds_frame11, 3},
    {75.00f, seconds_frame12, 3},
    {81.25f, seconds_frame13, 3},
    {87.50f, seconds_frame14, 3},
    {93.75f, seconds_frame15, 3},
    {100.00f, seconds_frame0, 3}};

Keyframe minutes_frames[] = {
    {0.00f, minutes_frame0, 3},
    {6.25f, minutes_frame1, 3},
    {12.50f, minutes_frame2, 3},
    {18.75f, minutes_frame3, 3},
    {25.00f, minutes_frame4, 3},
    {31.25f, minutes_frame5, 3},
    {37.50f, minutes_frame6, 3},
    {43.75f, minutes_frame7, 3},
    {50.00f, minutes_frame8, 3},
    {56.25f, minutes_frame9, 3},
    {62.50f, minutes_frame10, 3},
    {68.75f, minutes_frame11, 3},
    {75.00f, minutes_frame12, 3},
    {81.25f, minutes_frame13, 3},
    {87.50f, minutes_frame14, 3},
    {93.75f, minutes_frame15, 3},
    {100.00f, minutes_frame0, 3}};

Keyframe hours_frames[] = {
    {0.00f, hours_frame0, 3},
    {8.33f, hours_frame1, 3},
    {16.67f, hours_frame2, 3},
    {25.00f, hours_frame3, 3},
    {33.33f, hours_frame4, 3},
    {41.67f, hours_frame5, 3},
    {50.00f, hours_frame6, 3},
    {58.33f, hours_frame7, 3},
    {66.67f, hours_frame8, 3},
    {75.00f, hours_frame9, 3},
    {83.33f, hours_frame10, 3},
    {91.67f, hours_frame11, 3},
    {100.00f, hours_frame0, 3}};

Animation seconds_hand = {
    .frames = seconds_frames,
    .frame_count = sizeof(seconds_frames) / sizeof(Keyframe),
    .duration_ms = 60000,
    .start_time = 0,
    .loop = true};

Animation minutes_hand = {
    .frames = minutes_frames,
    .frame_count = sizeof(minutes_frames) / sizeof(Keyframe),
    .duration_ms = 3600000, // 1 hour
    .start_time = 0,
    .loop = true};

Animation hours_hand = {
    .frames = hours_frames,
    .frame_count = sizeof(hours_frames) / sizeof(Keyframe),
    .duration_ms = 43200000, // 12 hours
    .start_time = 0,
    .loop = true};

void animation_start_at(Animation *anim, uint64_t now_ms, float start_value, float max_value)
{
    float progress_frac = start_value / max_value;
    uint64_t offset = (uint64_t)(progress_frac * anim->duration_ms);
    anim->start_time = now_ms - offset;
}