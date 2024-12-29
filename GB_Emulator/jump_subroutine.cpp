#include "jump_subroutine.h"
#include "cpu.h"

void stack_pop(Cpu* cpu, u8* reg_into) {
	*reg_into = cpu->mem->read_byte(cpu->sp);
	cpu->sp++;
	return;
}

void stack_push(Cpu* cpu, u8* reg_from) {
	cpu->mem->write_byte(cpu->sp, *reg_from);
	cpu->sp--;
	return;
}


u8 jrnzi8_20(Cpu* cpu) {
	u8 zero_flag = cpu->read_zero_flag();
	i8 value = cpu->read_pc();

	if (zero_flag == 1) {
		cpu->sp += value;
		return 3;
	}
	else {
		return 2;
	}
}
u8 jrnci8_30(Cpu* cpu) {
	u8 carry_flag = cpu->read_carry_flag();
	i8 value = cpu->read_pc();

	if (carry_flag == 1) {
		cpu->sp += value;
		return 3;
	}
	else {
		return 2;
	}
}

u8 jri8_18(Cpu* cpu) {
	i8 value = cpu->read_pc();
	cpu->sp += value;
	return 3;
}
u8 jrzi8_28(Cpu* cpu) {
	u8 zero_flag = cpu->read_zero_flag();
	i8 value = cpu->read_pc();

	if (zero_flag == 0) {
		cpu->sp += value;
		return 3;
	}
	else {
		return 2;
	}

}
u8 jrci8_38(Cpu* cpu) {
	u8 carry_flag = cpu->read_carry_flag();
	i8 value = cpu->read_pc();

	if (carry_flag == 0) {
		cpu->sp += value;
		return 3;
	}
	else {
		return 2;
	}
}

u8 retnz_C0(Cpu* cpu) {
	u8 low8;
	u8 high8;
	
	if (cpu->read_zero_flag() == 0) {
		stack_pop(cpu, &low8);
		stack_pop(cpu, &high8);
		cpu->pc = (u16)low8 | ((u16)high8 << 8);
		return 5;
	}
	else {
		return 2;
	}
}


u8 retnc_D0(Cpu* cpu) {
	u8 low8;
	u8 high8;

	if (cpu->read_carry_flag() == 0) {
		stack_pop(cpu, &low8);
		stack_pop(cpu, &high8);
		cpu->pc = (u16)low8 | ((u16)high8 << 8);
		return 5;
	}
	else {
		return 2;
	}
}

u8 jpnzu16_C2(Cpu* cpu) {
	u8 low8;
	u8 high8;

	low8 = cpu->read_pc();
	high8 = cpu->read_pc();

	if (cpu->read_zero_flag() == 0) {
		cpu->pc = (u16)low8 | ((u16)high8 << 8);
		return 4;
	}
	return 3;
}
u8 jpncu16_D2(Cpu* cpu) {
	u8 low8;
	u8 high8;

	low8 = cpu->read_pc();
	high8 = cpu->read_pc();

	if (cpu->read_carry_flag() == 0) {
		cpu->pc = (u16)low8 | ((u16)high8 << 8);
		return 4;
	}
	return 3;
}

u8 jpu16_C3(Cpu* cpu) {
	u8 low8;
	u8 high8;

	low8 = cpu->read_pc();
	high8 = cpu->read_pc();
	cpu->pc = (u16)low8 | ((u16)high8 << 8);
	return 4;
}

void calln16(Cpu* cpu) {
	u16 low_jmp = cpu->read_pc();
	u16 high_jmp = cpu->read_pc();

	u8 low = (u8)cpu->pc;
	u8 high = (u8)((cpu->pc) >> 8);
	stack_push(cpu, &high);
	stack_push(cpu, &low);
	
	cpu->pc = (high_jmp << 8) | low_jmp;
	return;
}

