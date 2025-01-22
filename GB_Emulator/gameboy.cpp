#include "gameboy.h"


Gameboy::Gameboy(Cpu* cpu, Timer* timer, PPU* ppu) {
	this->cpu = cpu;
	this->timer = timer;
	this->ppu = ppu;
}