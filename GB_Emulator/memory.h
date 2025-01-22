#pragma once
#include "common.h"
#include "cart.h"
#include "tile.h"

//forward declaration
class PPU;

class Mmu {
public:
	Mmu(cartridge* cart, bool testing);
	u8 read_byte(u16 address);
	void write_byte(u16 address, u8 byte);
	bool read_bit_reg(u16 address, u8 bit);
	void set_bit_reg(u16 address, u8 bit, u8 value);
	u8 raw_read(u16 address);
	tile read_tile(u16 address);
	u8 read_ppu_mode();
	void write_ppu_mode(u8 state);
	void set_ppu(PPU* ppu);
	

	


private:
	u8 memory_arr[common::memsize];
	cartridge* cart;
	bool testing;
	PPU* ppu = nullptr;
};
