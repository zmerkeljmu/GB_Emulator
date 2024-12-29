#include "bit_flag.h"
#include "cpu.h"

void bit(Cpu* cpu, u8* reg, u8 bit) {
	u8 bit_val = u8read_bit(bit, reg);
	if (bit_val == 0)
		cpu->set_zero_flag();
	else
		cpu->clear_zero_flag();
	cpu->clear_s_flag();
	cpu->set_hc_flag();
	return;
}

u8 bit0b_40(Cpu* cpu) {
	bit(cpu, &cpu->reg_b, 0);
	return 2;
}
u8 bit0c_41(Cpu* cpu) {
	bit(cpu, &cpu->reg_c, 0);
	return 2;
}
u8 bit0d_42(Cpu* cpu) {
	bit(cpu, &cpu->reg_d, 0);
	return 2;
}
u8 bit0e_43(Cpu* cpu) {
	bit(cpu, &cpu->reg_e, 0);
	return 2;
}
u8 bit0h_44(Cpu* cpu) {
	bit(cpu, &cpu->reg_h, 0);
	return 2;
}
u8 bit0l_45(Cpu* cpu) {
	bit(cpu, &cpu->reg_l, 0);
	return 2;
}
u8 bit0hl_46(Cpu* cpu) {
	u8 val = cpu->mem->read_byte(cpu->read_hl());
	bit(cpu, &val, 0);
	return 3;
}
u8 bit0a_47(Cpu* cpu) {
	bit(cpu, &cpu->reg_a, 0);
	return 2;
}

u8 bit1b_48(Cpu* cpu) {
	bit(cpu, &cpu->reg_b, 1);
	return 2;
}
u8 bit1c_49(Cpu* cpu) {
	bit(cpu, &cpu->reg_c, 1);
	return 2;
}
u8 bit1d_4A(Cpu* cpu) {
	bit(cpu, &cpu->reg_d, 1);
	return 2;
}
u8 bit1e_4B(Cpu* cpu) {
	bit(cpu, &cpu->reg_e, 1);
	return 2;
}
u8 bit1h_4C(Cpu* cpu) {
	bit(cpu, &cpu->reg_h, 1);
	return 2;
}
u8 bit1l_4D(Cpu* cpu) {
	bit(cpu, &cpu->reg_l, 1);
	return 2;
}
u8 bit1hl_4E(Cpu* cpu) {
	u8 val = cpu->mem->read_byte(cpu->read_hl());
	bit(cpu, &val, 1);
	return 3;
}
u8 bit1a_4F(Cpu* cpu) {
	bit(cpu, &cpu->reg_a, 1);
	return 2;
}


u8 bit2b_50(Cpu* cpu) {
	bit(cpu, &cpu->reg_b, 2);
	return 2;
}
u8 bit2c_51(Cpu* cpu) {
	bit(cpu, &cpu->reg_c, 2);
	return 2;
}
u8 bit2d_52(Cpu* cpu) {
	bit(cpu, &cpu->reg_d, 2);
	return 2;
}
u8 bit2e_53(Cpu* cpu) {
	bit(cpu, &cpu->reg_e, 2);
	return 2;
}
u8 bit2h_54(Cpu* cpu) {
	bit(cpu, &cpu->reg_h, 2);
	return 2;
}
u8 bit2l_55(Cpu* cpu) {
	bit(cpu, &cpu->reg_l, 2);
	return 2;
}
u8 bit2hl_56(Cpu* cpu) {
	u8 val = cpu->mem->read_byte(cpu->read_hl());
	bit(cpu, &val, 2);
	return 3;
}
u8 bit2a_57(Cpu* cpu) {
	bit(cpu, &cpu->reg_a, 2);
	return 2;
}

u8 bit3b_58(Cpu* cpu) {
	bit(cpu, &cpu->reg_b, 3);
	return 2;
}
u8 bit3c_59(Cpu* cpu) {
	bit(cpu, &cpu->reg_c, 3);
	return 2;
}
u8 bit3d_5A(Cpu* cpu) {
	bit(cpu, &cpu->reg_d, 3);
	return 2;
}
u8 bit3e_5B(Cpu* cpu) {
	bit(cpu, &cpu->reg_e, 3);
	return 2;
}
u8 bit3h_5C(Cpu* cpu) {
	bit(cpu, &cpu->reg_h, 3);
	return 2;
}
u8 bit3l_5D(Cpu* cpu) {
	bit(cpu, &cpu->reg_l, 3);
	return 2;
}
u8 bit3hl_5E(Cpu* cpu) {
	u8 val = cpu->mem->read_byte(cpu->read_hl());
	bit(cpu, &val, 3);
	return 3;
}
u8 bit3a_5F(Cpu* cpu) {
	bit(cpu, &cpu->reg_a, 3);
	return 2;
}


