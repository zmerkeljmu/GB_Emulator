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
	void update_counter(u16 val);
	void do_tima();
	Mmu* mem;
	u8 prev_and = false;
	u8 tima;
	u8 tma;
	u8 tac;
	u16 counter;
	bool tima_reload_cycle;
	u8 cycles_til_tima_irq = 0;
	void detect_edge(bool before, bool after);
};



namespace timer {

	enum
	{
		TIMER_ENABLE = 2
	};

}