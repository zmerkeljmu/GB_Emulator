#pragma once
#include "common.h"
#include "memory.h"
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
	void render_bg_tilemap();

	void tick(u32 cycles);

	void write_lyc(u8 byte);
	u8 read_ly();
	u8 read_lyc();
	u8 read_lcdc();
	void write_lcdc(u8 byte);
	u8 read_scy();
	void write_scy(u8 byte);
	u8 read_scx();
	void write_scx(u8 byte);
	u8 read_bgp();
	void write_bgp(u8 byte);
	u8 read_stat();
	void write_stat(u8 byte);
	u8 read_obp0();
	void write_obp0(u8 byte);
	u8 read_obp1();
	void write_obp1(u8 byte);
	u8 read_wy();
	void write_wy(u8 byte);
	u8 read_wx();
	void write_wx(u8 byte);

	u8 read_vram(u16 address);
	void write_vram(u16 address, u8 byte);

	u8 read_oam_ram(u16 address);
	void write_oam_ram(u16 address, u8 byte);
	GLuint display_buffer[160 * 144] = {};
	GLuint bg_buffer[256 * 256] = {};
	void get_bg_line(GLuint* bg_line);


private:
	u8 vram[0x1FFF];
	u8 oam_ram[0x9F];
	u8 cur_state = State::HBLANK;
	u32 cycles_remaining = 0;
	u8 stat = 0x85;
	u8 ly = 0;
	u8 lyc = 0;
	u8 lcdc = 0x91;
	u8 scx = 0;
	u8 scy = 0;
	u8 bgp = 0xFC;
	u8 obp0 = 0;
	u8 obp1 = 0;
	u8 wy = 0;
	u8 wx = 0;
	u8 vblank_remaining = 0;
	bool ppu_started = false;
	void to_hblank(u32 tcycle_overflow);

	void to_oam_search(u32 tcycle_overflow);

	void to_pixel_transfer(u32 tcycle_overflow);

	void to_vblank(u32 tcycle_overflow);
	void exit_vblank();

	bool cur_stat = false;
	bool prev_stat = false;

	u8 read_bgp0();
	u8 read_bgp1();
	u8 read_bgp2();
	u8 read_bgp3();

	tile read_tile(u16 address);

	u8 read_ppu_mode();
	void write_ppu_mode(u8 state);
	void draw_line();

	void calc_stat(u8 mode);
};









