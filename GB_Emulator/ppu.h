#pragma once
#include "common.h"
#include "memory.h"
#include "tile.h"
#include <SDL_opengl.h>

enum class State {
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

private:
	State state = State::HBLANK;
};









