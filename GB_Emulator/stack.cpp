#include "stack.h"
#include "cpu.h"


void pop_2reg(Cpu* cpu, u8* high_reg, u8* low_reg) {
	*low_reg = cpu->mem->read_byte(cpu->sp);
	cpu->sp++;
	*high_reg = cpu->mem->read_byte(cpu->sp);
	cpu->sp++;
	return;
}


u8 popbc_C1(Cpu* cpu) {
	pop_2reg(cpu, &cpu->reg_b, &cpu->reg_c);
	return 3;
}
u8 popde_D1(Cpu* cpu) {
	pop_2reg(cpu, &cpu->reg_d, &cpu->reg_e);
	return 3;
}
u8 pophl_E1(Cpu* cpu) {
	pop_2reg(cpu, &cpu->reg_h, &cpu->reg_l);
	return 3;
}
u8 popaf_F1(Cpu* cpu) {
	pop_2reg(cpu, &cpu->reg_a, &cpu->reg_f);

	if (u8read_bit(Z_FLAG, &cpu->reg_f) == 1)
		cpu->set_zero_flag();
	else
		cpu->clear_zero_flag();
	if (u8read_bit(S_FLAG, &cpu->reg_f) == 1)
		cpu->set_s_flag();
	else
		cpu->clear_s_flag();
	if (u8read_bit(H_FLAG, &cpu->reg_f) == 1)
		cpu->set_hc_flag();
	else
		cpu->clear_hc_flag();
	if (u8read_bit(C_FLAG, &cpu->reg_f) == 1)
		cpu->set_carry_flag();
	else
		cpu->clear_carry_flag();
	return 3;
}


void push_reg(Cpu* cpu, u8* high_reg, u8* low_reg) {
	cpu->sp--;
	cpu->mem->write_byte(cpu->sp, *high_reg);
	cpu->sp--;
	cpu->mem->write_byte(cpu->sp, *low_reg);
	return;
}

u8 pushbc_C5(Cpu* cpu) {
	push_reg(cpu, &cpu->reg_b, &cpu->reg_c);
	return 4;
}
u8 pushde_D5(Cpu* cpu) {
	push_reg(cpu, &cpu->reg_d, &cpu->reg_e);
	return 4;
}
u8 pushhl_E5(Cpu* cpu) {
	push_reg(cpu, &cpu->reg_h, &cpu->reg_l);
	return 4;
}
u8 pushaf_F5(Cpu* cpu) {
	push_reg(cpu, &cpu->reg_a, &cpu->reg_f);
	return 4;
}

u8 addspi8_E8(Cpu* cpu) {
	i8 value = cpu->read_pc();
	u16 address = cpu->sp;

	if ((address & 0xFF) + value > 0xFF)
		cpu->set_carry_flag();
	else
		cpu->clear_carry_flag();
	if ((address & 0xF) + (value & 0xF) > 0xF)
		cpu->set_hc_flag();
	else
		cpu->clear_hc_flag();
	cpu->clear_zero_flag();
	cpu->clear_s_flag();

	cpu->sp += value;
	return 4;

}
u8 ldhlspi8_F8(Cpu* cpu) {
	i8 value = cpu->read_pc();
	u16 address = cpu->sp;

	if ((address & 0xFF) + value > 0xFF)
		cpu->set_carry_flag();
	else
		cpu->clear_carry_flag();
	if ((address & 0xF) + (value & 0xF) > 0xF)
		cpu->set_hc_flag();
	else
		cpu->clear_hc_flag();
	cpu->clear_zero_flag();
	cpu->clear_s_flag();

	cpu->write_hl(address + value);
	
	return 3;

}