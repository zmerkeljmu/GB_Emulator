#pragma once
#include "instruction.h"

u8 nop_00(Cpu* cpu);
u8 stop_10(Cpu* cpu);

u8 halt_76(Cpu* cpu);

u8 di_F4(Cpu* cpu);

u8 cb_CB(Cpu* cpu);
u8 ei_FB(Cpu* cpu);

//carry flag instructions

u8 cpl_2F(Cpu* cpu);
u8 ccf_3F(Cpu* cpu);

u8 daa_27(Cpu* cpu);
u8 scf_37(Cpu* cpu);