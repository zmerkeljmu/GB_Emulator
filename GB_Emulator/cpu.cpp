#include "cpu.h"
#include "cart.h"


Cpu::Cpu(Mmu* memory) {
	
	pc = 0x100;
	sp = 0xFFFE;
	reg_a = 0x01;
	reg_f = 0xB0;
	reg_b = 0x00;
	reg_c = 0x13;
	reg_d = 0x00;
	reg_e = 0xD8;
	reg_h = 0x01;
	reg_l = 0x4D;

	halted = false;
	cb = false;
	mem = memory;

}

int Cpu::step() {
	bool set_ime = this->pending_ei;
	int cycles;
	
	//fetch
	instruction inst = fetch_instruction();
	//decode
	//execute
	cycles = inst.function(this);

	if (set_ime) {
		this->ime = 1;
		this->pending_ei = false;
	}
	return cycles;
}

instruction Cpu::fetch_instruction() {
	u8 opcode = this->read_pc();
	instruction inst;
	if (!this->cb) 
		inst = instruction_list.base[opcode];
	else {
		inst = instruction_list.cb[opcode];
		this->cb = false;
	}
	return inst;
}

u8 Cpu::read_pc() {
	u8 res = this->mem->read_byte(this->pc);
	pc++;
	return res;
}

void Cpu::set_carry_flag() {
	u8set_bit(C_FLAG, &this->reg_f, 1);
}

void Cpu::clear_carry_flag() {
	u8set_bit(C_FLAG, &this->reg_f, 0);
}

bool Cpu::read_carry_flag() {
	return u8read_bit(C_FLAG, &this->reg_f);
}

void Cpu::set_hc_flag() {
	u8set_bit(H_FLAG, &this->reg_f, 1);
}

void Cpu::clear_hc_flag() {
	u8set_bit(H_FLAG, &this->reg_f, 0);
}

bool Cpu::read_hc_flag() {
	return u8read_bit(H_FLAG, &this->reg_f);

}

void Cpu::set_s_flag() {
	u8set_bit(S_FLAG, &this->reg_f, 1);
}

void Cpu::clear_s_flag() {
	u8set_bit(S_FLAG, &this->reg_f, 0);
}

bool Cpu::read_s_flag() {
	return u8read_bit(S_FLAG, &this->reg_f);

}

void Cpu::set_zero_flag() {
	u8set_bit(Z_FLAG, &this->reg_f, 1);
}

void Cpu::clear_zero_flag() {
	u8set_bit(Z_FLAG, &this->reg_f, 0);
}

bool Cpu::read_zero_flag() {
	return u8read_bit(Z_FLAG, &this->reg_f);
}

void Cpu::print_flags() {
	printf("F register: %#02x\nZero Flag: %d\nS Flag: %d\nH Flag: %d\nC Flag: %d\n", this->reg_f, this->read_zero_flag(), this->read_s_flag(), this->read_hc_flag(), this->read_carry_flag());
}


u16 Cpu::read_af() {
	u16 a = reg_a;
	u16 f = reg_f;
	return (a << 8) | f;
}

u16 Cpu::read_bc() {
	u16 b = reg_b;
	u16 c = reg_c;
	return (b << 8) | c;
}
u16 Cpu::read_de() {
	u16 d = reg_d;
	u16 e = reg_e;
	return (d << 8) | e;
}
u16 Cpu::read_hl() {
	u16 h = reg_h;
	u16 l = reg_l;
	return (h << 8) | l;
}

void Cpu::write_af(u16 value) {
	u8 high_bits = (u8) (value >> 8);
	u8 low_bits = (u8) value;
	this->reg_a = high_bits;
	this->reg_f = low_bits;
}

void Cpu::write_bc(u16 value) {
	u8 high_bits = (u8) (value >> 8);
	u8 low_bits = (u8) value;
	this->reg_b = high_bits;
	this->reg_c = low_bits;
}

void Cpu::write_de(u16 value) {
	u8 high_bits = (u8)(value >> 8);
	u8 low_bits = (u8) value;
	this->reg_d = high_bits;
	this->reg_e = low_bits;
}

void Cpu::write_hl(u16 value) {
	u8 high_bits = (u8)(value >> 8);
	u8 low_bits = (u8) value;
	this->reg_h = high_bits;
	this->reg_l = low_bits;
}
