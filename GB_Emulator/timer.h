#pragma once
#include "common.h"
#include "memory.h"

class Timer {
public:
	Timer(Mmu* mmu);
	void tick(u8 cycles);

	u8 read_tima();
	void write_tima(u8 byte);
	u8 read_tma();
	void write_tma(u8 byte);
	u8 read_div();
	void write_div(u8 byte);
	u8 read_tac();
	void write_tac(u8 byte);

private:
	u32 get_freq();
	void do_tima();
	Mmu* mem;
	bool prev_and = false;
	bool overflow = false;
	u8 tima = 0x00;
	u8 tma = 0x00;
	u8 div = 0xAB;
	u8 tac = 0xF8;
	u16 counter = 0xAB00;
	u16 old_counter = 0xAB00;
};


namespace timer {

	enum
	{
		TIMER_ENABLE = 2
	};

}