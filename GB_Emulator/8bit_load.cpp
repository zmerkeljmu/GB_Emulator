#include "8bit_load.h"
#include "cpu.h"

void ld_reg_to_reg(Cpu* cpu, u8* write_reg, u8* read_reg) {
	*write_reg = *read_reg;
	return;
}

void ld_reg_to_mem(Cpu* cpu, u8* reg, u16 address) {
	cpu->mem->write_byte(address, *reg);
	return;
}

void ld_mem_to_reg(Cpu* cpu, u8* reg, u16 address) {
	*reg = cpu->mem->read_byte(address);
	return;
}

u8 ldbb_40(Cpu* cpu) {
	ld_reg_to_reg(cpu, &cpu->reg_b, &cpu->reg_b);
	return 1;
}
u8 ldbc_41(Cpu* cpu) {
	ld_reg_to_reg(cpu, &cpu->reg_b, &cpu->reg_c);
	return 1;
}
u8 ldbd_42(Cpu* cpu) {
	ld_reg_to_reg(cpu, &cpu->reg_b, &cpu->reg_d);
	return 1;
}
u8 ldbe_43(Cpu* cpu) {
	ld_reg_to_reg(cpu, &cpu->reg_b, &cpu->reg_e);
	return 1;
}
u8 ldbh_44(Cpu* cpu) {
	ld_reg_to_reg(cpu, &cpu->reg_b, &cpu->reg_h);
	return 1;
}
u8 ldbl_45(Cpu* cpu) {
	ld_reg_to_reg(cpu, &cpu->reg_b, &cpu->reg_l);
	return 1;
}
u8 ldbhl_46(Cpu* cpu) {
	u16 hl = cpu->read_hl();
	ld_mem_to_reg(cpu, &cpu->reg_b, hl);
	return 2;
}
u8 ldba_47(Cpu* cpu) {
	ld_reg_to_reg(cpu, &cpu->reg_b, &cpu->reg_a);
	return 1;
}
u8 ldcb_48(Cpu* cpu) {
	ld_reg_to_reg(cpu, &cpu->reg_c, &cpu->reg_b);
	return 1;
}
u8 ldcc_49(Cpu* cpu) {
	ld_reg_to_reg(cpu, &cpu->reg_c, &cpu->reg_c);
	return 1;
}
u8 ldcd_4A(Cpu* cpu) {
	ld_reg_to_reg(cpu, &cpu->reg_c, &cpu->reg_d);
	return 1;
}
u8 ldce_4B(Cpu* cpu) {
	ld_reg_to_reg(cpu, &cpu->reg_c, &cpu->reg_e);
	return 1;
}
u8 ldch_4C(Cpu* cpu) {
	ld_reg_to_reg(cpu, &cpu->reg_c, &cpu->reg_h);
	return 1;
}
u8 ldcl_4D(Cpu* cpu) {
	ld_reg_to_reg(cpu, &cpu->reg_c, &cpu->reg_l);
	return 1;
}
u8 ldchl_4E(Cpu* cpu) {
	u16 hl = cpu->read_hl();
	ld_mem_to_reg(cpu, &cpu->reg_c, hl);
	return 2;
}
u8 ldca_4F(Cpu* cpu) {
	ld_reg_to_reg(cpu, &cpu->reg_c, &cpu->reg_a);
	return 1;
}

