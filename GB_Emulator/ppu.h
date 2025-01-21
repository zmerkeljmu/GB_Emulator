#pragma once
#include "common.h"
#include "memory.h"
#include "tile.h"
#include <SDL_opengl.h>

enum State {
	HBLANK = 0,
	VBLANK = 1,
	OAM_SEARCH = 2,
	PIXEL_TRANSFER = 3
};

class PPU {
public:
	PPU(Mmu* mmu);
	Mmu* mmu;
	void scan_vram(GLuint* framebuffer);
	void tick(u32 cycles);

private:
	State state = State::HBLANK;

};









