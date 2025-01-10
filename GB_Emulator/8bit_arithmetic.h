#pragma once
#include "common.h"

void add_rtor(Cpu* cpu, u8* reg);

u8 addb_80(Cpu* cpu);
u8 addc_81(Cpu* cpu);
u8 addd_82(Cpu* cpu);
u8 adde_83(Cpu* cpu);
u8 addh_84(Cpu* cpu);
u8 addl_85(Cpu* cpu);
u8 addhl_86(Cpu* cpu);
u8 adda_87(Cpu* cpu);
u8 addi8_C6(Cpu* cpu);

void adc_rtor(Cpu* cpu, u8* reg);

u8 adcb_88(Cpu* cpu);
u8 adcc_89(Cpu* cpu);
u8 adcd_8A(Cpu* cpu);
u8 adce_8B(Cpu* cpu);
u8 adch_8C(Cpu* cpu);
u8 adcl_8D(Cpu* cpu);
u8 adchl_8E(Cpu* cpu);
u8 adca_8F(Cpu* cpu);
u8 adci8_CE(Cpu* cpu);

void sub_rtor(Cpu* cpu, u8* reg);

u8 subb_90(Cpu* cpu);
u8 subc_91(Cpu* cpu);
u8 subd_92(Cpu* cpu);
u8 sube_93(Cpu* cpu);
u8 subh_94(Cpu* cpu);
u8 subl_95(Cpu* cpu);
u8 subhl_96(Cpu* cpu);
u8 suba_97(Cpu* cpu);
u8 subi8_D6(Cpu* cpu);

void sbc_rtor(Cpu* cpu, u8* reg);

u8 sbcb_98(Cpu* cpu);
u8 sbcc_99(Cpu* cpu);
u8 sbcd_9A(Cpu* cpu);
u8 sbce_9B(Cpu* cpu);
u8 sbch_9C(Cpu* cpu);
u8 sbcl_9D(Cpu* cpu);
u8 sbchl_9E(Cpu* cpu);
u8 sbca_9F(Cpu* cpu);
u8 sbci8_DE(Cpu* cpu);

void and_rtor(Cpu* cpu, u8* reg);

u8 andb_A0(Cpu* cpu);
u8 andc_A1(Cpu* cpu);
u8 andd_A2(Cpu* cpu);
u8 ande_A3(Cpu* cpu);
u8 andh_A4(Cpu* cpu);
u8 andl_A5(Cpu* cpu);
u8 andhl_A6(Cpu* cpu);
u8 anda_A7(Cpu* cpu);
u8 andi8_E6(Cpu* cpu);

void xor_rtor(Cpu* cpu, u8* reg);

u8 xorb_A8(Cpu* cpu);
u8 xorc_A9(Cpu* cpu);
u8 xord_AA(Cpu* cpu);
u8 xore_AB(Cpu* cpu);
u8 xorh_AC(Cpu* cpu);
u8 xorl_AD(Cpu* cpu);
u8 xorhl_AE(Cpu* cpu);
u8 xora_AF(Cpu* cpu);
u8 xori8_EE(Cpu* cpu);

void or_rtor(Cpu* cpu, u8* reg);

u8 orb_B0(Cpu* cpu);
u8 orc_B1(Cpu* cpu);
u8 ord_B2(Cpu* cpu);
u8 ore_B3(Cpu* cpu);
u8 orh_B4(Cpu* cpu);
u8 orl_B5(Cpu* cpu);
u8 orhl_B6(Cpu* cpu);
u8 ora_B7(Cpu* cpu);
u8 ori8_F6(Cpu* cpu);

void cp_rtor(Cpu* cpu, u8* reg);

u8 cpb_B8(Cpu* cpu);
u8 cpc_B9(Cpu* cpu);
u8 cpd_BA(Cpu* cpu);
u8 cpe_BB(Cpu* cpu);
u8 cph_BC(Cpu* cpu);
u8 cpl_BD(Cpu* cpu);
u8 cphl_BE(Cpu* cpu);
u8 cpa_BF(Cpu* cpu);
u8 cpi8_FE(Cpu* cpu);

void inc_reg(Cpu* cpu, u8* reg);

u8 incb_04(Cpu* cpu);
u8 incd_14(Cpu* cpu);
u8 inch_24(Cpu* cpu);
u8 inchl_34(Cpu* cpu);
u8 incc_0C(Cpu* cpu);
u8 ince_1C(Cpu* cpu);
u8 incl_2C(Cpu* cpu);
u8 inca_3C(Cpu* cpu);

u8 decb_05(Cpu* cpu);
u8 decd_15(Cpu* cpu);
u8 dech_25(Cpu* cpu);
u8 dechl_35(Cpu* cpu);
u8 decc_0D(Cpu* cpu);
u8 dece_1D(Cpu* cpu);
u8 decl_2D(Cpu* cpu);
u8 deca_3D(Cpu* cpu);