u8 callnzu16_C4(Cpu* cpu) {
	if (cpu->read_zero_flag() == 0) {
		calln16(cpu);
		return 6;
	}
	else {
		cpu->read_pc();
		cpu->read_pc();
		return 3;
	}
}
u8 callncu16_D4(Cpu* cpu) {

	if (cpu->read_carry_flag() == 0) {
		calln16(cpu);
		return 6;
	}
	else {
		cpu->read_pc();
		cpu->read_pc();
		return 3;
	}
}

void rst(Cpu* cpu, u16 low) {
	u16 high = 0x00 << 8;

	u16 address_jmp = low | high;
	
	u8 low_push = (u8)cpu->pc;
	u8 high_push = (u8)((cpu->pc) >> 8);
	stack_push(cpu, &high_push);
	stack_push(cpu, &low_push);
	return;
}

u8 rst00h_C7(Cpu* cpu) {
	u16 low = 0x00;
	rst(cpu, low);
	return 4;
}
u8 rst10h_D7(Cpu* cpu) {
	u16 low = 0x10;
	rst(cpu, low);
	return 4;
}
u8 rst20h_E7(Cpu* cpu) {
	u16 low = 0x20;
	rst(cpu, low);
	return 4;
}
u8 rst30h_F7(Cpu* cpu) {
	u16 low = 0x30;
	rst(cpu, low);
	return 4;
}

u8 retz_C8(Cpu* cpu) {
	u8 low8;
	u8 high8;

	if (cpu->read_zero_flag() == 1) {
		stack_pop(cpu, &low8);
		stack_pop(cpu, &high8);
		cpu->pc = (u16)low8 | ((u16)high8 << 8);
		return 5;
	}
	else {
		return 2;
	}
}
u8 retc_D8(Cpu* cpu) {
	u8 low8;
	u8 high8;

	if (cpu->read_carry_flag() == 1) {
		stack_pop(cpu, &low8);
		stack_pop(cpu, &high8);
		cpu->pc = (u16)low8 | ((u16)high8 << 8);
		return 5;
	}
	else {
		return 2;
	}
}

u8 ret_C9(Cpu* cpu) {
	u8 low8;
	u8 high8;

	stack_pop(cpu, &low8);
	stack_pop(cpu, &high8);
	cpu->pc = (u16)low8 | ((u16)high8 << 8);
	return 4;
}

//unimplemented
u8 reti_D9(Cpu* cpu);

u8 jphl_E9(Cpu* cpu) {
	cpu->pc = cpu->read_hl();
	return 1;
}

u8 jpzu16_CA(Cpu* cpu) {
	u16 low = cpu->read_pc();
	u16 high = cpu->read_pc();
	u16 address = low | (high << 8);

	if (cpu->read_zero_flag() == 0) {
		cpu->pc = address;
		return 4;
	}
	return 3;
}
u8 jpcu16_DA(Cpu* cpu) {
	u16 low = cpu->read_pc();
	u16 high = cpu->read_pc();
	u16 address = low | (high << 8);

	if (cpu->read_carry_flag() == 0) {
		cpu->pc = address;
		return 4;
	}
	return 3;
}

u8 callzu16_CC(Cpu* cpu) {
	if (cpu->read_zero_flag() == 1) {
		calln16(cpu);
		return 6;
	}
	else {
		cpu->read_pc();
		cpu->read_pc();
		return 3;
	}
}
u8 callcu16_DC(Cpu* cpu) {
	if (cpu->read_carry_flag() == 1) {
		calln16(cpu);
		return 6;
	}
	else {
		cpu->read_pc();
		cpu->read_pc();
		return 3;
	}
}

u8 callu16_CD(Cpu* cpu) {
	calln16(cpu);
	return 6;
}

u8 rst08h_CF(Cpu* cpu) {
	u16 low = 0x08;
	rst(cpu, low);
	return 4;
}
u8 rst18h_DF(Cpu* cpu) {
	u16 low = 0x18;
	rst(cpu, low);
	return 4;
}
u8 rst28h_EF(Cpu* cpu) {
	u16 low = 0x28;
	rst(cpu, low);
	return 4;
}
u8 rst38h_FF(Cpu* cpu) {
	u16 low = 0x38;
	rst(cpu, low);
	return 4;
}
