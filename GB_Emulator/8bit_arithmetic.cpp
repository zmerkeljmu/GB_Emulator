#include "cpu.h"
#include "8bit_arithmetic.h"

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
	cpu->reg_a = (u8) result;
	return;
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
	cpu->reg_a = (u8) result;
	return;
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
	cpu->reg_a = result;
	return;
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

	cpu->reg_a = result;
	return;
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


void and_rtor(Cpu* cpu, u8* reg) {
	u8 result = cpu->reg_a & *reg;
	
	if (result == 0)
		cpu->set_zero_flag();
	else
		cpu->clear_zero_flag();
	cpu->clear_s_flag();
	cpu->set_hc_flag();
	cpu->clear_carry_flag();

	cpu->reg_a = result;
	return;

}


u8 andb_A0(Cpu* cpu) {
	and_rtor(cpu, &cpu->reg_b);
	return 1;
}
u8 andc_A1(Cpu* cpu) {
	and_rtor(cpu, &cpu->reg_c);
	return 1;
}
u8 andd_A2(Cpu* cpu) {
	and_rtor(cpu, &cpu->reg_d);
	return 1;
}
u8 ande_A3(Cpu* cpu) {
	and_rtor(cpu, &cpu->reg_e);
	return 1;
}
u8 andh_A4(Cpu* cpu) {
	and_rtor(cpu, &cpu->reg_h);
	return 1;
}
u8 andl_A5(Cpu* cpu) {
	and_rtor(cpu, &cpu->reg_l);
	return 1;
}
u8 andhl_A6(Cpu* cpu) {
	u8 val = cpu->mem->read_byte(cpu->read_hl());
	and_rtor(cpu, &val);
	return 2;
}
u8 anda_A7(Cpu* cpu) {
	and_rtor(cpu, &cpu->reg_a);
	return 1;
}
u8 andi8_E6(Cpu* cpu) {
	u8 i8 = cpu->read_pc();
	and_rtor(cpu, &i8);
	return 2;
}

void xor_rtor(Cpu* cpu, u8* reg) {
	u8 result = cpu->reg_a ^ *reg;
	if (result == 0)
		cpu->set_zero_flag();
	else
		cpu->clear_zero_flag();
	cpu->clear_carry_flag();
	cpu->clear_hc_flag();
	cpu->clear_s_flag();
	
	cpu->reg_a = result;
	return;
}

u8 xorb_A8(Cpu* cpu) {
	xor_rtor(cpu, &cpu->reg_b);
	return 1;
}
u8 xorc_A9(Cpu* cpu) {
	xor_rtor(cpu, &cpu->reg_c);
	return 1;
}
u8 xord_AA(Cpu* cpu) {
	xor_rtor(cpu, &cpu->reg_d);
	return 1;
}
u8 xore_AB(Cpu* cpu) {
	xor_rtor(cpu, &cpu->reg_e);
	return 1;
}
u8 xorh_AC(Cpu* cpu) {
	xor_rtor(cpu, &cpu->reg_h);
	return 1;
}
u8 xorl_AD(Cpu* cpu) {
	xor_rtor(cpu, &cpu->reg_l);
	return 1;
}
u8 xorhl_AE(Cpu* cpu) {
	u8 val = cpu->mem->read_byte(cpu->read_hl());
	xor_rtor(cpu, &val);
	return 2;
}
u8 xora_AF(Cpu* cpu) {
	xor_rtor(cpu, &cpu->reg_a);
	return 1;
}
u8 xori8_EE(Cpu* cpu) {
	u8 i8 = cpu->read_pc();
	xor_rtor(cpu, &i8);
	return 2;
}

void or_rtor(Cpu* cpu, u8* reg) {
	u8 result = cpu->reg_a | *reg;
	if (result == 0)
		cpu->set_zero_flag();
	else
		cpu->clear_zero_flag();
	cpu->clear_s_flag();
	cpu->clear_hc_flag();
	cpu->clear_carry_flag();
	
	cpu->reg_a = result;
	return;
}

u8 orb_B0(Cpu* cpu) {
	or_rtor(cpu, &cpu->reg_b);
	return 1;
}
u8 orc_B1(Cpu* cpu) {
	or_rtor(cpu, &cpu->reg_c);
	return 1;
}
u8 ord_B2(Cpu* cpu) {
	or_rtor(cpu, &cpu->reg_d);
	return 1;
}
u8 ore_B3(Cpu* cpu) {
	or_rtor(cpu, &cpu->reg_e);
	return 1;
}
u8 orh_B4(Cpu* cpu) {
	or_rtor(cpu, &cpu->reg_h);
	return 1;
}
u8 orl_B5(Cpu* cpu) {
	or_rtor(cpu, &cpu->reg_l);
	return 1;
}
u8 orhl_B6(Cpu* cpu) {
	u8 val = cpu->mem->read_byte(cpu->read_hl());
	or_rtor(cpu, &val);
	return 2;
} 
u8 ora_B7(Cpu* cpu) {
	or_rtor(cpu, &cpu->reg_l);
	return 1;
}
u8 ori8_F6(Cpu* cpu){
	u8 i8 = cpu->read_pc();
	or_rtor(cpu, &i8);
	return 2;
}