u8 bit4b_60(Cpu* cpu) {
	bit(cpu, &cpu->reg_b, 4);
	return 2;
}
u8 bit4c_61(Cpu* cpu) {
	bit(cpu, &cpu->reg_c, 4);
	return 2;
}
u8 bit4d_62(Cpu* cpu) {
	bit(cpu, &cpu->reg_d, 4);
	return 2;
}
u8 bit4e_63(Cpu* cpu) {
	bit(cpu, &cpu->reg_e, 4);
	return 2;
}
u8 bit4h_64(Cpu* cpu) {
	bit(cpu, &cpu->reg_h, 4);
	return 2;
}
u8 bit4l_65(Cpu* cpu) {
	bit(cpu, &cpu->reg_l, 4);
	return 2;
}
u8 bit4hl_66(Cpu* cpu) {
	u8 val = cpu->mem->read_byte(cpu->read_hl());
	bit(cpu, &val, 4);
	return 3;
}
u8 bit4a_67(Cpu* cpu) {
	bit(cpu, &cpu->reg_a, 4);
	return 2;
}

u8 bit5b_68(Cpu* cpu) {
	bit(cpu, &cpu->reg_b, 5);
	return 2;
}
u8 bit5c_69(Cpu* cpu) {
	bit(cpu, &cpu->reg_c, 5);
	return 2;
}
u8 bit5d_6A(Cpu* cpu) {
	bit(cpu, &cpu->reg_d, 5);
	return 2;
}
u8 bit5e_6B(Cpu* cpu) {
	bit(cpu, &cpu->reg_e, 5);
	return 2;
}
u8 bit5h_6C(Cpu* cpu) {
	bit(cpu, &cpu->reg_h, 5);
	return 2;
}
u8 bit5l_6D(Cpu* cpu) {
	bit(cpu, &cpu->reg_l, 5);
	return 2;
}
u8 bit5hl_6E(Cpu* cpu) {
	u8 val = cpu->mem->read_byte(cpu->read_hl());
	bit(cpu, &val, 5);
	return 3;
}
u8 bit5a_6F(Cpu* cpu) {
	bit(cpu, &cpu->reg_a, 5);
	return 2;
}


u8 bit6b_70(Cpu* cpu) {
	bit(cpu, &cpu->reg_b, 6);
	return 2;
}
u8 bit6c_71(Cpu* cpu) {
	bit(cpu, &cpu->reg_c, 6);
	return 2;
}
u8 bit6d_72(Cpu* cpu) {
	bit(cpu, &cpu->reg_d, 6);
	return 2;
}
u8 bit6e_73(Cpu* cpu) {
	bit(cpu, &cpu->reg_e, 6);
	return 2;
}
u8 bit6h_74(Cpu* cpu) {
	bit(cpu, &cpu->reg_h, 6);
	return 2;
}
u8 bit6l_75(Cpu* cpu) {
	bit(cpu, &cpu->reg_l, 6);
	return 2;
}
u8 bit6hl_76(Cpu* cpu) {
	u8 val = cpu->mem->read_byte(cpu->read_hl());
	bit(cpu, &val, 6);
	return 3;
}
u8 bit6a_77(Cpu* cpu) {
	bit(cpu, &cpu->reg_a, 6);
	return 2;
}

u8 bit7b_78(Cpu* cpu) {
	bit(cpu, &cpu->reg_b, 7);
	return 2;
}
u8 bit7c_79(Cpu* cpu) {
	bit(cpu, &cpu->reg_c, 7);
	return 2;
}
u8 bit7d_7A(Cpu* cpu) {
	bit(cpu, &cpu->reg_d, 7);
	return 2;
}
u8 bit7e_7B(Cpu* cpu) {
	bit(cpu, &cpu->reg_e, 7);
	return 2;
}
u8 bit7h_7C(Cpu* cpu) {
	bit(cpu, &cpu->reg_h, 7);
	return 2;
}
u8 bit7l_7D(Cpu* cpu) {
	bit(cpu, &cpu->reg_l, 7);
	return 2;
}
u8 bit7hl_7E(Cpu* cpu) {
	u8 val = cpu->mem->read_byte(cpu->read_hl());
	bit(cpu, &val, 7);
	return 3;
}
u8 bit7a_7F(Cpu* cpu) {
	bit(cpu, &cpu->reg_a, 7);
	return 2;
}