u8 lddb_50(Cpu* cpu) {
	ld_reg_to_reg(cpu, &cpu->reg_d, &cpu->reg_b);
	return 1;
}
u8 lddc_51(Cpu* cpu) {
	ld_reg_to_reg(cpu, &cpu->reg_d, &cpu->reg_c);
	return 1;
}
u8 lddd_52(Cpu* cpu) {
	ld_reg_to_reg(cpu, &cpu->reg_d, &cpu->reg_d);
	return 1;
}
u8 ldde_53(Cpu* cpu) {
	ld_reg_to_reg(cpu, &cpu->reg_d, &cpu->reg_e);
	return 1;
}
u8 lddh_54(Cpu* cpu) {
	ld_reg_to_reg(cpu, &cpu->reg_d, &cpu->reg_h);
	return 1;
}
u8 lddl_55(Cpu* cpu) {
	ld_reg_to_reg(cpu, &cpu->reg_d, &cpu->reg_l);
	return 1;
}
u8 lddhl_56(Cpu* cpu) {
	u16 hl = cpu->read_hl();
	ld_mem_to_reg(cpu, &cpu->reg_d, hl);
	return 2;
}
u8 ldda_57(Cpu* cpu) {
	ld_reg_to_reg(cpu, &cpu->reg_d, &cpu->reg_a);
	return 1;
}
u8 ldeb_58(Cpu* cpu) {
	ld_reg_to_reg(cpu, &cpu->reg_e, &cpu->reg_b);
	return 1;
}
u8 ldec_59(Cpu* cpu) {
	ld_reg_to_reg(cpu, &cpu->reg_e, &cpu->reg_c);
	return 1;
}
u8 lded_5A(Cpu* cpu) {
	ld_reg_to_reg(cpu, &cpu->reg_e, &cpu->reg_d);
	return 1;
}
u8 ldee_5B(Cpu* cpu) {
	ld_reg_to_reg(cpu, &cpu->reg_e, &cpu->reg_e);
	return 1;
}
u8 ldeh_5C(Cpu* cpu) {
	ld_reg_to_reg(cpu, &cpu->reg_e, &cpu->reg_h);
	return 1;
}
u8 ldel_5D(Cpu* cpu) {
	ld_reg_to_reg(cpu, &cpu->reg_e, &cpu->reg_l);
	return 1;
}
u8 ldehl_5E(Cpu* cpu) {
	u16 hl = cpu->read_hl();
	ld_mem_to_reg(cpu, &cpu->reg_e, hl);
	return 2;
}
u8 ldea_5F(Cpu* cpu) {
	ld_reg_to_reg(cpu, &cpu->reg_e, &cpu->reg_a);
	return 1;
}

u8 ldhc_61(Cpu* cpu) {
	ld_reg_to_reg(cpu, &cpu->reg_h, &cpu->reg_c);
	return 1;
}
u8 ldhd_62(Cpu* cpu) {
	ld_reg_to_reg(cpu, &cpu->reg_h, &cpu->reg_d);
	return 1;
}
u8 ldhb_60(Cpu* cpu) {
	ld_reg_to_reg(cpu, &cpu->reg_h, &cpu->reg_b);
	return 1;
}
u8 ldhe_63(Cpu* cpu) {
	ld_reg_to_reg(cpu, &cpu->reg_h, &cpu->reg_e);
	return 1;
}
u8 ldhh_64(Cpu* cpu) {
	ld_reg_to_reg(cpu, &cpu->reg_h, &cpu->reg_h);
	return 1;
}
u8 ldhl_65(Cpu* cpu) {
	ld_reg_to_reg(cpu, &cpu->reg_h, &cpu->reg_l);
	return 1;
}
u8 ldhhl_66(Cpu* cpu) {
	u16 hl = cpu->read_hl();
	ld_mem_to_reg(cpu, &cpu->reg_h, hl);
	return 2;
}
u8 ldha_67(Cpu* cpu) {
	ld_reg_to_reg(cpu, &cpu->reg_h, &cpu->reg_a);
	return 1;
}
u8 ldlb_68(Cpu* cpu) {
	ld_reg_to_reg(cpu, &cpu->reg_l, &cpu->reg_b);
	return 1;
}
u8 ldlc_69(Cpu* cpu) {
	ld_reg_to_reg(cpu, &cpu->reg_l, &cpu->reg_c);
	return 1;
}
u8 ldld_6A(Cpu* cpu) {
	ld_reg_to_reg(cpu, &cpu->reg_l, &cpu->reg_d);
	return 1;
}
u8 ldle_6B(Cpu* cpu) {
	ld_reg_to_reg(cpu, &cpu->reg_l, &cpu->reg_e);
	return 1;
}
u8 ldlh_6C(Cpu* cpu) {
	ld_reg_to_reg(cpu, &cpu->reg_l, &cpu->reg_h);
	return 1;
}
u8 ldll_6D(Cpu* cpu) {
	ld_reg_to_reg(cpu, &cpu->reg_l, &cpu->reg_l);
	return 1;
}
u8 ldlhl_6E(Cpu* cpu) {
	u16 hl = cpu->read_hl();
	ld_mem_to_reg(cpu, &cpu->reg_l, hl);
	return 2;
}
u8 ldla_6F(Cpu* cpu) {
	ld_reg_to_reg(cpu, &cpu->reg_l, &cpu->reg_a);
	return 1;
}