void cp_rtor(Cpu* cpu, u8* reg) {
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
	return;
}


u8 cpb_B8(Cpu* cpu) {
	cp_rtor(cpu, &cpu->reg_b);
	return 1;
}
u8 cpc_B9(Cpu* cpu) {
	cp_rtor(cpu, &cpu->reg_c);
	return 1;
}
u8 cpd_BA(Cpu* cpu) {
	cp_rtor(cpu, &cpu->reg_d);
	return 1;
}
u8 cpe_BB(Cpu* cpu) {
	cp_rtor(cpu, &cpu->reg_e);
	return 1;
}
u8 cph_BC(Cpu* cpu) {
	cp_rtor(cpu, &cpu->reg_h);
	return 1;
}
u8 cpl_BD(Cpu* cpu) {
	cp_rtor(cpu, &cpu->reg_l);
	return 1;
}
u8 cphl_BE(Cpu* cpu) {
	u8 val = cpu->mem->read_byte(cpu->read_hl());
	cp_rtor(cpu, &val);
	return 2;
}
u8 cpa_BF(Cpu* cpu) {
	cp_rtor(cpu, &cpu->reg_a);
	return 1;
}
u8 cpi8_FE(Cpu* cpu) {
	u8 i8 = cpu->read_pc();
	cp_rtor(cpu, &i8);
	return 2;
}

void inc_reg(Cpu* cpu, u8* reg) {
	u8 reg_in = *reg;
	
	*reg++;
	if (*reg == 0)
		cpu->set_zero_flag();
	else
		cpu->clear_zero_flag();
	cpu->set_s_flag();

	if ((reg_in & 0xF) + 1 > 0xF)
		cpu->set_hc_flag();
	else
		cpu->clear_hc_flag();

	return;
}

u8 incd_14(Cpu* cpu) {
	inc_reg(cpu, &cpu->reg_d);
	return 1;
}
u8 inch_24(Cpu* cpu) {
	inc_reg(cpu, &cpu->reg_h);
	return 1;
}
u8 incb_04(Cpu* cpu) {
	inc_reg(cpu, &cpu->reg_b);
	return 1;
}
u8 inchl_34(Cpu* cpu) {
	u16 address = cpu->read_hl();
	u8 byte_in_mem = cpu->mem->read_byte(address);
	byte_in_mem++;
	cpu->mem->write_byte(address, byte_in_mem);
	return 3;
}
u8 incc_0C(Cpu* cpu) {
	inc_reg(cpu, &cpu->reg_c);
	return 1;
}
u8 ince_1C(Cpu* cpu) {
	inc_reg(cpu, &cpu->reg_e);
	return 1;
}
u8 incl_2C(Cpu* cpu) {
	inc_reg(cpu, &cpu->reg_l);
	return 1;
}
u8 inca_3C(Cpu* cpu) {
	inc_reg(cpu, &cpu->reg_a);
	return 1;
}

void dec_reg(Cpu* cpu, u8* reg) {
	u8 reg_in = *reg;

	*reg--;
	if (*reg == 0)
		cpu->set_zero_flag();
	else
		cpu->clear_zero_flag();
	cpu->set_s_flag();

	if (((*reg & 0x0F) - 1) < 0)
		cpu->set_hc_flag();
	else
		cpu->clear_hc_flag();

	return;
}

u8 decb_05(Cpu* cpu) {
	dec_reg(cpu, &cpu->reg_b);
	return 1;
}
u8 decd_15(Cpu* cpu) {
	dec_reg(cpu, &cpu->reg_d);
	return 1;
}
u8 dech_25(Cpu* cpu) {
	dec_reg(cpu, &cpu->reg_h);
	return 1;
}
u8 dechl_35(Cpu* cpu) {
	u16 address = cpu->read_hl();
	u8 byte_in_mem = cpu->mem->read_byte(address);
	byte_in_mem--;
	cpu->mem->write_byte(address, byte_in_mem);
	return 3;
}
u8 decc_0D(Cpu* cpu) {
	dec_reg(cpu, &cpu->reg_c);
	return 1;
}
u8 dece_1D(Cpu* cpu) {
	dec_reg(cpu, &cpu->reg_e);
	return 1;
}
u8 decl_2D(Cpu* cpu) {
	dec_reg(cpu, &cpu->reg_l);
	return 1;
}
u8 deca_3D(Cpu* cpu) {
	dec_reg(cpu, &cpu->reg_a);
	return 1;
}