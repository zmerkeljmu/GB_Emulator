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


	u16 read_af();
	u16 read_bc();
	u16 read_de();
	u16 read_hl();

	u8 read_pc();

	void print_flags();

	void set_zero_flag();
	void clear_zero_flag();
	bool read_zero_flag();
	void set_s_flag();
	void clear_s_flag();
	bool read_s_flag();
	void set_hc_flag();
	void clear_hc_flag();
	bool read_hc_flag();
	void set_carry_flag();
	void clear_carry_flag();
	bool read_carry_flag();

private:
	Instruction_list instruction_list;
};
