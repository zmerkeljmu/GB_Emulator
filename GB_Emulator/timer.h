#pragma once
#include "common.h"
#include "memory.h"

class Timer {
public:
	Timer(Mmu* mmu);
	void tick(u8 cycles);
private:
	u32 get_freq();
	void do_tima(u16 counter, u16 old_counter);
	Mmu* mem;
	bool prev_and = false;
	bool overflow = false;
};


namespace timer {

	enum
	{
		TIMER_ENABLE = 2
	};

}