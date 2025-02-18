#pragma once
#include "common.h"
#include "cart.h"
#include "tile.h"

//forward declaration
class PPU;
class Cpu;
class Timer;

class Mmu {
public:
	Mmu(cartridge* cart, bool testing);
	virtual u8 read_byte(u16 address);
	virtual void write_byte(u16 address, u8 byte);
	virtual bool read_bit_reg(u16 address, u8 bit);
	virtual void set_bit_reg(u16 address, u8 bit, u8 value);
	void set_ppu(PPU* ppu);
	void set_cpu(Cpu* cpu);
	void set_timer(Timer* timer);

private:
	u8 wram[WRAM_END - WRAM_START + 1] = {};
	u8 hram[HRAM_END - HRAM_START + 1] = {};
	cartridge* cart;
	bool testing;
	PPU* ppu = nullptr;
	Cpu* cpu = nullptr;
	Timer* timer = nullptr;
	void execute_dma(u8 address);
	u8 dma = 0xFF;

};

