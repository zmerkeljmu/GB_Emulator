#pragma once
#include "common.h"
#include "memory.h"
#include "tile.h"

class PPU {
public:
	PPU(Mmu* mmu);
	Mmu* mmu;
	void scan_vram();

};






