#pragma once
#include "cpu.h"
#include "timer.h"

class Gameboy {
public:
	Gameboy(Cpu* cpu, Timer* timer);
	Cpu* cpu;
	Timer* timer;
};