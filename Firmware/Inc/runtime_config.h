#ifndef OPQ_RUNTIME_CONFIG_H_H
#define OPQ_RUNTIME_CONFIG_H_H
#include "stm32f3xx_hal.h"

///Number of OPQFrames inside the OPQ_Frame_Buffer.
#define FRAME_BUFFER_SIZE 4
#define FRAME_DATA_COUNT 200

///OPQ data frame:
typedef struct{
    ///Signed 16 bit data points
    int16_t data[FRAME_DATA_COUNT];
    //Reserved
    int32_t zero_crossing_high;
    //Reserved
    int32_t zero_crossing_low;
} OPQ_Frame;

///OPQ Frame Buffer. This is a persistent data structure for storing the data samples.
typedef struct{
    ///Data frame circular buffer.
    OPQ_Frame frames[FRAME_BUFFER_SIZE];
    ///Head of the buffer.
    uint8_t head;
    ///Tail of the buffer.
    uint8_t tail;
    ///Current data sample in the frame.
    uint8_t currentSample;
} OPQ_Frame_Buffer;

///Circular frame buffer
extern __IO OPQ_Frame_Buffer frameBuffer;

///Register buffer implementation.
void init_OPQ_RunTime();

#endif //FIRMWARE_RUNTIME_CONFIG_H_H
