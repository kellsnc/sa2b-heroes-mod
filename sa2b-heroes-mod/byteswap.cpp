#include "stdafx.h"

Sint32 bswap_S32(Sint32 input) {
    Sint32 result = ((input >> 24) & 0xff) | ((input << 8) & 0xff0000) |
        ((input >> 8) & 0xff00) | ((input << 24) & 0xff000000);

    return result;
}

Sint16 bswap_S16(Sint16 input) {
    Sint16 result = (input >> 8) | (input << 8);

    return result;
}

float bswap_F32(float input) {
    float result;

    char* BytesIn = (char*)&input;
    char* BytesOut = (char*)&result;

    BytesOut[0] = BytesIn[3];
    BytesOut[1] = BytesIn[2];
    BytesOut[2] = BytesIn[1];
    BytesOut[3] = BytesIn[0];

    return result;
}