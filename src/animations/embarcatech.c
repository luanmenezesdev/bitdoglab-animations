#include "led_animation.h"
#include "np_driver.h"

FrameLED frame_E[] = {
    {0,0,RED}, {0,1,RED}, {0,2,RED}, {0,3,RED}, {0,4,RED},
    {1,0,RED}, {2,0,RED}, {2,1,RED}, {2,2,RED},
    {3,0,RED}, {4,0,RED}, {4,1,RED}, {4,2,RED}, {4,3,RED}, {4,4,RED}
};

FrameLED frame_M[] = {
    {0,0,GREEN}, {0,4,GREEN},
    {1,0,GREEN}, {1,1,GREEN}, {1,3,GREEN}, {1,4,GREEN},
    {2,0,GREEN}, {2,2,GREEN}, {2,4,GREEN},
    {3,0,GREEN}, {3,4,GREEN},
    {4,0,GREEN}, {4,4,GREEN}
};

FrameLED frame_B[] = {
    {0,0,BLUE}, {0,1,BLUE}, {0,2,BLUE},
    {1,0,BLUE}, {1,2,BLUE},
    {2,0,BLUE}, {2,1,BLUE},
    {3,0,BLUE}, {3,2,BLUE},
    {4,0,BLUE}, {4,1,BLUE}, {4,2,BLUE}
};

FrameLED frame_A[] = {
    {0,2,RED},
    {1,1,RED}, {1,3,RED},
    {2,0,RED}, {2,1,RED}, {2,2,RED}, {2,3,RED}, {2,4,RED},
    {3,0,RED}, {3,4,RED},
    {4,0,RED}, {4,4,RED}
};

FrameLED frame_R[] = {
    {0,0,GREEN}, {0,1,GREEN}, {0,2,GREEN},
    {1,0,GREEN}, {1,2,GREEN},
    {2,0,GREEN}, {2,1,GREEN},
    {3,0,GREEN}, {3,2,GREEN},
    {4,0,GREEN}, {4,3,GREEN}
};

FrameLED frame_C[] = {
    {0,1,BLUE}, {0,2,BLUE}, {0,3,BLUE},
    {1,0,BLUE}, {2,0,BLUE},
    {3,0,BLUE},
    {4,1,BLUE}, {4,2,BLUE}, {4,3,BLUE}
};

FrameLED frame_T[] = {
    {0,0,GREEN}, {0,1,GREEN}, {0,2,GREEN}, {0,3,GREEN}, {0,4,GREEN},
    {1,2,GREEN},
    {2,2,GREEN},
    {3,2,GREEN},
    {4,2,GREEN}
};

FrameLED frame_H[] = {
    {0,0,GREEN}, {0,4,GREEN},
    {1,0,GREEN}, {1,4,GREEN},
    {2,0,GREEN}, {2,1,GREEN}, {2,2,GREEN}, {2,3,GREEN}, {2,4,GREEN},
    {3,0,GREEN}, {3,4,GREEN},
    {4,0,GREEN}, {4,4,GREEN}
};


Keyframe embarcatech_frames[] = {
    {0.00f, frame_E, sizeof(frame_E) / sizeof(FrameLED)},
    {9.09f, frame_M, sizeof(frame_M) / sizeof(FrameLED)},
    {18.18f, frame_B, sizeof(frame_B) / sizeof(FrameLED)},
    {27.27f, frame_A, sizeof(frame_A) / sizeof(FrameLED)},
    {36.36f, frame_R, sizeof(frame_R) / sizeof(FrameLED)},
    {45.45f, frame_C, sizeof(frame_C) / sizeof(FrameLED)},
    {54.54f, frame_A, sizeof(frame_A) / sizeof(FrameLED)},
    {63.63f, frame_T, sizeof(frame_T) / sizeof(FrameLED)},
    {72.72f, frame_E, sizeof(frame_E) / sizeof(FrameLED)},
    {81.81f, frame_C, sizeof(frame_C) / sizeof(FrameLED)},
    {90.90f, frame_H, sizeof(frame_H) / sizeof(FrameLED)},
    {100.00f, frame_E, sizeof(frame_E) / sizeof(FrameLED)}};

Animation embarcatech = {
    .frames = embarcatech_frames,
    .frame_count = sizeof(embarcatech_frames) / sizeof(Keyframe),
    .duration_ms = 10000, // 10 seconds
    .start_time = 0,
    .loop = true};
