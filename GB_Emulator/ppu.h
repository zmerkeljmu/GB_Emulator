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
	u8 cur_state = State::HBLANK;
	u32 cycles_remaining = 0;
	u8 ly = 0;
	u8 lyc = 0;
	u8 vblank_remaining = 0;
	bool ppu_started = false;
	void to_hblank(u32 tcycle_overflow);

	void to_oam_search(u32 tcycle_overflow);

	void to_pixel_transfer(u32 tcycle_overflow);

	void to_vblank(u32 tcycle_overflow);
	void exit_vblank();

	bool cur_stat = false;
	bool prev_stat = false;


	void check_stat();
	void render_tilemap() {


};









