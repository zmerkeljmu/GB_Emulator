#include "bit_shift.h"
#include "cpu.h"

void rlc(Cpu* cpu, u8* reg) {
	u8 carryout = u8read_bit(7, reg);
	*reg = *reg << 1;
	u8set_bit(0, reg, carryout);
	
	if (*reg == 0)
		cpu->set_zero_flag();
	else
		cpu->clear_zero_flag();
	if (carryout == 1)
		cpu->set_carry_flag();
	else
		cpu->clear_carry_flag();
	cpu->clear_s_flag();
	cpu->clear_hc_flag();
	return;
}

u8 rlcb_00(Cpu* cpu) {
	rlc(cpu, &cpu->reg_b);
	return 2;
}
u8 rlcc_01(Cpu* cpu) {
	rlc(cpu, &cpu->reg_c);
	return 2;
}
u8 rlcd_02(Cpu* cpu) {
	rlc(cpu, &cpu->reg_d);
	return 2;
}
u8 rlce_03(Cpu* cpu) {
	rlc(cpu, &cpu->reg_e);
	return 2;
}
u8 rlch_04(Cpu* cpu) {
	rlc(cpu, &cpu->reg_h);
	return 2;
}
u8 rlcl_05(Cpu* cpu) {
	rlc(cpu, &cpu->reg_l);
	return 2;
}
u8 rlchl_06(Cpu* cpu) {
	u8 val = cpu->mem->read_byte(cpu->read_hl());

	u8 carryout = u8read_bit(7, &val);
	val = val << 1;
	u8set_bit(0, &val, carryout);

	if (val == 0)
		cpu->set_zero_flag();
	else
		cpu->clear_zero_flag();
	if (carryout == 1)
		cpu->set_carry_flag();
	else
		cpu->clear_carry_flag();
	cpu->clear_s_flag();
	cpu->clear_hc_flag();

	cpu->mem->write_byte(cpu->read_hl(), val);
	return 4;
}

u8 cbrlca_07(Cpu* cpu) {
	rlc(cpu, &cpu->reg_a);
	return 2;
}


void rrc(Cpu* cpu, u8* reg) {
	u8 carryout = u8read_bit(0, reg);
	*reg = *reg >> 1;
	u8set_bit(7, reg, carryout);
	if (carryout == 1)
		cpu->set_carry_flag();
	else
		cpu->clear_carry_flag();
	if (*reg == 0)
		cpu->set_zero_flag();
	else
		cpu->clear_zero_flag();
	cpu->clear_s_flag();
	cpu->clear_hc_flag();
	return;
}

u8 rrcb_08(Cpu* cpu) {
	rrc(cpu, &cpu->reg_b);
	return 2;
}
u8 rrcc_09(Cpu* cpu) {
	rrc(cpu, &cpu->reg_c);
	return 2;
}
u8 rrcd_0A(Cpu* cpu) {
	rrc(cpu, &cpu->reg_d);
	return 2;
}
u8 rrce_0B(Cpu* cpu) {
	rrc(cpu, &cpu->reg_e);
	return 2;
}
u8 rrch_0C(Cpu* cpu) {
	rrc(cpu, &cpu->reg_h);
	return 2;
}
u8 rrcl_0D(Cpu* cpu) {
	rrc(cpu, &cpu->reg_l);
	return 2;
}
u8 rrchl_0E(Cpu* cpu) {
	u8 val = cpu->mem->read_byte(cpu->read_hl());
	u8 carryout = u8read_bit(0, &val);
	val = val >> 1;
	u8set_bit(7, &val, carryout);
	if (carryout == 1)
		cpu->set_carry_flag();
	else
		cpu->clear_carry_flag();
	if (val == 0)
		cpu->set_zero_flag();
	else
		cpu->clear_zero_flag();
	cpu->clear_s_flag();
	cpu->clear_hc_flag();
	cpu->mem->write_byte(cpu->read_hl(), val);
	return 4;

}
u8 cbrrca_0F(Cpu* cpu) {
	rrc(cpu, &cpu->reg_a);
	return 2;
}

void rl(Cpu* cpu, u8* reg) {
	u8 carryin = cpu->read_carry_flag();
	u8 carryout = u8read_bit(7, reg);

	*reg = *reg << 1;
	u8set_bit(0, reg, carryin);
	if (carryout == 1)
		cpu->set_carry_flag();
	else
		cpu->clear_carry_flag();
	cpu->clear_s_flag();
	cpu->clear_hc_flag();
	if (*reg == 0)
		cpu->set_zero_flag();
	else
		cpu->clear_zero_flag();
	return;
}

