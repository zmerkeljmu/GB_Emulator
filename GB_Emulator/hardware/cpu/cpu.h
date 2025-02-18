#pragma once
#include "common.h"
#include "memory.h"
#include "instruction.h"
#include "cart.h"
#include <fstream>
#include <iomanip>


class Cpu {

public :
	Cpu(Mmu* memory);

	void log_state();
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
	bool ime;
	bool pending_ei;
	bool cb;

	bool debug;

	Mmu *mem;


	u16 read_af();
	u16 read_bc();
	u16 read_de();
	u16 read_hl();

	void write_af(u16 value);
	void write_bc(u16 value);
	void write_de(u16 value);
	void write_hl(u16 value);

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

	bool handle_interrupts();
	bool read_bit_IE(int bit);
	bool read_bit_IF(int bit);
	void clear_bit_IF(int bit);
	void stack_push(u8* reg_from);
	void push_pc();
	void bootrom();

	u8 read_ie();
	u8 read_if();

	void write_ie(u8 byte);
	void write_if(u8 byte);


	u8 joyp = 0xCF;
	u8 buttons_state;
	u8 read_joyp();
	void write_joyp(u8 byte);

	u8 button_right;
	u8 button_left;
	u8 button_up;
	u8 button_down;
	u8 button_a;
	u8 button_b;
	u8 button_select;
	u8 button_start;

private:
	Instruction_list instruction_list;
	u8 ie_reg = 0b11100000;
	u8 if_reg = 0xE1;
};

