#include "misc_inst.h"
#include "cpu.h"


u8 nop_00(Cpu* cpu) {
	return 1;
}
u8 stop_10(Cpu* cpu) {
	return 0;
}

u8 halt_76(Cpu* cpu) {
	cpu->halted = true;
	return 1;
}

//requires ime/interrupts
u8 di_F4(Cpu* cpu) {
	cpu->ime = false;
	cpu->pending_ei = false;
	return 1;
}

u8 cb_CB(Cpu* cpu) {
	cpu->cb = true;
	return 1;
}

u8 ei_FB(Cpu* cpu) {
	cpu->pending_ei = true;
	return 1;
}

//carry flag instructions

u8 cpl_2F(Cpu* cpu) {
	cpu->reg_a = ~cpu->reg_a;
	cpu->set_s_flag();
	cpu->set_hc_flag();
	return 1;
}
u8 ccf_3F(Cpu* cpu) {
	if (cpu->read_carry_flag() == 1)
		cpu->clear_carry_flag();
	else
		cpu->set_carry_flag();
	cpu->clear_s_flag();
	cpu->clear_hc_flag();
	return 1;
}

u8 daa_27(Cpu* cpu) {
	u8 adjustment = 0;
	u16 result;
	
	if (cpu->read_s_flag() == 1) {
		if (cpu->read_hc_flag())
			adjustment += 0x6;
		if (cpu->read_carry_flag())
			adjustment += 0x60;
		result = cpu->reg_a - adjustment;
		cpu->reg_a -= adjustment;

	} else {
		if (cpu->read_hc_flag() == 1 || (cpu->reg_a & 0xF) > 0x9)
			adjustment += 0x6;
		if (cpu->read_carry_flag() == 1 || (cpu->reg_a > 0x99)) {
			adjustment += 0x60;
			cpu->set_carry_flag();
		}
		cpu->reg_a += adjustment;
	}

	if (cpu->reg_a == 0)
		cpu->set_zero_flag();
	else
		cpu->clear_zero_flag();
	cpu->clear_hc_flag();
	return 1;
}

u8 scf_37(Cpu* cpu) {
	cpu->clear_hc_flag();
	cpu->clear_s_flag();
	cpu->set_carry_flag();
	return 1;
}