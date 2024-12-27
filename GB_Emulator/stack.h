#pragma once
#include "instruction.h"

void pop_2reg(Cpu* cpu, u8* high_reg, u8* low_reg);

u8 popbc_C1(Cpu* cpu);
u8 popde_D1(Cpu* cpu);
u8 pophl_E1(Cpu* cpu);
u8 popaf_F1(Cpu* cpu);

void push_reg(Cpu* cpu, u8* high_reg, u8* low_reg);

u8 pushbc_C5(Cpu* cpu);
u8 pushde_D5(Cpu* cpu);
u8 pushhl_E5(Cpu* cpu);
u8 pushaf_F5(Cpu* cpu);

u8 addspi8_E8(Cpu* cpu);
u8 ldhlspi8_F8(Cpu* cpu);