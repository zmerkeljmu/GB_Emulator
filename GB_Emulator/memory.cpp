#include "memory.h"

Mmu::Mmu(cartridge* cart, bool testing) : cart(cart), memory_arr{} {
	Mmu::testing = testing;
}


u8 Mmu::read_byte(u16 address) {
	if (address <= 0x7FFF)
		return cart->rom_data[address];
	if (address == 0xFF44)
		return 0x90;
	if (address == 0xFF00)
		return 0xFF;
	return memory_arr[address];
}

void Mmu::write_byte(u16 address, u8 byte) {
	if (address == 0xFF01) {
		printf("%c", byte);
		memory_arr[address] = byte;
	}
	
	if (address == hardware_reg::DIV) {
		memory_arr[address] = 0;
		memory_arr[hardware_reg::DIVLOW] = 0;
		return;
	}
	
	
	else {
		memory_arr[address] = byte;
	
	}

	return;
}

bool Mmu::read_bit_reg(u16 address, u8 bit) {
	u8 val = this->read_byte(address);
	return u8read_bit(bit, &val);
}

void Mmu::set_bit_reg(u16 address, u8 bit, u8 value) {
	u8 val = this->read_byte(address);
	u8set_bit(bit, &val, value);
	this->write_byte(address, val);
	return;
}