u8 ldhlb_70(Cpu* cpu) {
	u16 hl = cpu->read_hl();
	ld_reg_to_mem(cpu, &cpu->reg_b, hl);
	return 2;
}
u8 ldhlc_71(Cpu* cpu) {
	u16 hl = cpu->read_hl();
	ld_reg_to_mem(cpu, &cpu->reg_c, hl);
	return 2;
}
u8 ldhld_72(Cpu* cpu) {
	u16 hl = cpu->read_hl();
	ld_reg_to_mem(cpu, &cpu->reg_d, hl);
	return 2;
}
u8 ldhle_73(Cpu* cpu) {
	u16 hl = cpu->read_hl();
	ld_reg_to_mem(cpu, &cpu->reg_e, hl);
	return 2;
}
u8 ldhlh_74(Cpu* cpu) {
	u16 hl = cpu->read_hl();
	ld_reg_to_mem(cpu, &cpu->reg_h, hl);
	return 2;
}
u8 ldhll_75(Cpu* cpu) {
	u16 hl = cpu->read_hl();
	ld_reg_to_mem(cpu, &cpu->reg_l, hl);
	return 2;
}
u8 ldhla_77(Cpu* cpu) {
	u16 hl = cpu->read_hl();
	ld_reg_to_mem(cpu, &cpu->reg_a, hl);
	return 2;
}

u8 ldac_79(Cpu* cpu) {
	ld_reg_to_reg(cpu, &cpu->reg_a, &cpu->reg_c);
	return 1;
}
u8 ldad_7A(Cpu* cpu) {
	ld_reg_to_reg(cpu, &cpu->reg_a, &cpu->reg_d);
	return 1;
}
u8 ldae_7B(Cpu* cpu) {
	ld_reg_to_reg(cpu, &cpu->reg_a, &cpu->reg_e);
	return 1;
}
u8 ldah_7C(Cpu* cpu) {
	ld_reg_to_reg(cpu, &cpu->reg_a, &cpu->reg_h);
	return 1;
}
u8 ldab_78(Cpu* cpu) {
	ld_reg_to_reg(cpu, &cpu->reg_a, &cpu->reg_b);
	return 1;
}
u8 ldal_7D(Cpu* cpu) {
	ld_reg_to_reg(cpu, &cpu->reg_a, &cpu->reg_l);
	return 1;
}
u8 ldahl_7E(Cpu* cpu) {
	u16 hl = cpu->read_hl();
	ld_mem_to_reg(cpu, &cpu->reg_a, hl);
	return 2;
}
u8 ldaa_7F(Cpu* cpu) {
	ld_reg_to_reg(cpu, &cpu->reg_a, &cpu->reg_a);
	return 1;
}

u8 ldbca_02(Cpu* cpu) {
	u16 bc = cpu->read_bc();
	ld_reg_to_mem(cpu, &cpu->reg_a, bc);
	return 2;
}
u8 lddea_12(Cpu* cpu) {
	u16 de = cpu->read_de();
	ld_reg_to_mem(cpu, &cpu->reg_a, de);
	return 2;
}
u8 ldhlinca_22(Cpu* cpu) {
	u16 hl = cpu->read_hl();
	ld_reg_to_mem(cpu, &cpu->reg_a, hl);
	cpu->write_hl(hl + 1);
	return 2;
}
u8 ldhldeca_32(Cpu* cpu) {
	u16 hl = cpu->read_hl();
	ld_reg_to_mem(cpu, &cpu->reg_a, hl);
	cpu->write_hl(hl - 1);
	return 2;
}

