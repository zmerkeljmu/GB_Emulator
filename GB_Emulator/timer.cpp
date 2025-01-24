#include "timer.h"
#include <iostream>

Timer::Timer(Mmu* memory) {
	mem = memory;
}

//cycles here are m cycles
void Timer::tick(u8 cycles) {
	old_counter = counter;
	counter +=  cycles * 4; //converted to t cycles
	div = counter >> 8;
	do_tima();
	return;
}

void Timer::do_tima() {

	u32 freq = get_freq();
	u16 bit_select = freq >> 1;
	bool timer_enable = u8read_bit(timer::TIMER_ENABLE, &tac);

	//loop for each time the counter has increased
	for (u16 i = old_counter + 1; i < counter; i++) {
		bool bit = (i >> bit_select) & 1;
		bool and_result = bit && timer_enable;

		if (overflow) {
			std::cout << "TIMER OVERFLOW\n";
			overflow = false;
			tima = tma;
			mem->set_bit_reg(hardware_reg::IF, interrupt::TIMER, 1);
			
			printf("%x\n", mem->read_byte(hardware_reg::IF));
			printf("%x\n", mem->read_byte(hardware_reg::IE));

		}
		//inc tima
		if (prev_and && !and_result) {
			tima++;
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
		freq = common::CPU_SPEED / 4096; //every 256 m cycles (1024)
		break;
	case 1:
		freq = common::CPU_SPEED / 262144; //every 4 m cycles (16)
		break;
	case 2:
		freq = common::CPU_SPEED / 65536; //every 16 m cycles (64)
		break;
	case 3:
		freq = common::CPU_SPEED / 16384; //every 64 m cycles (256)
		break;
	}

	return freq;

}

u8 Timer:: read_tima() {
	return tima;
}
void Timer:: write_tima(u8 byte) {
	tima = byte;
}
u8 Timer:: read_tma() {
	return tma;
}
void Timer:: write_tma(u8 byte) {
	tma = byte;
}
u8 Timer:: read_div() {
	return div;
}
void Timer:: write_div(u8 byte) {
	div = 0;
	counter = 0;
	prev_and = false;
}
u8 Timer:: read_tac() {
	return tac;
}
void Timer::write_tac(u8 byte) {
	tac = byte;
}