void res(Cpu* cpu, u8* reg, u8 bit) {
	u8set_bit(bit, reg, 0);
	return;
}

u8 res0b_80(Cpu* cpu) {
	res(cpu, &cpu->reg_b, 0);
	return 2;
}
u8 res0c_81(Cpu* cpu) {
	res(cpu, &cpu->reg_c, 0);
	return 2;
}
u8 res0d_82(Cpu* cpu) {
	res(cpu, &cpu->reg_d, 0);
	return 2;
}
u8 res0e_83(Cpu* cpu) {
	res(cpu, &cpu->reg_e, 0);
	return 2;
}
u8 res0h_84(Cpu* cpu) {
	res(cpu, &cpu->reg_h, 0);
	return 2;
}
u8 res0l_85(Cpu* cpu) {
	res(cpu, &cpu->reg_l, 0);
	return 2;
}
u8 res0hl_86(Cpu* cpu) {
	u8 val = cpu->mem->read_byte(cpu->read_hl());
	res(cpu, &val, 0);
	return 3;
}
u8 res0a_87(Cpu* cpu) {
	res(cpu, &cpu->reg_a, 0);
	return 2;
}

u8 res1b_88(Cpu* cpu) {
	res(cpu, &cpu->reg_b, 1);
	return 2;
}
u8 res1c_89(Cpu* cpu) {
	res(cpu, &cpu->reg_c, 1);
	return 2;
}
u8 res1d_8A(Cpu* cpu) {
	res(cpu, &cpu->reg_d, 1);
	return 2;
}
u8 res1e_8B(Cpu* cpu) {
	res(cpu, &cpu->reg_e, 1);
	return 2;
}
u8 res1h_8C(Cpu* cpu) {
	res(cpu, &cpu->reg_h, 1);
	return 2;
}
u8 res1l_8D(Cpu* cpu) {
	res(cpu, &cpu->reg_l, 1);
	return 2;
}
u8 res1hl_8E(Cpu* cpu) {
	u8 val = cpu->mem->read_byte(cpu->read_hl());
	res(cpu, &val, 1);
	return 3;
}
u8 res1a_8F(Cpu* cpu) {
	res(cpu, &cpu->reg_a, 1);
	return 2;
}


u8 res2b_90(Cpu* cpu) {
	res(cpu, &cpu->reg_b, 2);
	return 2;
}
u8 res2c_91(Cpu* cpu) {
	res(cpu, &cpu->reg_c, 2);
	return 2;
}
u8 res2d_92(Cpu* cpu) {
	res(cpu, &cpu->reg_d, 2);
	return 2;
}
u8 res2e_93(Cpu* cpu) {
	res(cpu, &cpu->reg_e, 2);
	return 2;
}
u8 res2h_94(Cpu* cpu) {
	res(cpu, &cpu->reg_h, 2);
	return 2;
}
u8 res2l_95(Cpu* cpu) {
	res(cpu, &cpu->reg_l, 2);
	return 2;
}
u8 res2hl_96(Cpu* cpu) {
	u8 val = cpu->mem->read_byte(cpu->read_hl());
	res(cpu, &val, 2);
	return 3;
}
u8 res2a_97(Cpu* cpu) {
	res(cpu, &cpu->reg_a, 2);
	return 2;
}

u8 res3b_98(Cpu* cpu) {
	res(cpu, &cpu->reg_b, 3);
	return 2;
}
u8 res3c_99(Cpu* cpu) {
	res(cpu, &cpu->reg_c, 3);
	return 2;
}
u8 res3d_9A(Cpu* cpu) {
	res(cpu, &cpu->reg_d, 3);
	return 2;
}
u8 res3e_9B(Cpu* cpu) {
	res(cpu, &cpu->reg_e, 3);
	return 2;
}
u8 res3h_9C(Cpu* cpu) {
	res(cpu, &cpu->reg_h, 3);
	return 2;
}
u8 res3l_9D(Cpu* cpu) {
	res(cpu, &cpu->reg_l, 3);
	return 2;
}
u8 res3hl_9E(Cpu* cpu) {
	u8 val = cpu->mem->read_byte(cpu->read_hl());
	res(cpu, &val, 3);
	return 3;
}
u8 res3a_9F(Cpu* cpu) {
	res(cpu, &cpu->reg_a, 3);
	return 2;
}