u8 ldbu8_06(Cpu* cpu) {
	u8 value = cpu->read_pc();
	ld_reg_to_reg(cpu, &cpu->reg_b, &value);
	return 2;
}
u8 lddu8_16(Cpu* cpu) {
	u8 value = cpu->read_pc();
	ld_reg_to_reg(cpu, &cpu->reg_d, &value);
	return 2;
}
u8 ldhu8_26(Cpu* cpu) {
	u8 value = cpu->read_pc();
	ld_reg_to_reg(cpu, &cpu->reg_h, &value);
	return 2;
}
u8 ldhlu8_36(Cpu* cpu) {
	u8 value = cpu->read_pc();
	u16 hl = cpu->read_hl();
	ld_reg_to_mem(cpu, &value, hl);
	return 3;
}

u8 ldabc_0A(Cpu* cpu) {
	u16 bc = cpu->read_bc();
	ld_mem_to_reg(cpu, &cpu->reg_a, bc);
	return 2;
}
u8 ldade_1A(Cpu* cpu) {
	u16 de = cpu->read_de();
	ld_mem_to_reg(cpu, &cpu->reg_a, de);
	return 2;
}
u8 ldahlinc_2A(Cpu* cpu) {
	u16 hl = cpu->read_hl();
	ld_mem_to_reg(cpu, &cpu->reg_a, hl);
	cpu->write_hl(hl + 1);
	return 2;
}
u8 ldahldec_3A(Cpu* cpu) {
	u16 hl = cpu->read_hl();
	ld_mem_to_reg(cpu, &cpu->reg_a, hl);
	cpu->write_hl(hl - 1);
	return 2;
}

u8 ldcu8_0E(Cpu* cpu) {
	u8 value = cpu->read_pc();
	ld_reg_to_reg(cpu, &cpu->reg_c, &value);
	return 2;
}
u8 ldeu8_1E(Cpu* cpu) {
	u8 value = cpu->read_pc();
	ld_reg_to_reg(cpu, &cpu->reg_e, &value);
	return 2;
}
u8 ldlu8_2E(Cpu* cpu) {
	u8 value = cpu->read_pc();
	ld_reg_to_reg(cpu, &cpu->reg_l, &value);
	return 2;
}
u8 ldau8_3E(Cpu* cpu) {
	u8 value = cpu->read_pc();
	ld_reg_to_reg(cpu, &cpu->reg_a, &value);
	return 2;
}
u8 ldFFu8a_E0(Cpu* cpu) {
	u16 address = 0xFF00 + cpu->read_pc();
	ld_reg_to_mem(cpu, &cpu->reg_a, address);
	return 3;
}
u8 ldaFFu8_F0(Cpu* cpu) {
	u16 address = 0xFF00 + cpu->read_pc();
	ld_mem_to_reg(cpu, &cpu->reg_a, address);
	return 3;
}

u8 ldFFca_E2(Cpu* cpu) {
	u16 address = 0xFF00 + cpu->reg_c;
	ld_reg_to_mem(cpu, &cpu->reg_a, address);
	return 2;
}
u8 ldaFFc_F2(Cpu* cpu) {
	u16 address = 0xFF00 + cpu->reg_c;
	ld_mem_to_reg(cpu, &cpu->reg_a, address);
	return 2;
}

u8 ldu16a_EA(Cpu* cpu) {
	u16 low = cpu->read_pc();
	u16 high = cpu->read_pc();
	u16 address = (high << 8) | low;

	ld_reg_to_mem(cpu, &cpu->reg_a, address);
	return 4;
}
u8 ldau16_FA(Cpu* cpu) {
	u16 low = cpu->read_pc();
	u16 high = cpu->read_pc();
	u16 address = (high << 8) | low;

	ld_mem_to_reg(cpu, &cpu->reg_a, address);
	return 4;
}





