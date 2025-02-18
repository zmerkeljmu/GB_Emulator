#include "16bit_arithmetic.h"
#include "cpu.h"


u8 incbc_03(Cpu* cpu) {
	cpu->write_bc(cpu->read_bc() + 1);
	return 2;
}
u8 incde_13(Cpu* cpu) {
	cpu->write_de(cpu->read_de() + 1);
	return 2;
}
u8 inchl_23(Cpu* cpu) {
	cpu->write_hl(cpu->read_hl() + 1);
	return 2;
}
u8 incsp_33(Cpu* cpu) {
	cpu->sp += 1;
	return 2;
}

u8 decbc_0B(Cpu* cpu) {
	cpu->write_bc(cpu->read_bc() - 1);
	return 2;
}
u8 decde_1B(Cpu* cpu) {
	cpu->write_de(cpu->read_de() - 1);
	return 2;
}
u8 dechl_2B(Cpu* cpu) {
	cpu->write_hl(cpu->read_hl() - 1);
	return 2;
}
u8 decsp_3B(Cpu* cpu) {
	cpu->sp -= 1;
	return 2;
}

u8 addbc_09(Cpu* cpu) {
	u16 hl = cpu->read_hl();
	u16 bc = cpu->read_bc();
	u32 result = hl + bc;

	cpu->clear_s_flag();

	if (result > 0xFFFF)
		cpu->set_carry_flag();
	else
		cpu->clear_carry_flag();
	if ((hl & 0xFFF) + (bc & 0xFFF) > 0xFFF)
		cpu->set_hc_flag();
	else
		cpu->clear_hc_flag();

	cpu->write_hl((u16) result);
	return 2;
}
u8 addde_19(Cpu* cpu) {
	u16 hl = cpu->read_hl();
	u16 de = cpu->read_de();
	u32 result = hl + de;

	cpu->clear_s_flag();

	if (result > 0xFFFF)
		cpu->set_carry_flag();
	else
		cpu->clear_carry_flag();
	if ((hl & 0xFFF) + (de & 0xFFF) > 0xFFF)
		cpu->set_hc_flag();
	else
		cpu->clear_hc_flag();

	cpu->write_hl((u16)result);
	return 2;
}
u8 addhl_29(Cpu* cpu) {
	u16 hl = cpu->read_hl();
	u32 result = hl + hl;

	cpu->clear_s_flag();

	if (result > 0xFFFF)
		cpu->set_carry_flag();
	else
		cpu->clear_carry_flag();
	if ((hl & 0xFFF) + (hl & 0xFFF) > 0xFFF)
		cpu->set_hc_flag();
	else
		cpu->clear_hc_flag();

	cpu->write_hl((u16)result);
	return 2;
}
u8 addsp_39(Cpu* cpu) {
	u16 hl = cpu->read_hl();
	u16 sp = cpu->sp;
	u32 result = hl + sp;

	cpu->clear_s_flag();

	if (result > 0xFFFF)
		cpu->set_carry_flag();
	else
		cpu->clear_carry_flag();
	if ((hl & 0xFFF) + (sp & 0xFFF) > 0xFFF)
		cpu->set_hc_flag();
	else
		cpu->clear_hc_flag();

	cpu->write_hl((u16)result);
	return 2;
}


