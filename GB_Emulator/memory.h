#pragma once
#include "common.h"
#include "cart.h"

class mmu {
public:
	mmu(cartridge* cart);
	u8 read_byte(u16 address);

private:
	u8 memory_arr[common::memsize];
	cartridge* cart;

};