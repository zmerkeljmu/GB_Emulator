#include "timer.h"
#include <iostream>

Timer::Timer(Mmu* memory) {
	mem = memory;
	counter = 0xabcc;
	tima = 0x00;
	tma = 0x00;
	tac = 0xF8;
	tima_reload_cycle = false;
}

void Timer::tick(u8 cycles) {
	u8 tcycles = cycles * 4;
	for (int i = 0; i < tcycles; i++) {
		do_tima();
	}
}

void Timer::do_tima() {
	tima_reload_cycle = false;
	if (cycles_til_tima_irq > 0) {
		cycles_til_tima_irq--;
		if (cycles_til_tima_irq == 0) {
			mem->write_byte(hardware_reg::IF, mem->read_byte(hardware_reg::IF) | (1 << interrupt::TIMER));
			tima = tma;
			tima_reload_cycle = true;
		}
	}
	update_counter(counter + 1);
}

void Timer::update_counter(u16 val) {
	counter = val;
	u8 and_result = 0;
	switch (tac & 3) //check first 2 bits
	{
	case 0:
		and_result = (counter >> 9) & 1;
		break;
	case 1:
		and_result = (counter >> 3) & 1;
		break;
	case 2:
		and_result = (counter >> 5) & 1;
		break;
	case 3:
		and_result = (counter >> 7) & 1;
		break;
	}
	and_result &= ((tac & 4) >> 2);
	detect_edge(prev_and, and_result);
	prev_and = and_result;

}

void Timer::detect_edge(bool before, bool after) {
	if (before && !after) {
		tima++;
		if (tima == 0) {
			cycles_til_tima_irq = 4;
		}
	}
}

u8 Timer:: read_tima() {
	return tima;
}
void Timer::write_tima(u8 byte) {
	if (!tima_reload_cycle) {
		tima = byte;
	}
	if (cycles_til_tima_irq == 1) {
		cycles_til_tima_irq = 0;
	}
}

u8 Timer:: read_tma() {
	return tma;
}
void Timer::write_tma(u8 byte) {
	if (tima_reload_cycle) {
		tima = byte;
	}
	tma = byte;
}

u8 Timer:: read_div() {
	return (counter >> 8) && 0xFF;
}
void Timer:: write_div(u8 byte) {
	update_counter(0);
}
u8 Timer:: read_tac() {
	return 0b11111000 | tac;
}
void Timer::write_tac(u8 byte) {
	bool prev = prev_and;
	prev_and &= ((byte & 4) >> 2);
	detect_edge(prev, prev_and);
	tac = byte;
}