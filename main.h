#pragma once
#pragma warning(disable:4996) //_CRT_SECURE_NO_WARNINGS

typedef unsigned char       uint8;
typedef char                sint8;

typedef unsigned short      uint16;
typedef short               sint16;

typedef unsigned int        uint32;
typedef int                 sint32;

time_t rawtime;
struct tm * timeinfo;

typedef struct
{
    uint32 state;
    uint16 out;
    uint8 K;
} Filter;

typedef struct
{
    uint16 rawInput;
    uint16 filteredInput;
    Filter filt;
} Sensor;

Sensor sensor = {
    .rawInput = 200,
    .filteredInput = 0u,
    .filt = {
        .state = 0u,
        .out = 0u,
        .K = 5u
    }
};

#define FILT sensor.filt
