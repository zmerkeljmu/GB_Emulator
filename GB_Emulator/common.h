#pragma once
#include <stdint.h>

typedef uint32_t u32;
typedef uint8_t u8;
typedef uint16_t u16; 

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;


namespace common {
	const u32 memsize = 0x10000;

}

enum flags
{
	Z_FLAG = 7,
	S_FLAG = 6,
	H_FLAG = 5,
	C_FLAG = 4
};

void u8set_bit(u8 bit,u8* reg, u8 value);

bool u8read_bit(u8 bit, u8* reg);
