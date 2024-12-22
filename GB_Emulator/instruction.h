#pragma once
#include "common.h"

class Cpu;


typedef u8(*opcode_func)(Cpu*);

struct instruction {
	u8 bytes;
	const char* name;
	opcode_func function;
};

class Instruction_list {

public:
	Instruction_list() {
		base[0x00] = { 1, "NOP", nullptr};
		
	}

	instruction base[0x100];
	instruction cb[0x100];
};
