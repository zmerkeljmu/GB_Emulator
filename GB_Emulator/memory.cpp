#include "memory.h"

Mmu::Mmu(cartridge* cart, bool testing) : cart(cart), memory_arr{} {
	Mmu::testing = testing;
}


u8 Mmu::read_byte(u16 address) {
	if (address <= 0x7FFF)
		return cart->rom_data[address];
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

u8 Mmu::raw_read(u16 address) {
	return memory_arr[address];
}

tile Mmu::read_tile(u16 address) {
	tile cur_tile;
	for (int line = 0; line < 8; line++) {
		u8 low_byte = raw_read(address + (line * 2));
		u8 high_byte = raw_read(address + (line * 2) + 1);

		for (int i = 0; i < 8; i++) {
			cur_tile.data[line][i] = ((high_byte >> (7 - i)) & 1) << 1 | ((low_byte >> (7 - i)) & 1);
		}
	}
	return cur_tile;
}

u8 Mmu::read_ppu_mode() {
	u8 stat = raw_read(hardware_reg::STAT);
	return stat & 0b11;
}

void Mmu::write_ppu_mode(u8 state) {
	u8 stat = raw_read(hardware_reg::STAT);
	stat &= 0b11111100;
	stat |= state;
	write_byte(hardware_reg::STAT, stat);
}
