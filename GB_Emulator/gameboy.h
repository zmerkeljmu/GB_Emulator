#pragma once
#include "cpu.h"
#include "timer.h"
#include "ppu.h"

class Gameboy {
public:
	Gameboy(Cpu* cpu, Timer* timer, PPU* ppu);
	Cpu* cpu;
	Timer* timer;
	PPU* ppu;
};