u8 rlb_10(Cpu* cpu) {
	rl(cpu, &cpu->reg_b);
	return 2;
}
u8 rlc_11(Cpu* cpu) {
	rl(cpu, &cpu->reg_c);
	return 2;
}
u8 rld_12(Cpu* cpu) {
	rl(cpu, &cpu->reg_d);
	return 2;
}
u8 rle_13(Cpu* cpu) {
	rl(cpu, &cpu->reg_e);
	return 2;
}
u8 rlh_14(Cpu* cpu) {
	rl(cpu, &cpu->reg_h);
	return 2;
}
u8 rll_15(Cpu* cpu) {
	rl(cpu, &cpu->reg_l);
	return 2;
}
u8 rlhl_16(Cpu* cpu) {
	u8 val = cpu->mem->read_byte(cpu->read_hl());
	rl(cpu, &val);
	cpu->mem->write_byte(cpu->read_hl(), val);
	return 4;
}
u8 cbrla_17(Cpu* cpu) {
	rl(cpu, &cpu->reg_a);
	return 2;
}

void rr(Cpu* cpu, u8* reg) {
	u8 carryin = cpu->read_carry_flag();
	u8 carryout = u8read_bit(0, reg);

	*reg = *reg >> 1;
	u8set_bit(7, reg, carryin);
	if (carryout == 1)
		cpu->set_carry_flag();
	else
		cpu->clear_carry_flag();
	cpu->clear_s_flag();
	cpu->clear_hc_flag();
	if (*reg == 0)
		cpu->set_zero_flag();
	else
		cpu->clear_zero_flag();
	return;
}

u8 rrb_18(Cpu* cpu) {
	rr(cpu, &cpu->reg_b);
	return 2;
}
u8 rrc_19(Cpu* cpu) {
	rr(cpu, &cpu->reg_c);
	return 2;
}
u8 rrd_1A(Cpu* cpu) {
	rr(cpu, &cpu->reg_d);
	return 2;
}
u8 rre_1B(Cpu* cpu) {
	rr(cpu, &cpu->reg_e);
	return 2;
}
u8 rrh_1C(Cpu* cpu) {
	rr(cpu, &cpu->reg_h);
	return 2;
}
u8 rrl_1D(Cpu* cpu) {
	rr(cpu, &cpu->reg_l);
	return 2;
}
u8 rrhl_1E(Cpu* cpu) {
	u8 val = cpu->mem->read_byte(cpu->read_hl());
	rr(cpu, &val);
	cpu->mem->write_byte(cpu->read_hl(), val);
	return 4;
}
u8 cbrra_1F(Cpu* cpu) {
	rr(cpu, &cpu->reg_a);
	return 2;
}

void sla(Cpu* cpu, u8* reg) {
	u8 carryout = u8read_bit(7, reg);
	*reg = *reg << 1;
	if (*reg == 0)
		cpu->set_zero_flag();
	else
		cpu->clear_zero_flag();
	cpu->clear_s_flag();
	cpu->clear_hc_flag();
	if (carryout == 1)
		cpu->set_carry_flag();
	else
		cpu->clear_carry_flag();
	return;
}

u8 slab_20(Cpu* cpu) {
	sla(cpu, &cpu->reg_b);
	return 2;
}
u8 slac_21(Cpu* cpu) {
	sla(cpu, &cpu->reg_c);
	return 2;
}
u8 slad_22(Cpu* cpu) {
	sla(cpu, &cpu->reg_d);
	return 2;
}
u8 slae_23(Cpu* cpu) {
	sla(cpu, &cpu->reg_e);
	return 2;
}
u8 slah_24(Cpu* cpu) {
	sla(cpu, &cpu->reg_h);
	return 2;
}
u8 slal_25(Cpu* cpu) {
	sla(cpu, &cpu->reg_l);
	return 2;
}
u8 slahl_26(Cpu* cpu) {
	u8 val = cpu->mem->read_byte(cpu->read_hl());
	sla(cpu, &val);
	cpu->mem->write_byte(cpu->read_hl(), val);
	return 4;
}
u8 slaa_27(Cpu* cpu) {
	sla(cpu, &cpu->reg_a);
	return 2;
}

