#pragma once
#include <stdint.h>

typedef uint32_t u32;
typedef uint8_t u8;
typedef uint16_t u16; 

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;

class Cpu;

namespace common {
	const u32 memsize = 0x10000;
	const u32 IE = 0xFFFF;
	const u32 IF = 0xFF0F;

	const u32 CPU_SPEED = 4194304;
}

namespace interrupt {
	enum {
		JOYPAD = 4,
		SERIAL = 3,
		TIMER = 2,
		LCD = 1,
		VBLANK = 0
	};

	enum {
		JOYPAD_ADDR = 0x60,
		SERIAL_ADDR = 0x58,
		TIMER_ADDR = 0x50,
		LCD_ADDR = 0x48,
		VBLANK_ADDR = 0x40
	};
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

bool u16read_bit(u8 bit, u16* reg);