u8 res4b_A0(Cpu* cpu) {
	res(cpu, &cpu->reg_b, 4);
	return 2;
}
u8 res4c_A1(Cpu* cpu) {
	res(cpu, &cpu->reg_c, 4);
	return 2;
}
u8 res4d_A2(Cpu* cpu) {
	res(cpu, &cpu->reg_d, 4);
	return 2;
}
u8 res4e_A3(Cpu* cpu) {
	res(cpu, &cpu->reg_e, 4);
	return 2;
}
u8 res4h_A4(Cpu* cpu) {
	res(cpu, &cpu->reg_h, 4);
	return 2;
}
u8 res4l_A5(Cpu* cpu) {
	res(cpu, &cpu->reg_l, 4);
	return 2;
}
u8 res4hl_A6(Cpu* cpu) {
	u8 val = cpu->mem->read_byte(cpu->read_hl());
	res(cpu, &val, 4);
	return 3;
}
u8 res4a_A7(Cpu* cpu) {
	res(cpu, &cpu->reg_a, 4);
	return 2;
}

u8 res5b_A8(Cpu* cpu) {
	res(cpu, &cpu->reg_b, 5);
	return 2;
}
u8 res5c_A9(Cpu* cpu) {
	res(cpu, &cpu->reg_c, 5);
	return 2;
}
u8 res5d_AA(Cpu* cpu) {
	res(cpu, &cpu->reg_d, 5);
	return 2;
}
u8 res5e_AB(Cpu* cpu) {
	res(cpu, &cpu->reg_e, 5);
	return 2;
}
u8 res5h_AC(Cpu* cpu) {
	res(cpu, &cpu->reg_h, 5);
	return 2;
}
u8 res5l_AD(Cpu* cpu) {
	res(cpu, &cpu->reg_l, 5);
	return 2;
}
u8 res5hl_AE(Cpu* cpu) {
	u8 val = cpu->mem->read_byte(cpu->read_hl());
	res(cpu, &val, 5);
	return 3;
}
u8 res5a_AF(Cpu* cpu) {
	res(cpu, &cpu->reg_a, 5);
	return 2;
}


u8 res6b_B0(Cpu* cpu) {
	res(cpu, &cpu->reg_b, 6);
	return 2;
}
u8 res6c_B1(Cpu* cpu) {
	res(cpu, &cpu->reg_c, 6);
	return 2;
}
u8 res6d_B2(Cpu* cpu) {
	res(cpu, &cpu->reg_d, 6);
	return 2;
}
u8 res6e_B3(Cpu* cpu) {
	res(cpu, &cpu->reg_e, 6);
	return 2;
}
u8 res6h_B4(Cpu* cpu) {
	res(cpu, &cpu->reg_h, 6);
	return 2;
}
u8 res6l_B5(Cpu* cpu) {
	res(cpu, &cpu->reg_l, 6);
	return 2;
}
u8 res6hl_B6(Cpu* cpu) {
	u8 val = cpu->mem->read_byte(cpu->read_hl());
	res(cpu, &val, 6);
	return 3;
}
u8 res6a_B7(Cpu* cpu) {
	res(cpu, &cpu->reg_a, 6);
	return 2;
}

u8 res7b_B8(Cpu* cpu) {
	res(cpu, &cpu->reg_b, 7);
	return 2;
}
u8 res7c_B9(Cpu* cpu) {
	res(cpu, &cpu->reg_c, 7);
	return 2;
}
u8 res7d_BA(Cpu* cpu) {
	res(cpu, &cpu->reg_d, 7);
	return 2;
}
u8 res7e_BB(Cpu* cpu) {
	res(cpu, &cpu->reg_e, 7);
	return 2;
}
u8 res7h_BC(Cpu* cpu) {
	res(cpu, &cpu->reg_h, 7);
	return 2;
}
u8 res7l_BD(Cpu* cpu) {
	res(cpu, &cpu->reg_l, 7);
	return 2;
}
u8 res7hl_BE(Cpu* cpu) {
	u8 val = cpu->mem->read_byte(cpu->read_hl());
	res(cpu, &val, 7);
	return 3;
}
u8 res7a_BF(Cpu* cpu) {
	res(cpu, &cpu->reg_a, 7);
	return 2;
}


