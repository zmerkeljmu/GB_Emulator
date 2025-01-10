#pragma once
#include "common.h"

void ld_reg_to_reg(Cpu* cpu, u8* write_reg, u8* read_reg);

void ld_reg_to_mem(Cpu* cpu, u8* reg, u16 address);

u8 ldbb_40(Cpu* cpu);
u8 ldbc_41(Cpu* cpu);
u8 ldbd_42(Cpu* cpu);
u8 ldbe_43(Cpu* cpu);
u8 ldbh_44(Cpu* cpu);
u8 ldbl_45(Cpu* cpu);
u8 ldbhl_46(Cpu* cpu);
u8 ldba_47(Cpu* cpu);
u8 ldcb_48(Cpu* cpu);
u8 ldcc_49(Cpu* cpu);
u8 ldcd_4A(Cpu* cpu);
u8 ldce_4B(Cpu* cpu);
u8 ldch_4C(Cpu* cpu);
u8 ldcl_4D(Cpu* cpu);
u8 ldchl_4E(Cpu* cpu);
u8 ldca_4F(Cpu* cpu);

u8 lddb_50(Cpu* cpu);
u8 lddc_51(Cpu* cpu);
u8 lddd_52(Cpu* cpu);
u8 ldde_53(Cpu* cpu);
u8 lddh_54(Cpu* cpu);
u8 lddl_55(Cpu* cpu);
u8 lddhl_56(Cpu* cpu);
u8 ldda_57(Cpu* cpu);
u8 ldeb_58(Cpu* cpu);
u8 ldec_59(Cpu* cpu);
u8 lded_5A(Cpu* cpu);
u8 ldee_5B(Cpu* cpu);
u8 ldeh_5C(Cpu* cpu);
u8 ldel_5D(Cpu* cpu);
u8 ldehl_5E(Cpu* cpu);
u8 ldea_5F(Cpu* cpu);

u8 ldhb_60(Cpu* cpu);
u8 ldhc_61(Cpu* cpu);
u8 ldhd_62(Cpu* cpu);
u8 ldhe_63(Cpu* cpu);
u8 ldhh_64(Cpu* cpu);
u8 ldhl_65(Cpu* cpu);
u8 ldhhl_66(Cpu* cpu);
u8 ldha_67(Cpu* cpu);
u8 ldlb_68(Cpu* cpu);
u8 ldlc_69(Cpu* cpu);
u8 ldld_6A(Cpu* cpu);
u8 ldle_6B(Cpu* cpu);
u8 ldlh_6C(Cpu* cpu);
u8 ldll_6D(Cpu* cpu);
u8 ldlhl_6E(Cpu* cpu);
u8 ldla_6F(Cpu* cpu);

u8 ldhlb_70(Cpu* cpu);
u8 ldhlc_71(Cpu* cpu);
u8 ldhld_72(Cpu* cpu);
u8 ldhle_73(Cpu* cpu);
u8 ldhlh_74(Cpu* cpu);
u8 ldhll_75(Cpu* cpu);

u8 ldhla_77(Cpu* cpu);
u8 ldab_78(Cpu* cpu);
u8 ldac_79(Cpu* cpu);
u8 ldad_7A(Cpu* cpu);
u8 ldae_7B(Cpu* cpu);
u8 ldah_7C(Cpu* cpu);
u8 ldal_7D(Cpu* cpu);
u8 ldahl_7E(Cpu* cpu);
u8 ldaa_7F(Cpu* cpu);

u8 ldbca_02(Cpu* cpu);
u8 lddea_12(Cpu* cpu);
u8 ldhlinca_22(Cpu* cpu);
u8 ldhldeca_32(Cpu* cpu);

u8 ldbu8_06(Cpu* cpu);
u8 lddu8_16(Cpu* cpu);
u8 ldhu8_26(Cpu* cpu);
u8 ldhlu8_36(Cpu* cpu);

u8 ldabc_0A(Cpu* cpu);
u8 ldade_1A(Cpu* cpu);
u8 ldahlinc_2A(Cpu* cpu);
u8 ldahldec_3A(Cpu* cpu);

u8 ldcu8_0E(Cpu* cpu);
u8 ldeu8_1E(Cpu* cpu);
u8 ldlu8_2E(Cpu* cpu);
u8 ldau8_3E(Cpu* cpu);

u8 ldFFu8a_E0(Cpu* cpu);
u8 ldaFFu8_F0(Cpu* cpu);

u8 ldFFca_E2(Cpu* cpu);
u8 ldaFFc_F2(Cpu* cpu);

u8 ldu16a_EA(Cpu* cpu);
u8 ldau16_FA(Cpu* cpu);