void sra(Cpu* cpu, u8* reg) {
	u8 carryout = u8read_bit(0, reg);
	u8 bit7 = u8read_bit(7, reg);
	*reg = *reg >> 1;
	u8set_bit(7, reg, bit7);
	if (*reg == 0)
		cpu->set_zero_flag();
	else
		cpu->clear_zero_flag();
	cpu->clear_s_flag();
	cpu->clear_hc_flag();
	if (carryout == 1)
		cpu->set_carry_flag();
	else
		cpu->clear_carry_flag();
	return;
}

u8 srab_28(Cpu* cpu) {
	sra(cpu, &cpu->reg_b);
	return 2;
}
u8 srac_29(Cpu* cpu) {
	sra(cpu, &cpu->reg_c);
	return 2;
}
u8 srad_2A(Cpu* cpu) {
	sra(cpu, &cpu->reg_d);
	return 2;
}
u8 srae_2B(Cpu* cpu) {
	sra(cpu, &cpu->reg_e);
	return 2;
}
u8 srah_2C(Cpu* cpu) {
	sra(cpu, &cpu->reg_h);
	return 2;
}
u8 sral_2D(Cpu* cpu) {
	sra(cpu, &cpu->reg_l);
	return 2;
}
u8 srahl_2E(Cpu* cpu) {
	u8 val = cpu->mem->read_byte(cpu->read_hl());
	sra(cpu, &val);
	cpu->mem->write_byte(cpu->read_hl(), val);
	return 4;
}
u8 sraa_2F(Cpu* cpu) {
	sra(cpu, &cpu->reg_a);
	return 2;
}

void swap(Cpu* cpu, u8* reg) {
	u8 result = (*reg << 4) | (*reg >> 4);
	if (result == 0)
		cpu->set_zero_flag();
	else
		cpu->clear_zero_flag();
	cpu->clear_s_flag();
	cpu->clear_hc_flag();
	cpu->clear_carry_flag();
	*reg = result;
	return;

}

u8 swapb_30(Cpu* cpu) {
	swap(cpu, &cpu->reg_b);
	return 2;
}
u8 swapc_31(Cpu* cpu) {
	swap(cpu, &cpu->reg_c);
	return 2;
}
u8 swapd_32(Cpu* cpu) {
	swap(cpu, &cpu->reg_d);
	return 2;
}
u8 swape_33(Cpu* cpu) {
	swap(cpu, &cpu->reg_e);
	return 2;
}
u8 swaph_34(Cpu* cpu) {
	swap(cpu, &cpu->reg_h);
	return 2;
}
u8 swapl_35(Cpu* cpu) {
	swap(cpu, &cpu->reg_l);
	return 2;
}
u8 swaphl_36(Cpu* cpu) {
	u8 val = cpu->mem->read_byte(cpu->read_hl());
	swap(cpu, &val);
	cpu->mem->write_byte(cpu->read_hl(), val);
	return 4;
}
u8 swapa_37(Cpu* cpu) {
	swap(cpu, &cpu->reg_a);
	return 2;
}

void srl(Cpu* cpu, u8* reg) {
	u8 carryout = u8read_bit(0, reg);
	*reg = *reg >> 1;
	if (carryout == 1)
		cpu->set_carry_flag();
	else
		cpu->clear_carry_flag();
	if (*reg == 0)
		cpu->set_zero_flag();
	else
		cpu->clear_zero_flag();
	cpu->clear_s_flag();
	cpu->clear_hc_flag();
	return;
}

u8 srlb_38(Cpu* cpu) {
	srl(cpu, &cpu->reg_b);
	return 2;
}
u8 srlc_39(Cpu* cpu) {
	srl(cpu, &cpu->reg_c);
	return 2;
}
u8 srld_3A(Cpu* cpu) {
	srl(cpu, &cpu->reg_d);
	return 2;
}
u8 srle_3B(Cpu* cpu) {
	srl(cpu, &cpu->reg_e);
	return 2;
}
u8 srlh_3C(Cpu* cpu) {
	srl(cpu, &cpu->reg_h);
	return 2;
}
u8 srll_3D(Cpu* cpu) {
	srl(cpu, &cpu->reg_l);
	return 2;
}
u8 srlhl_3E(Cpu* cpu) {
	u8 val = cpu->mem->read_byte(cpu->read_hl());
	srl(cpu, &val);
	cpu->mem->write_byte(cpu->read_hl(), val);
	return 4;
}
u8 srla_3F(Cpu* cpu) {
	srl(cpu, &cpu->reg_a);
	return 2;
}