void set(Cpu* cpu, u8* reg, u8 bit) {
	u8set_bit(bit, reg, 1);
	return;
}

u8 set0b_C0(Cpu* cpu) {
	set(cpu, &cpu->reg_b, 0);
	return 2;
}
u8 set0c_C1(Cpu* cpu) {
	set(cpu, &cpu->reg_c, 0);
	return 2;
}
u8 set0d_C2(Cpu* cpu) {
	set(cpu, &cpu->reg_d, 0);
	return 2;
}
u8 set0e_C3(Cpu* cpu) {
	set(cpu, &cpu->reg_e, 0);
	return 2;
}
u8 set0h_C4(Cpu* cpu) {
	set(cpu, &cpu->reg_h, 0);
	return 2;
}
u8 set0l_C5(Cpu* cpu) {
	set(cpu, &cpu->reg_l, 0);
	return 2;
}
u8 set0hl_C6(Cpu* cpu) {
	u8 val = cpu->mem->read_byte(cpu->read_hl());
	set(cpu, &val, 0);
	return 3;
}
u8 set0a_C7(Cpu* cpu) {
	set(cpu, &cpu->reg_a, 0);
	return 2;
}

u8 set1b_C8(Cpu* cpu) {
	set(cpu, &cpu->reg_b, 1);
	return 2;
}
u8 set1c_C9(Cpu* cpu) {
	set(cpu, &cpu->reg_c, 1);
	return 2;
}
u8 set1d_CA(Cpu* cpu) {
	set(cpu, &cpu->reg_d, 1);
	return 2;
}
u8 set1e_CB(Cpu* cpu) {
	set(cpu, &cpu->reg_e, 1);
	return 2;
}
u8 set1h_CC(Cpu* cpu) {
	set(cpu, &cpu->reg_h, 1);
	return 2;
}
u8 set1l_CD(Cpu* cpu) {
	set(cpu, &cpu->reg_l, 1);
	return 2;
}
u8 set1hl_CE(Cpu* cpu) {
	u8 val = cpu->mem->read_byte(cpu->read_hl());
	set(cpu, &val, 1);
	return 3;
}
u8 set1a_CF(Cpu* cpu) {
	set(cpu, &cpu->reg_a, 1);
	return 2;
}


u8 set2b_D0(Cpu* cpu) {
	set(cpu, &cpu->reg_b, 2);
	return 2;
}
u8 set2c_D1(Cpu* cpu) {
	set(cpu, &cpu->reg_c, 2);
	return 2;
}
u8 set2d_D2(Cpu* cpu) {
	set(cpu, &cpu->reg_d, 2);
	return 2;
}
u8 set2e_D3(Cpu* cpu) {
	set(cpu, &cpu->reg_e, 2);
	return 2;
}
u8 set2h_D4(Cpu* cpu) {
	set(cpu, &cpu->reg_h, 2);
	return 2;
}
u8 set2l_D5(Cpu* cpu) {
	set(cpu, &cpu->reg_l, 2);
	return 2;
}
u8 set2hl_D6(Cpu* cpu) {
	u8 val = cpu->mem->read_byte(cpu->read_hl());
	set(cpu, &val, 2);
	return 3;
}
u8 set2a_D7(Cpu* cpu) {
	set(cpu, &cpu->reg_a, 2);
	return 2;
}

u8 set3b_D8(Cpu* cpu) {
	set(cpu, &cpu->reg_b, 3);
	return 2;
}
u8 set3c_D9(Cpu* cpu) {
	set(cpu, &cpu->reg_c, 3);
	return 2;
}
u8 set3d_DA(Cpu* cpu) {
	set(cpu, &cpu->reg_d, 3);
	return 2;
}
u8 set3e_DB(Cpu* cpu) {
	set(cpu, &cpu->reg_e, 3);
	return 2;
}
u8 set3h_DC(Cpu* cpu) {
	set(cpu, &cpu->reg_h, 3);
	return 2;
}
u8 set3l_DD(Cpu* cpu) {
	set(cpu, &cpu->reg_l, 3);
	return 2;
}
u8 set3hl_DE(Cpu* cpu) {
	u8 val = cpu->mem->read_byte(cpu->read_hl());
	set(cpu, &val, 3);
	return 3;
}
u8 set3a_DF(Cpu* cpu) {
	set(cpu, &cpu->reg_a, 3);
	return 2;
}


