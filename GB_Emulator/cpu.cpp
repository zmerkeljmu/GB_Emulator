#include "cpu.h"
#include "cart.h"


Cpu::Cpu(mmu* memory) {
	
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

	mem = memory;

}

int Cpu::step() {
	int cycles;
	
	//fetch
	instruction inst = fetch_instruction();
	//decode
	//execute
	cycles = inst.function(this);

	return cycles;
}

instruction Cpu::fetch_instruction() {
	u8 opcode = this->read_pc();

	instruction inst = instruction_list.base[opcode];
	
	//this line is wrong i think
	pc += inst.bytes - 1;

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

