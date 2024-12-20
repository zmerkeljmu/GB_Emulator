#pragma once
#include "common.h"
#include "memory.h"
#include "instruction.h"

class Cpu {

public :
	Cpu(mmu* memory);

	int step();

	instruction fetch_instruction();

	u16 sp;
	u16 pc;

	u8 reg_a;
	u8 reg_f;
	u8 reg_b;
	u8 reg_c;
	u8 reg_d;
	u8 reg_e;
	u8 reg_h;
	u8 reg_l;

	bool halted;

	mmu *mem;

private:
	Instruction_list instruction_list;
};
