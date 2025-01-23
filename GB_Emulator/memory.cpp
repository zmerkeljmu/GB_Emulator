#include "memory.h"
#include "ppu.h"
#include "cpu.h"
#include "timer.h"

Mmu::Mmu(cartridge* cart, bool testing) {
	this->cart = cart;
	Mmu::testing = testing;
}


u8 Mmu::read_byte(u16 address) {
	if (address <= ROM_END)
		return cart->read_rom(address);
	if (address <= VRAM_END)
		return ppu->read_vram(address);
	if (address <= WRAM_END)
		return wram[address - WRAM_START];
	if (address <= ECHO_END)//echo ram
		return 0;
	if (address <= OAM_END)
		return ppu->read_oam_ram(address);
	if (address <= 0xFEFF)//prohibited area
		return 0;
	if (address <= IO_END) {//IO registers
		if (address == hardware_reg::JOYP)
			return 0xFF;
		else if (address == hardware_reg::SB)
			return 0xFF;
		else if (address == hardware_reg::SC)
			return 0xFF;
		else if (address == hardware_reg::DIV)
			return timer->read_div();
		else if (address == hardware_reg::TIMA)
			return timer->read_tima();
		else if (address == hardware_reg::TMA)
			return timer->read_tma();
		else if (address == hardware_reg::TAC)
			return timer->read_tac();
		else if (address == hardware_reg::IF)
			return cpu->read_if();
		else if (address >= 0xFF10 && address <= 0xFF3F)
			return 0xFF;
		else if (address == hardware_reg::LCDC)
			return ppu->read_lcdc();
		else if (address == hardware_reg::STAT)
			return ppu->read_stat();
		else if (address == hardware_reg::SCY)
			return ppu->read_scy();
		else if (address == hardware_reg::SCX)
			return ppu->read_scx();
		else if (address == hardware_reg::LY)
			return ppu->read_ly();
		else if (address == hardware_reg::LYC)
			return ppu->read_lyc();
		else if (address == hardware_reg::DMA)//UNIMPLEMENTED
			return 0xFF;
		else if (address == hardware_reg::BGP)
			return ppu->read_bgp();
		else if (address == hardware_reg::OBP0)
			return ppu->read_obp0();
		else if (address == hardware_reg::OBP1)
			return ppu->read_obp1();
		else if (address == hardware_reg::WY)
			return ppu->read_wy();
		else if (address == hardware_reg::WX)
			return ppu->read_wx();
		else {
			printf("ERROR READ NOT IMPLEMENTED FOR %d", address);
			exit(0);
		}
	}
	if (address <= HRAM_END)
		return hram[address - HRAM_START];
	if (address == hardware_reg::IE)
		return cpu->read_ie();
}

void Mmu::write_byte(u16 address, u8 byte) {
	if (address <= ROM_END)
		return;
	else if (address <= VRAM_END)
		ppu->write_vram(address, byte);
	else if (address <= WRAM_END)
		wram[address - WRAM_START] = byte;
	else if (address <= ECHO_END)//echo ram
		return;
	else if (address <= OAM_END)
		ppu->write_oam_ram(address, byte);
	else if (address <= 0xFEFF)//prohibited area
		return;
	else if (address <= IO_END) {//IO registers
		if (address == hardware_reg::JOYP)//mixed write/read register
			return;
		else if (address == hardware_reg::SB) {
			printf("%c", byte);
			return;
		}
		else if (address == hardware_reg::SC)
			return;
		else if (address == hardware_reg::DIV)
			timer->write_div(byte);
		else if (address == hardware_reg::TIMA)
			timer->write_tima(byte);
		else if (address == hardware_reg::TMA)
			timer->write_tma(byte);
		else if (address == hardware_reg::TAC)
			timer->write_tac(byte);
		else if (address == hardware_reg::IF)
			cpu->write_if(byte);
		else if (address >= 0xFF10 && address <= 0xFF3F)
			return;
		else if (address == hardware_reg::LCDC)
			ppu->write_lcdc(byte);
		else if (address == hardware_reg::STAT)
			ppu->write_stat(byte);
		else if (address == hardware_reg::SCY)
			ppu->write_scy(byte);
		else if (address == hardware_reg::SCX)
			ppu->write_scx(byte);
		else if (address == hardware_reg::LY)
			return;
		else if (address == hardware_reg::LYC)
			return ppu->write_lyc(byte);
		else if (address == hardware_reg::DMA)//UNIMPLEMENTED
			return;
		else if (address == hardware_reg::BGP)
			return ppu->write_bgp(byte);
		else if (address == hardware_reg::OBP0)
			return ppu->write_obp0(byte);
		else if (address == hardware_reg::OBP1)
			return ppu->write_obp1(byte);
		else if (address == hardware_reg::WY)
			return ppu->write_wy(byte);
		else if (address == hardware_reg::WX)
			return ppu->write_wx(byte);
		else {
			printf("ERROR READ NOT IMPLEMENTED FOR %d", address);
			exit(0);
		}
	}
	else if (address <= HRAM_END)
		hram[address - HRAM_START] = byte;
	else if (address == hardware_reg::IE)
		cpu->write_ie(byte);
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

void Mmu::set_ppu(PPU* ppu) {
	this->ppu = ppu;
}

void Mmu::set_cpu(Cpu* cpu) {
	this->cpu = cpu;
}

void Mmu::set_timer(Timer* timer) {
	this->timer = timer;
}