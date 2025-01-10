#include "common.h"

void u8set_bit(u8 bit, u8* reg, u8 value) {
	//setting to 1
	if (value == 1) {
		*reg = *reg | (value << bit);
	}
	//setting to 0
	else {
		*reg = *reg & ~(1 << bit);
	}
	return;
}

bool u8read_bit(u8 bit, u8* reg) {
	return (*reg >> bit) & 0x01;
}