u8 set4b_E0(Cpu* cpu) {
	set(cpu, &cpu->reg_b, 4);
	return 2;
}
u8 set4c_E1(Cpu* cpu) {
	set(cpu, &cpu->reg_c, 4);
	return 2;
}
u8 set4d_E2(Cpu* cpu) {
	set(cpu, &cpu->reg_d, 4);
	return 2;
}
u8 set4e_E3(Cpu* cpu) {
	set(cpu, &cpu->reg_e, 4);
	return 2;
}
u8 set4h_E4(Cpu* cpu) {
	set(cpu, &cpu->reg_h, 4);
	return 2;
}
u8 set4l_E5(Cpu* cpu) {
	set(cpu, &cpu->reg_l, 4);
	return 2;
}
u8 set4hl_E6(Cpu* cpu) {
	u8 val = cpu->mem->read_byte(cpu->read_hl());
	set(cpu, &val, 4);
	return 3;
}
u8 set4a_E7(Cpu* cpu) {
	set(cpu, &cpu->reg_a, 4);
	return 2;
}


u8 set5b_E8(Cpu* cpu) {
	set(cpu, &cpu->reg_b, 5);
	return 2;
}
u8 set5c_E9(Cpu* cpu) {
	set(cpu, &cpu->reg_c, 5);
	return 2;
}
u8 set5d_EA(Cpu* cpu) {
	set(cpu, &cpu->reg_d, 5);
	return 2;
}
u8 set5e_EB(Cpu* cpu) {
	set(cpu, &cpu->reg_e, 5);
	return 2;
}
u8 set5h_EC(Cpu* cpu) {
	set(cpu, &cpu->reg_h, 5);
	return 2;
}
u8 set5l_ED(Cpu* cpu) {
	set(cpu, &cpu->reg_l, 5);
	return 2;
}
u8 set5hl_EE(Cpu* cpu) {
	u8 val = cpu->mem->read_byte(cpu->read_hl());
	set(cpu, &val, 5);
	return 3;
}
u8 set5a_EF(Cpu* cpu) {
	set(cpu, &cpu->reg_a, 5);
	return 2;
}


u8 set6b_F0(Cpu* cpu) {
	set(cpu, &cpu->reg_b, 6);
	return 2;
}
u8 set6c_F1(Cpu* cpu) {
	set(cpu, &cpu->reg_c, 6);
	return 2;
}
u8 set6d_F2(Cpu* cpu) {
	set(cpu, &cpu->reg_d, 6);
	return 2;
}
u8 set6e_F3(Cpu* cpu) {
	set(cpu, &cpu->reg_e, 6);
	return 2;
}
u8 set6h_F4(Cpu* cpu) {
	set(cpu, &cpu->reg_h, 6);
	return 2;
}
u8 set6l_F5(Cpu* cpu) {
	set(cpu, &cpu->reg_l, 6);
	return 2;
}
u8 set6hl_F6(Cpu* cpu) {
	u8 val = cpu->mem->read_byte(cpu->read_hl());
	set(cpu, &val, 6);
	return 3;
}
u8 set6a_F7(Cpu* cpu) {
	set(cpu, &cpu->reg_a, 6);
	return 2;
}

u8 set7b_F8(Cpu* cpu) {
	set(cpu, &cpu->reg_b, 7);
	return 2;
}
u8 set7c_F9(Cpu* cpu) {
	set(cpu, &cpu->reg_c, 7);
	return 2;
}
u8 set7d_FA(Cpu* cpu) {
	set(cpu, &cpu->reg_d, 7);
	return 2;
}
u8 set7e_FB(Cpu* cpu) {
	set(cpu, &cpu->reg_e, 7);
	return 2;
}
u8 set7h_FC(Cpu* cpu) {
	set(cpu, &cpu->reg_h, 7);
	return 2;
}
u8 set7l_FD(Cpu* cpu) {
	set(cpu, &cpu->reg_l, 7);
	return 2;
}
u8 set7hl_FE(Cpu* cpu) {
	u8 val = cpu->mem->read_byte(cpu->read_hl());
	set(cpu, &val, 7);
	return 3;
}
u8 set7a_FF(Cpu* cpu) {
	set(cpu, &cpu->reg_a, 7);
	return 2;
}