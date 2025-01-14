#include "timer.h"
#include <iostream>

Timer::Timer(Mmu* memory) {
	mem = memory;
}

//cycles here are m cycles
void Timer::tick(u8 cycles) {
	u16 old_counter = (mem->read_byte(hardware_reg::DIV) << 8) | (mem->read_byte(hardware_reg::DIVLOW));
	u16 counter = old_counter;
	counter +=  cycles * 4; //converted to t cycles
	
	u8 high = (u8) (counter >> 8);
	u8 low = counter & 0xFF;
	mem->write_byte(hardware_reg::DIV, high);
	mem->write_byte(hardware_reg::DIVLOW, low);

	do_tima(counter, old_counter);
	return;
}

void Timer::do_tima(u16 counter, u16 old_counter) {

	u32 freq = get_freq();
	u16 bit_select = freq >> 1;
	bool timer_enable = mem->read_bit_reg(hardware_reg::TAC, timer::TIMER_ENABLE);

	//loop for each time the counter has increased
	for (int i = old_counter + 1; i < counter; i++) {
		bool bit = bit_select & i;
		bool and_result = bit && timer_enable;

		if (overflow) {
			//std::cout << "TIMER OVERFLOW\n";
			overflow = false;
			mem->write_byte(hardware_reg::TIMA, mem->read_byte(hardware_reg::TMA));
			mem->set_bit_reg(hardware_reg::IF, interrupt::TIMER, 1);
			//printf("%x\n", mem->read_byte(hardware_reg::IF));
			//printf("%x\n", mem->read_byte(hardware_reg::IE));

		}

		//inc tima
		if (prev_and && !and_result) {
			u8 tima = mem->read_byte(hardware_reg::TIMA) + 1;
			//printf("tima = %d\n", tima);
			mem->write_byte(hardware_reg::TIMA, tima);
			overflow = tima == 0;
		}
		prev_and = and_result;
	}
	return;
}

u32 Timer::get_freq() {

	u32 freq = 0;
	u8 tac = mem->read_byte(hardware_reg::TAC);
	switch (tac & 3) //check first 2 bits
	{
	case 0:
		freq = common::CPU_SPEED / 4096; //every 256 m cycles
		break;
	case 1:
		freq = common::CPU_SPEED / 262144; //every 4 m cycles
		break;
	case 2:
		freq = common::CPU_SPEED / 65536; //every 16 m cycles
		break;
	case 3:
		freq = common::CPU_SPEED / 16384; //every 64 m cycles
		break;
	}

	return freq;

}