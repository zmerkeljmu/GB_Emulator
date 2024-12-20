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
	u8 opcode = this->mem->read_byte(this->pc);

	instruction inst = instruction_list.base[opcode];
	pc += inst.bytes;

	return inst;
}





