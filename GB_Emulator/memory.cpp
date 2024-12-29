#include "memory.h"

Mmu::Mmu(cartridge* cart) : cart(cart), memory_arr{} {}


u8 Mmu::read_byte(u16 address) {

	return memory_arr[address];
}

void Mmu::write_byte(u16 address, u8 byte) {
	memory_arr[address] = byte;
	return;
}

