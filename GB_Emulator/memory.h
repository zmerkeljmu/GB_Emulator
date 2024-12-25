#pragma once
#include "common.h"
#include "cart.h"

class Mmu {
public:
	Mmu(cartridge* cart);
	u8 read_byte(u16 address);
	void write_byte(u16 address, u8 byte);

private:
	u8 memory_arr[common::memsize];
	cartridge* cart;

};