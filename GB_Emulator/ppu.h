#pragma once
#include "common.h"
#include "memory.h"
#include <SDL_opengl.h>


class PPU {
public:
	PPU(Mmu* mmu);
	Mmu* mmu;
	void scan_vram(GLuint* framebuffer);
	void render_bg_tilemap();
	GLuint sprite_buffer8[64 * 40] = {};
	GLuint sprite_buffer16[64 * 80] = {};

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

	u8 get_state();



private:
	u8 vram[0x1FFF + 1] = {};
	u8 oam_ram[0x9F + 1] = {};
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

	bool cur_stat = false;
	bool prev_stat = false;

	int win_counter = 0;

	u8 read_bgp0();
	u8 read_bgp1();
	u8 read_bgp2();
	u8 read_bgp3();

	u8 read_obj00();
	u8 read_obj01();
	u8 read_obj02();
	u8 read_obj03();


	u8 read_obj10();
	u8 read_obj11();
	u8 read_obj12();
	u8 read_obj13();

	tile read_tile(u16 address);

	u8 read_ppu_mode();
	void write_ppu_mode(u8 state);
	void draw_line();
	void get_bg_line(GLuint* bg_line, u8* bg_line_data);
	void get_window_line(GLuint* window_line, u8* window_line_data);
	void get_sprite_line(GLuint* sprite_line, u8* bg_line_data);
	void calc_stat(u8 mode);

	u8 cur_palette[4] = { 0, 0, 0, 0 };
	GLuint cur_palette_colors[4] = { 0,0,0,0 };
	
	u8 obj_palette0[4] = { 0, 0, 0, 0 };
	u8 obj_palette1[4] = { 0, 0, 0, 0 };

	GLuint cur_obj0_palette_colors[4] = {0,0,0,0};
	GLuint cur_obj1_palette_colors[4] = { 0,0,0,0 };


	RGBA cur_theme_white = { 0x9B, 0XBC, 0X0F, 255 };
	RGBA cur_theme_light_gray = { 0x8B, 0xAC, 0x0F, 255 };
	RGBA cur_theme_dark_gray = { 0x30, 0x62, 0x30, 255 };
	RGBA cur_theme_black = { 0x0F, 0x38, 0x0F, 255 };


	void set_palette();
};

class Sprite {
public:
	u8 y;
	u8 x;
	u8 tile;
	bool priority;
	bool y_flip;
	bool x_flip;
	bool palette;

	Sprite() {
		this->y = 0;
		this->x = 0;
		this->tile = 0;
		this->priority = false;
		this->y_flip = false;
		this->x_flip = false;
		this->palette = false;
	}

	void set_flags(u8 y, u8 x, u8 tile, u8 flags) {
		this->priority = flags & (1 << 7);
		this->y_flip = flags & (1 << 6);
		this->x_flip = flags & (1 << 5);
		this->palette = flags & (1 << 4);

		this->y = y;
		this->x = x;
		this->tile = tile;
	}

};







