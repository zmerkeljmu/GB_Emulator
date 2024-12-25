#pragma once
#include "instruction.h"

u8 incbc_03(Cpu* cpu);
u8 incde_13(Cpu* cpu);
u8 inchl_23(Cpu* cpu);
u8 incsp_33(Cpu* cpu);

u8 decbc_0B(Cpu* cpu);
u8 decde_1B(Cpu* cpu);
u8 dechl_2B(Cpu* cpu);
u8 decsp_2B(Cpu* cpu);

u8 addbc_09(Cpu* cpu);
u8 addde_19(Cpu* cpu);
u8 addhl_29(Cpu* cpu);
u8 addsp_39(Cpu* cpu);