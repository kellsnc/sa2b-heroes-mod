#pragma once

#define SWAPITSELF(n, func) n = func(n); 

Sint32 bswap_S32(Sint32 input);
Sint16 bswap_S16(Sint16 input);

float bswap_F32(float input);