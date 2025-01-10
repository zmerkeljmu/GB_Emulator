#pragma once
#include "common.h"

u8 ldbcu16_01(Cpu* cpu);
u8 lddeu16_11(Cpu* cpu);
u8 ldhlu16_21(Cpu* cpu);
u8 ldspu16_31(Cpu* cpu);

u8 ldsphl_F9(Cpu* cpu);

u8 ldu16sp_08(Cpu* cpu);