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

struct RGBA {
	u8 r;
	u8 g;
	u8 b;
	u8 a;
};

const RGBA white = { 0x9B, 0XBC, 0X0F, 255 };
const RGBA light_gray = { 0x8B, 0xAC, 0x0F, 255 };
const RGBA dark_gray = { 0x30, 0x62, 0x30, 255 };
const RGBA black = { 0x0F, 0x38, 0x0F, 255 };

enum pixels {
	WHITE = 0,
	LIGHT_GRAY = 1,
	DARK_GRAY = 2,
	BLACK = 3
};

enum lcdc {
	PPU_ENABLE = 7,
	WIN_TILE_MAP = 6,
	WIN_ENABLE = 5,
	TILE_DATA = 4,
	BG_TILE_MAP = 3,
	OBJ_SIZE = 2,
	OBJ_ENABLE = 1,
	BG_ENABLE = 0
};

enum stat_reg {
	LYC_INT = 6,
	MODE_2 = 5,
	MODE_1 = 4,
	MODE_0 = 3,
	LYC_LY = 2,
	//ppu mode takes up lower 2 bits
};

const int OAM_CYCLES = 80;
const int PIXEL_CYCLES = 172;
const int HBLANK_CYCLES = 204;
const int VBLANK_CYCLES = 456;


namespace hardware_reg {
	enum MyEnum
	{
		JOYP = 0xFF00,
		SB = 0xFF01,
		SC = 0xFF02,
		DIVLOW = 0xFF03,
		DIV = 0xFF04,
		TIMA = 0xFF05,
		TMA = 0xFF06,
		TAC = 0xFF07,
		IF = 0xFF0F,
		//skipped audio related regs for now
		LCDC = 0xFF40,
		STAT = 0xFF41,
		SCY = 0xFF42,
		SCX = 0xFF43,
		LY = 0xFF44,
		LYC = 0xFF45,
		DMA = 0xFF46,
		BGP = 0xFF47,
		OBP0 = 0xFF48,
		OBP1 = 0xFF49,
		WY = 0xFF4A,
		WX = 0xFF4B,
		KEY1 = 0xFF4D,
		VBK = 0xFF4F,
		HDMA1 = 0xFF51,
		HDMA2 = 0xFF52,
		HDMA3 = 0xFF53,
		HDMA4 = 0xFF54,
		HDMA5 = 0xFF55,
		RP = 0xFF56,
		BCPS = 0xFF68,//BGPI
		BCPD = 0xFF69,//BGPD
		OCPS = 0xFF6A,//OBPI
		OCPD = 0xFF6B,//OBPD
		OPRI = 0xFF6C,
		SVBK = 0xFF70,
		//skipped more audio
		IE = 0xFFFF
	};
}

const u16 ROM_END = 0x7FFF;
const u16 VRAM_START = 0x8000;
const u16 VRAM_END = 0x9FFF;
const u16 OAM_START = 0xFE00;
const u16 OAM_END = 0xFE9F;
const u16 WRAM_START = 0xC000;
const u16 WRAM_END = 0xDFFF;
const u16 HRAM_START = 0xFF80;
const u16 HRAM_END = 0xFFFE;
const u16 EXTERNAL_START = 0xA000;
const u16 EXTERNAL_END = 0xBFFF;
const u16 ECHO_START = 0xE000;
const u16 ECHO_END = 0xFDFF;
const u16 IO_END = 0xFF7F;

const u16 MAP0_START = 0x9800;
const u16 MAP1_START = 0x9C00;