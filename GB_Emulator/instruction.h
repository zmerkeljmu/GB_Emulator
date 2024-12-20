#pragma once
#include "common.h"
#include "cpu.h"

typedef u8 (*opcode_func)(Cpu*);


struct instruction {
	u8 bytes;
	char* name;
	opcode_func function;
};

class Instruction_list {

public:
	Instruction_list() {
		base[0x00] = {};
		
		
		
	}

	instruction base[0x100];
	instruction cb[0x100];
};


