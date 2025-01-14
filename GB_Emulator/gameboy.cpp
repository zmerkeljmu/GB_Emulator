#include "gameboy.h"


Gameboy::Gameboy(Cpu* cpu, Timer* timer) {
	this->cpu = cpu;
	this->timer = timer;
}