#include "jump_subroutine.h"
#include "cpu.h"


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

u8 retnz_C0(Cpu* cpu);
u8 retnc_D0(Cpu* cpu);

u8 jpnzu16_C2(Cpu* cpu);
u8 jpncu16_D2(Cpu* cpu);

u8 jpu16_C3(Cpu* cpu);

u8 callnzu16_C4(Cpu* cpu);
u8 callncu16_D4(Cpu* cpu);

u8 rst00h_C7(Cpu* cpu);
u8 rst10h_D7(Cpu* cpu);
u8 rst20h_E7(Cpu* cpu);
u8 rst30h_F7(Cpu* cpu);

u8 retz_C8(Cpu* cpu);
u8 retc_D8(Cpu* cpu);

u8 ret_C9(Cpu* cpu);
u8 reti_D9(Cpu* cpu);
u8 jphl_E9(Cpu* cpu);

u8 jpzu16_CA(Cpu* cpu);
u8 jpcu16_DA(Cpu* cpu);

u8 callzu16_CC(Cpu* cpu);
u8 callcu16_DC(Cpu* cpu);

u8 callu16_CD(Cpu* cpu);

u8 rst08h_CF(Cpu* cpu);
u8 rst18h_DF(Cpu* cpu);
u8 rst28h_EF(Cpu* cpu);
u8 rst38h_FF(Cpu* cpu);