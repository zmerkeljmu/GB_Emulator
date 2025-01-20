#pragma once
#include "common.h"
#include "cart.h"
#include "tile.h"

class Mmu {
public:
	Mmu(cartridge* cart, bool testing);
	u8 read_byte(u16 address);
	void write_byte(u16 address, u8 byte);
	bool read_bit_reg(u16 address, u8 bit);
	void set_bit_reg(u16 address, u8 bit, u8 value);
	u8 raw_read(u16 address);
	tile read_tile(u16 address);

private:
	u8 memory_arr[common::memsize];
	cartridge* cart;
	bool testing;

};

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