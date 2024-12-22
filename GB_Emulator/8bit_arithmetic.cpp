#include "cpu.h"

void add_rtor(Cpu* cpu, u8* reg) {
	u16 result = cpu->reg_a;
	result += *reg;
	
	//check for overflow
	if (result > 0xFF)
		cpu->set_carry_flag();
	else
		cpu->clear_carry_flag();
	//check for 4 bit overflow
	if (((*reg & 0xF) + (cpu->reg_a & 0xF)) > 0xF)
		cpu->set_hc_flag();
	else
		cpu->clear_hc_flag();
	//check zero flag
	if (result == 0)
		cpu->set_zero_flag();
	else
		cpu->clear_zero_flag();
}

u8 addb_80(Cpu* cpu){
	add_rtor(cpu, &cpu->reg_b);
	return 1;
}
u8 addc_81(Cpu* cpu){
	add_rtor(cpu, &cpu->reg_c);
	return 1;
}
u8 addd_82(Cpu* cpu){
	add_rtor(cpu, &cpu->reg_d);
	return 1;
}
u8 adde_83(Cpu* cpu){
	add_rtor(cpu, &cpu->reg_e);
	return 1;
}
u8 addh_84(Cpu* cpu){
	add_rtor(cpu, &cpu->reg_h);
	return 1;
}
u8 addl_85(Cpu* cpu) {
	add_rtor(cpu, &cpu->reg_l);
	return 1;
}
u8 addhl_86(Cpu* cpu) {
	u8 val = cpu->mem->read_byte(cpu->read_hl());
	add_rtor(cpu, &val);
	return 2;
}
u8 adda_87(Cpu* cpu) {
	add_rtor(cpu, &cpu->reg_a);
	return 1;
}
u8 addi8_C6(Cpu* cpu) {
	u8 i8 = cpu->read_pc();
	add_rtor(cpu, &i8);
	return 2;
}


void adc_rtor(Cpu* cpu, u8* reg) {
	u16 result = cpu->reg_a;
	result += *reg + cpu->read_carry_flag();


	//check for 4 bit overflow
	if (((*reg & 0xF) + (cpu->reg_a & 0xF)) + cpu->read_carry_flag() > 0xF)
		cpu->set_hc_flag();
	else
		cpu->clear_hc_flag();
	//check zero flag
	if (result == 0)
		cpu->set_zero_flag();
	else
		cpu->clear_zero_flag();
	//check for overflow
	if (result > 0xFF)
		cpu->set_carry_flag();
	else
		cpu->clear_carry_flag();
}

u8 adcb_88(Cpu* cpu) {
	adc_rtor(cpu, &cpu->reg_b);
	return 1;
}
u8 adcc_89(Cpu* cpu) {
	adc_rtor(cpu, &cpu->reg_c);
	return 1;
}
u8 adcd_8A(Cpu* cpu) {
	adc_rtor(cpu, &cpu->reg_d);
	return 1;
}
u8 adce_8B(Cpu* cpu) {
	adc_rtor(cpu, &cpu->reg_e);
	return 1;
}
u8 adch_8C(Cpu* cpu) {
	adc_rtor(cpu, &cpu->reg_h);
	return 1;
}
u8 adcl_8D(Cpu* cpu) {
	adc_rtor(cpu, &cpu->reg_l);
	return 1;
}
u8 adchl_8E(Cpu* cpu) {
	u8 val = cpu->mem->read_byte(cpu->read_hl());
	adc_rtor(cpu, &val);
	return 2;
}
u8 adca_8F(Cpu* cpu) {
	adc_rtor(cpu, &cpu->reg_a);
	return 1;
}
u8 adci8_CE(Cpu* cpu) {
	u8 i8 = cpu->read_pc();
	adc_rtor(cpu, &i8);
	return 2;
}

//(A&mask) - (B&mask) - carry_in < 0
void sub_rtor(Cpu* cpu, u8* reg) {
	u8 result = cpu->reg_a - *reg;

	cpu->set_s_flag();
	if (*reg > cpu->reg_a)
		cpu->set_carry_flag();
	else
		cpu->clear_carry_flag();

	if (((cpu->reg_a & 0x0F) - (*reg & 0x0F)) < 0)
		cpu->set_hc_flag();
	else
		cpu->clear_hc_flag();
	
	if (result == 0)
		cpu->set_zero_flag();
	else
		cpu->clear_zero_flag();
}


u8 subb_90(Cpu* cpu) {
	sub_rtor(cpu, &cpu->reg_b);
	return 1;
}
u8 subc_91(Cpu* cpu) {
	sub_rtor(cpu, &cpu->reg_c);
	return 1;
}
u8 subd_92(Cpu* cpu) {
	sub_rtor(cpu, &cpu->reg_d);
	return 1;
}
u8 sube_93(Cpu* cpu) {
	sub_rtor(cpu, &cpu->reg_e);
	return 1;
}
u8 subh_94(Cpu* cpu) {
	sub_rtor(cpu, &cpu->reg_h);
	return 1;
}
u8 subl_95(Cpu* cpu) {
	sub_rtor(cpu, &cpu->reg_l);
	return 1;
}
u8 subhl_96(Cpu* cpu) {
	u8 val = cpu->mem->read_byte(cpu->read_hl());
	sub_rtor(cpu, &val);
	return 2;
}
u8 suba_97(Cpu* cpu) {
	sub_rtor(cpu, &cpu->reg_a);
	return 1;
}
u8 subi8_D6(Cpu* cpu) {
	u8 i8 = cpu->read_pc();
	sub_rtor(cpu, &i8);
	return 2;
}

//(A&mask) - (B&mask) - carry_in < 0
void sbc_rtor(Cpu* cpu, u8* reg) {
	u8 carry_in = cpu->read_carry_flag();
	u8 result = cpu->reg_a - *reg - carry_in;

	cpu->set_s_flag();
	if (*reg + carry_in > cpu->reg_a)
		cpu->set_carry_flag();
	else
		cpu->clear_carry_flag();

	if (((cpu->reg_a & 0x0F) - (*reg & 0x0F) - carry_in) < 0)
		cpu->set_hc_flag();
	else
		cpu->clear_hc_flag();

	if (result == 0)
		cpu->set_zero_flag();
	else
		cpu->clear_zero_flag();
}

u8 sbcb_98(Cpu* cpu) {
	sbc_rtor(cpu, &cpu->reg_b);
	return 1;
}
u8 sbcc_99(Cpu* cpu) {
	sbc_rtor(cpu, &cpu->reg_c);
	return 1;
}
u8 sbcd_9A(Cpu* cpu) {
	sbc_rtor(cpu, &cpu->reg_d);
	return 1;
}
u8 sbce_9B(Cpu* cpu) {
	sbc_rtor(cpu, &cpu->reg_e);
	return 1;
}
u8 sbch_9C(Cpu* cpu) {
	sbc_rtor(cpu, &cpu->reg_h);
	return 1;
}
u8 sbcl_9D(Cpu* cpu) {
	sbc_rtor(cpu, &cpu->reg_l);
	return 1;
}
u8 sbchl_9E(Cpu* cpu) {
	u8 val = cpu->mem->read_byte(cpu->read_hl());
	sbc_rtor(cpu, &val);
	return 2;
}
u8 sbca_9F(Cpu* cpu) {
	sbc_rtor(cpu, &cpu->reg_a);
	return 1;
}
u8 sbci8_DE(Cpu* cpu) {
	u8 i8 = cpu->read_pc();
	sbc_rtor(cpu, &i8);
	return 2;
}
