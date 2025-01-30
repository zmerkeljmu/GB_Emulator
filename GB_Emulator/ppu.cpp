#include "ppu.h"
#include <iostream>
#include <algorithm>
/* 
Make a state machine that cycles through the lines and 4 modes after the correct number of cycles
Make a framebuffer that can be rendered. Maybe add video sync and/or double buffering
Render the tile data to that framebuffer
Render the tile map
Change the tile map rendering to go line by line and put it in the state machine
Start using colors from the palette
Add Y scroll. This should get the bootrom rendering properly
Add X scroll
If you haven't already, add VBLANK and STAT interrupts
Now you can start using acid2 to test your rendering
Add the window
Add sprites
*/

/*
Each frame is 70224 T cycles long and contains 154 scanlines.
One scacline takes 456 T cycles to complete a frame. Each mode takes the following number of T cycles to complete:

Mode 2
OAM scan
80 cycles

Mode 3
Drawing pixels
172–289 cycles

Mode 0
Horizontal blank
87–204 cycles

Mode 1
Vertical blank
10 "scanlines"
4560 dots
*/

/*

My plan for PPU

keep track of how many cycles are left in the current mode
when ppu tick is called check state and then call function for that state
in that state function subtract number of cycles from remaining cycles, if that number will hit 0 or go below 0 change state and run next state function (making sure to carry over the extra cycles from the previous state)

want to make sure im understanding stat IRQ blocking right, do you basically just keep 2 internal flags 
that at each point where there is a possible stat IRQ you check the STAT reg to see if that condition is
enabled, if it is you set the old_stat flag to the value of cur_stat and set cur_stat to true and if it
isn't you set cur_stat to false and only trigger an interrupt if (cur_stat && !old_stat)

two internal flags prev_stat and cur_stat
at every change of state calc stat and move cur_state to prev_state
*/

PPU::PPU(Mmu* mmu) {
	this->mmu = mmu;
}

void PPU::tick(u32 cycles) {
    
    u32 tcycles = cycles * 4;

    if (!mmu->read_bit_reg(hardware_reg::LCDC, lcdc::PPU_ENABLE))
        return;

    if (!ppu_started) {
        ppu_started = true;
        cycles_remaining = HBLANK_CYCLES;
    }

    if (tcycles >= cycles_remaining) {
        cur_state = read_ppu_mode();
        u32 overflow = tcycles - cycles_remaining;

        switch (cur_state)
        {
        case State::HBLANK:
            if (ly == 143) {
                vblank_remaining = 10;
                to_vblank(overflow);
                calc_stat(1 << stat_reg::MODE_1);
                mmu->write_byte(hardware_reg::IF, mmu->read_byte(hardware_reg::IF) | 1 << interrupt::VBLANK);
            }
            else
                to_oam_search(overflow);
            break;
        case State::OAM_SEARCH:
            to_pixel_transfer(overflow);
            break;
        case State::PIXEL_TRANSFER:
            to_hblank(overflow);
            break;
        case State::VBLANK: 
            if (vblank_remaining > 1) {
                vblank_remaining--;
                to_vblank(overflow);
            }
            else {
                to_oam_search(overflow);
				win_counter = 0;
            }
            break;
        default:
            exit(0);
            break;
        }
    }
    else {
        cycles_remaining -= tcycles;
    }
}

//tranistion to hblank
void PPU::to_hblank(u32 tcycle_overflow) {
    draw_line();
    cycles_remaining = HBLANK_CYCLES - tcycle_overflow;
    write_ppu_mode(HBLANK);
    calc_stat(1 << stat_reg::MODE_0);
}

//transition to OAM search
void PPU::to_oam_search(u32 tcycle_overflow) {
    cycles_remaining = OAM_CYCLES - tcycle_overflow;
    write_ppu_mode(OAM_SEARCH);
    ly++;
    if (ly > 153)
        ly = 0;
    calc_stat(1 << stat_reg::MODE_2);
}

//transition to pixel transfer
void PPU::to_pixel_transfer(u32 tcycle_overflow) {
    cycles_remaining = PIXEL_CYCLES - tcycle_overflow;
    write_ppu_mode(PIXEL_TRANSFER);
}

//transition to vblank
void PPU::to_vblank(u32 tcycle_overflow) {
    cycles_remaining = VBLANK_CYCLES - tcycle_overflow;
    write_ppu_mode(VBLANK);
    ly++;
}



//functions called by the mmu for io register reads
void PPU::write_lyc(u8 byte) {
    lyc = byte;
}
u8 PPU::read_ly() {
    return ly;
}
u8 PPU::read_lyc() {
    return lyc;
}
u8 PPU::read_lcdc() {
    return lcdc;
}
void PPU::write_lcdc(u8 byte) {
    lcdc = byte;
}
u8 PPU::read_scy() {
    return scy;
}
void PPU::write_scy(u8 byte) {
    scy = byte;
}
u8 PPU::read_scx() {
    return scx;
}
void PPU::write_scx(u8 byte) {
    scx = byte;
}
u8 PPU::read_bgp() {
    return bgp;
}
void PPU::write_bgp(u8 byte) {
    bgp = byte;
}
u8 PPU::read_obp0() {
    return obp0;
}
void PPU::write_obp0(u8 byte) {
	obp0 = byte;
}
u8 PPU::read_obp1() {
	return obp1;
}
void PPU::write_obp1(u8 byte) {
	obp1 = byte;
}
u8 PPU::read_wy() {
	return wy;
}
void PPU::write_wy(u8 byte) {
	wy = byte;
}
u8 PPU::read_wx() {
	return wx;
}
void PPU::write_wx(u8 byte) {
	wx = byte;
}


u8 PPU::read_stat() {
    return stat;
}
//needs to be updated because register is mixed read/write
void PPU::write_stat(u8 byte) {
    stat = byte;
}


//blocking needs to be implemented
u8 PPU::read_vram(u16 address) {
    return vram[address - VRAM_START];
}

void PPU::write_vram(u16 address, u8 byte) {
    vram[address - VRAM_START] = byte;
}

u8 PPU::read_oam_ram(u16 address) {
    return oam_ram[address - OAM_START];
}

void PPU::write_oam_ram(u16 address, u8 byte) {
    u16 index = address - OAM_START;
    oam_ram[index] = byte;
}

u8 PPU::read_ppu_mode() {
    return stat & 0b11;
}

void PPU::write_ppu_mode(u8 state) {
    stat &= 0b11111100;
    stat |= state;
}

u8 PPU::read_bgp0() {
    return bgp & 0b11;
}

u8 PPU::read_bgp1() {
    return (bgp & 0b1100) >> 2;
}

u8 PPU::read_bgp2() {
    return (bgp & 0b110000) >> 4;
}

u8 PPU::read_bgp3() {
    return (bgp & 0b11000000) >> 6;
}

u8 PPU::read_obj00() {
    return (obp0 & 0b11);
}

u8 PPU::read_obj01() {
    return (obp0 & 0b1100) >> 2;
}

u8 PPU::read_obj02() {
    return (obp0 & 0b110000) >> 4;
}

u8 PPU::read_obj03() {
	return (obp0 & 0b11000000) >> 6;
}

u8 PPU::read_obj10() {
	return (obp1 & 0b11);
}

u8 PPU::read_obj11() {
	return (obp1 & 0b1100) >> 2;
}

u8 PPU::read_obj12() {
	return (obp1 & 0b110000) >> 4;
}

u8 PPU::read_obj13() {
	return (obp1 & 0b11000000) >> 6;
}

tile PPU::read_tile(u16 address) {
    tile cur_tile;
    for (int line = 0; line < 8; line++) {
        u8 low_byte = read_vram(address + (line * 2));
        u8 high_byte = read_vram(address + (line * 2) + 1);

        for (int i = 0; i < 8; i++) {
            cur_tile.data[line][i] = ((high_byte >> (7 - i)) & 1) << 1 | ((low_byte >> (7 - i)) & 1);
        }
    }
    return cur_tile;
}

/*
Render all of VRAM to a framebuffer
const GLuint width = 128;
const GLuint height = 192;
*/
void PPU::scan_vram(GLuint* framebuffer) {
	tile* tiles = new tile[384];


	for (int i = 0; i < 384; i++) {
		u16 address = 0x8000 + (16 * i);
        tiles[i] = read_tile(address);
	}
    int row = 0;
    int column = 0;
    for (int j = 0; j < 384; ++j) {
        
        for (int tile_row = 0; tile_row < 8; tile_row++) {
            for (int tile_col = 0; tile_col < 8; tile_col++) {
                int pixel_offset = ((row * 8 + tile_row) * 128) + (column * 8 + tile_col);
                GLuint color = 0;
                u8 pixel_value = tiles[j].data[tile_row][tile_col];
                memcpy(&color, &cur_palette_colors[pixel_value], sizeof(RGBA));
                framebuffer[pixel_offset] = color;
            }
        }
        column++;
        if (column > 15) {
            column = 0;
            row++;
        }
    }
}

void PPU::render_bg_tilemap() {
	set_palette();
    u16 map_area;
    tile* tiles = new tile[32 * 32];
    u16 base;
    if (u8read_bit(lcdc::BG_TILE_MAP, &lcdc))
        map_area = MAP1_START;
    else
        map_area = MAP0_START;
    if (u8read_bit(lcdc::TILE_DATA, &lcdc))
        base = 0x8000;
    else
        base = 0x8800;
    
    for (int i = 0; i < 1024; i++) {
        if (base == 0x8000)
            tiles[i] = read_tile(0x8000 + read_vram(map_area + i) * 16);
        else
            tiles[i] = read_tile(0x8800 + (i8) read_vram(map_area + i) * 16);
    }

    int row = 0;
    int column = 0;
    for (int j = 0; j < 1024; ++j) {

        for (int tile_row = 0; tile_row < 8; tile_row++) {
            for (int tile_col = 0; tile_col < 8; tile_col++) {
                int pixel_offset = ((row * 8 + tile_row) * 256) + (column * 8 + tile_col);
                GLuint color = 0;
                u8 pixel_value = tiles[j].data[tile_row][tile_col];
                memcpy(&color, &cur_palette_colors[pixel_value], sizeof(RGBA));
                bg_buffer[pixel_offset] = color;
            }
        }
        column++;
        if (column > 31) {
            column = 0;
            row++;
        }
    }
}
//get the line of the background
void PPU::get_bg_line(GLuint* bg_line_160, u8* bg_line_data_160) {
    tile tiles[32];
    u16 map_area;
    GLuint bg_line[256];
    u8 bg_line_data[256];

    int tile_row = ((scy + ly) / 8) % 32;
    int line_in_tile = ly % 8;

    
    if (!(lcdc & 1 << lcdc::BG_ENABLE)) {
		for (int i = 0; i < 160; i++) {
			memcpy(&bg_line_160[i], &cur_palette_colors[0], sizeof(RGBA));
			bg_line_data[i] = 0;
		}
		return;
    }
    
    u16 base;
    if (u8read_bit(lcdc::BG_TILE_MAP, &lcdc))
        map_area = MAP1_START;
    else
        map_area = MAP0_START;
    if (u8read_bit(lcdc::TILE_DATA, &lcdc))
        base = 0x8000;
    else
        base = 0x8800;

    for (int num_tile = 0; num_tile < 32; num_tile++) {
        if (base == 0x8000)
            tiles[num_tile] = read_tile(0x8000 + read_vram(map_area + num_tile + (32 * tile_row)) * 16);
        else
            tiles[num_tile] = read_tile(0x9000 + (i8)read_vram(map_area + num_tile + (32 * tile_row)) * 16);
    }

    
    for (int tile_index = 0; tile_index < 32; tile_index++) {
        for (int pixel_index = 0; pixel_index < 8; pixel_index++) {
            GLuint color = 0;
            u8 pixel_value = tiles[tile_index].data[line_in_tile][pixel_index];
            memcpy(&color, &cur_palette_colors[pixel_value], sizeof(RGBA));
            bg_line_data[(tile_index * 8) + pixel_index] = pixel_value;
            bg_line[(tile_index * 8) + pixel_index] = color;
        }
    }

    u8 bg_y = (scy + ly) % 256;
    u8 bg_x;
    for (int screen_x = 0; screen_x < 160; screen_x++) {
        bg_x = (scx + screen_x) % 256;
		bg_line_data_160[screen_x] = bg_line_data[bg_x];
        bg_line_160[screen_x] = bg_line[bg_x];
    }
}

void PPU::get_window_line(GLuint* bg_line, u8* bg_line_data) {
    // Ensure window is enabled
    if (!(lcdc & (1 << lcdc::WIN_ENABLE)))
        return;

    // Start rendering at or after WY
    if (ly < wy)
        return;

	if (wx < 0 || wx > 166) {
		printf("Window X start is off-screen.\n");
		return;
	}


    int x_start = wx - 7;

	if (wy < 0 || wy > 143) {
		printf("Window Y start is off-screen.\n");
		return;
	}
    int window_line = win_counter;
    // Determine tile map and base address
    u16 map_area = (u8read_bit(lcdc::WIN_TILE_MAP, &lcdc)) ? MAP1_START : MAP0_START;
    u16 base = (u8read_bit(lcdc::TILE_DATA, &lcdc)) ? 0x8000 : 0x8800;

    // Load tiles for the current row
    tile tiles[32] = {};
    int tile_row = window_line / 8 ;
    for (int num_tile = 0; num_tile < 32; num_tile++) {
        u16 tile_address = map_area + num_tile + (32 * tile_row);
        u8 tile_id = read_vram(tile_address);

        if (base == 0x8000)
            tiles[num_tile] = read_tile(0x8000 + tile_id * 16);
        else
            tiles[num_tile] = read_tile(0x9000 + (i8)tile_id * 16);
    }

    // Render the window line
    int line_in_tile = window_line % 8;
    for (int tile_index = 0; tile_index < 32; tile_index++) {
        for (int pixel_index = 0; pixel_index < 8; pixel_index++) {
            int x_index = (tile_index * 8) + pixel_index + x_start;

            if (x_index < 0 || x_index > 159)
                continue; // Skip out-of-bounds pixels

            GLuint color = 0;
			u8 pixel_value = tiles[tile_index].data[line_in_tile][pixel_index];
            memcpy(&color, &cur_palette_colors[pixel_value], sizeof(RGBA));
            // Overwrite the corresponding position in the background line
            bg_line[x_index] = color;
            bg_line_data[x_index] = pixel_value;
        }
    }
	win_counter++;
}

static bool compare_sprites(const Sprite& a, const Sprite& b) {
    return a.x > b.x; // Sort in descending order based on x
}

void PPU::get_sprite_line(GLuint* sprite_line, u8* bg_line_data) {
    int found_sprites = 0;
    Sprite sprites[10] = {};
    u8 address_offset = 0;
    u8 sprite_size = 8;
    u8 sprite_wrote_at[160] = {};
    for (int i = 0; i < 160; i++) {
        sprite_wrote_at[i] = 254;
    }
    if (u8read_bit(lcdc::OBJ_SIZE, &lcdc))
        sprite_size = 16;

    if (!u8read_bit(lcdc::OBJ_ENABLE, &lcdc))
        return;

    //find up to 10 sprites that are rendered on this line
    while (found_sprites < 10 && address_offset < 160) {
        Sprite sprite;
        
        u8 y = read_oam_ram(OAM_START + address_offset);
        u8 x = read_oam_ram(OAM_START + address_offset + 1);
        u8 tile = read_oam_ram(OAM_START + address_offset + 2);
        u8 flags = read_oam_ram(OAM_START + address_offset + 3);
        
        sprite.set_flags(y, x, tile, flags, address_offset);

        if (ly >= (sprite.y - 16) && ly < (sprite.y - 16 + sprite_size)) {
            sprites[found_sprites] = sprite;
            found_sprites++;
        }
        address_offset += 4;
    } 

    std::sort(sprites, sprites + found_sprites, compare_sprites);
    
    for (int sprite_index = 0; sprite_index < found_sprites; sprite_index++) {
        Sprite cur_sprite = sprites[sprite_index];
        tile sprite_tile = {};
		GLuint* palette = cur_sprite.palette ? cur_obj1_palette_colors : cur_obj0_palette_colors;

        if (sprite_size == 16) {
            //check if the upper or lower tile should be selected
            if (ly >= (cur_sprite.y - 16) && ly < (cur_sprite.y - 8)) {
                if (!cur_sprite.y_flip)
                    sprite_tile = read_tile(0x8000 + ((cur_sprite.tile & 0xFE) * 16));
                else
                    sprite_tile = read_tile(0x8000 + ((cur_sprite.tile | 0x01) * 16));
            }
            else {
                if (!cur_sprite.y_flip)
                    sprite_tile = read_tile(0x8000 + ((cur_sprite.tile | 0x01) * 16));
                else
                    sprite_tile = read_tile(0x8000 + ((cur_sprite.tile & 0xFE) * 16));

            }
        }
        else {
            sprite_tile = read_tile(0x8000 + cur_sprite.tile * 16);
        }
        
        int tile_y = (ly - cur_sprite.y + 16) % 8;
        if (sprite_size == 16) {
            tile_y = (ly - (cur_sprite.y - 16)) % 8;
        }
        
        for (int tile_x = 0; tile_x < 8; tile_x++) {
            int x_offset = cur_sprite.x - 8 + tile_x;
            if (x_offset < 0 || x_offset > 159)
                continue;
            GLuint color = 0;
            int tile_x_raw = tile_x;
            int tile_y_raw = tile_y;
            //Priortized over the background
            if (!cur_sprite.priority) {
                //if the tile is not transparent
                if (cur_sprite.x_flip) {
                    tile_x = 7 - tile_x;
                }
                if (cur_sprite.y_flip)
                    tile_y = 7 - tile_y;
                u8 pixel_data = sprite_tile.data[tile_y][tile_x];
                if (pixel_data != 0) {
                    memcpy(&color, &palette[pixel_data], sizeof(RGBA));
                    //trying to fix same tile sprite priority while not breaking lower x value sprites having priority
                    if (sprite_wrote_at[x_offset] != 254) {
                        Sprite sprite_wrote = sprites[sprite_wrote_at[x_offset]];
                        if (sprite_wrote.x > cur_sprite.x || (cur_sprite.x == sprite_wrote.x && cur_sprite.oam_index < sprite_wrote.oam_index)) {
                            sprite_line[x_offset] = color;
                            sprite_wrote_at[x_offset] = sprite_index;
                        }
                    }
                    else {
                        sprite_line[x_offset] = color;
                        sprite_wrote_at[x_offset] = sprite_index;
                    }
                }
            }
            //Only draw over background color 0
            else {
                if (cur_sprite.x_flip) {
                    tile_x = 7 - tile_x;
                }
                if (cur_sprite.y_flip)
                    tile_y = 7 - tile_y;
                u8 sprite_pixel = sprite_tile.data[tile_y][tile_x];
                u8 bg_pixel = bg_line_data[x_offset];
                if (bg_pixel == 0) {
                    memcpy(&color, &palette[sprite_pixel], sizeof(RGBA));
                    if (sprite_wrote_at[x_offset] != 254) {
                        Sprite sprite_wrote = sprites[sprite_wrote_at[x_offset]];
                        if (sprite_wrote.x > cur_sprite.x || (cur_sprite.x == sprite_wrote.x && cur_sprite.oam_index < sprite_wrote.oam_index)) {
                            sprite_line[x_offset] = color;
                            sprite_wrote_at[x_offset] = sprite_index;
                        }
                    }
                    else {
                        sprite_line[x_offset] = color;
                        sprite_wrote_at[x_offset] = sprite_index;

                    }
                }
            }
            tile_x = tile_x_raw;
            tile_y = tile_y_raw;
        }
    }
}



void PPU::draw_line() {
    if (ly > 143)
        return;
    set_palette();
    
	GLuint bg_line[160];
	u8 bg_line_data[160];
    get_bg_line(bg_line, bg_line_data);
	get_window_line(bg_line, bg_line_data);
    get_sprite_line(bg_line, bg_line_data);
    for (int i = 0; i < 160; i++) {
		display_buffer[(ly * 160) + i] = bg_line[i];
	}

}

void PPU::calc_stat(u8 mode) {
    prev_stat = cur_stat;
    cur_stat = (mode & stat) || (ly == lyc);

    if (cur_stat && !prev_stat)
        mmu->write_byte(hardware_reg::IF, mmu->read_byte(hardware_reg::IF) | 1 << interrupt::LCD);
}

u8 PPU::get_state() {
    return this->cur_state;
}

void PPU::set_palette() {
    cur_palette[0] = read_bgp0();
    cur_palette[1] = read_bgp1();
    cur_palette[2] = read_bgp2();
    cur_palette[3] = read_bgp3();

    switch (cur_palette[0]) {
    case 0:
        memcpy(&cur_palette_colors[0], &cur_theme_white, sizeof(RGBA));
        break;
    case 1:
        memcpy(&cur_palette_colors[0], &cur_theme_light_gray, sizeof(RGBA));
        break;
    case 2:
        memcpy(&cur_palette_colors[0], &cur_theme_dark_gray, sizeof(RGBA));
        break;
    case 3:
        memcpy(&cur_palette_colors[0], &cur_theme_black, sizeof(RGBA));
        break;
    default:
        break;
    }

    switch (cur_palette[1]) {
    case 0:
        memcpy(&cur_palette_colors[1], &cur_theme_white, sizeof(RGBA));
        break;
    case 1:
        memcpy(&cur_palette_colors[1], &cur_theme_light_gray, sizeof(RGBA));
        break;
    case 2:
        memcpy(&cur_palette_colors[1], &cur_theme_dark_gray, sizeof(RGBA));
        break;
    case 3:
        memcpy(&cur_palette_colors[1], &cur_theme_black, sizeof(RGBA));
        break;
    default:
        break;
    }

    switch (cur_palette[2]) {
    case 0:
        memcpy(&cur_palette_colors[2], &cur_theme_white, sizeof(RGBA));
        break;
    case 1:
        memcpy(&cur_palette_colors[2], &cur_theme_light_gray, sizeof(RGBA));
        break;
    case 2:
        memcpy(&cur_palette_colors[2], &cur_theme_dark_gray, sizeof(RGBA));
        break;
    case 3:
        memcpy(&cur_palette_colors[2], &cur_theme_black, sizeof(RGBA));
        break;
    default:
        break;
    }

    switch (cur_palette[3]) {
    case 0:
        memcpy(&cur_palette_colors[3], &cur_theme_white, sizeof(RGBA));
        break;
    case 1:
        memcpy(&cur_palette_colors[3], &cur_theme_light_gray, sizeof(RGBA));
        break;
    case 2:
        memcpy(&cur_palette_colors[3], &cur_theme_dark_gray, sizeof(RGBA));
        break;
    case 3:
        memcpy(&cur_palette_colors[3], &cur_theme_black, sizeof(RGBA));
        break;
    default:
        break;
    }

	obj_palette0[0] = read_obj00();
	obj_palette0[1] = read_obj01();
	obj_palette0[2] = read_obj02();
	obj_palette0[3] = read_obj03();


    switch (obj_palette0[0]) {
    case 0:
        memcpy(&cur_obj0_palette_colors[0], &cur_theme_white, sizeof(RGBA));
        break;
    case 1:
        memcpy(&cur_obj0_palette_colors[0], &cur_theme_light_gray, sizeof(RGBA));
        break;
    case 2:
        memcpy(&cur_obj0_palette_colors[0], &cur_theme_dark_gray, sizeof(RGBA));
        break;
    case 3:
        memcpy(&cur_obj0_palette_colors[0], &cur_theme_black, sizeof(RGBA));
        break;
    default:
        break;
    }

    switch (obj_palette0[1]) {
    case 0:
        memcpy(&cur_obj0_palette_colors[1], &cur_theme_white, sizeof(RGBA));
        break;
    case 1:
        memcpy(&cur_obj0_palette_colors[1], &cur_theme_light_gray, sizeof(RGBA));
        break;
    case 2:
        memcpy(&cur_obj0_palette_colors[1], &cur_theme_dark_gray, sizeof(RGBA));
        break;
    case 3:
        memcpy(&cur_obj0_palette_colors[1], &cur_theme_black, sizeof(RGBA));
        break;
    default:
        break;
    }

    switch (obj_palette0[2]) {
    case 0:
        memcpy(&cur_obj0_palette_colors[2], &cur_theme_white, sizeof(RGBA));
        break;
    case 1:
        memcpy(&cur_obj0_palette_colors[2], &cur_theme_light_gray, sizeof(RGBA));
        break;
    case 2:
        memcpy(&cur_obj0_palette_colors[2], &cur_theme_dark_gray, sizeof(RGBA));
        break;
    case 3:
        memcpy(&cur_obj0_palette_colors[2], &cur_theme_black, sizeof(RGBA));
        break;
    default:
        break;
    }

    switch (obj_palette0[3]) {
    case 0:
        memcpy(&cur_obj0_palette_colors[3], &cur_theme_white, sizeof(RGBA));
        break;
    case 1:
        memcpy(&cur_obj0_palette_colors[3], &cur_theme_light_gray, sizeof(RGBA));
        break;
    case 2:
        memcpy(&cur_obj0_palette_colors[3], &cur_theme_dark_gray, sizeof(RGBA));
        break;
    case 3:
        memcpy(&cur_obj0_palette_colors[3], &cur_theme_black, sizeof(RGBA));
        break;
    default:
        break;
    }

    obj_palette1[0] = read_obj10();
    obj_palette1[1] = read_obj11();
    obj_palette1[2] = read_obj12();
    obj_palette1[3] = read_obj13();

    switch (obj_palette1[0]) {
    case 0:
        memcpy(&cur_obj1_palette_colors[0], &cur_theme_white, sizeof(RGBA));
        break;
    case 1:
        memcpy(&cur_obj1_palette_colors[0], &cur_theme_light_gray, sizeof(RGBA));
        break;
    case 2:
        memcpy(&cur_obj1_palette_colors[0], &cur_theme_dark_gray, sizeof(RGBA));
        break;
    case 3:
        memcpy(&cur_obj1_palette_colors[0], &cur_theme_black, sizeof(RGBA));
        break;
    default:
        break;
    }

    switch (obj_palette1[1]) {
    case 0:
        memcpy(&cur_obj1_palette_colors[1], &cur_theme_white, sizeof(RGBA));
        break;
    case 1:
        memcpy(&cur_obj1_palette_colors[1], &cur_theme_light_gray, sizeof(RGBA));
        break;
    case 2:
        memcpy(&cur_obj1_palette_colors[1], &cur_theme_dark_gray, sizeof(RGBA));
        break;
    case 3:
        memcpy(&cur_obj1_palette_colors[1], &cur_theme_black, sizeof(RGBA));
        break;
    default:
        break;
    }

    switch (obj_palette1[2]) {
    case 0:
        memcpy(&cur_obj1_palette_colors[2], &cur_theme_white, sizeof(RGBA));
        break;
    case 1:
        memcpy(&cur_obj1_palette_colors[2], &cur_theme_light_gray, sizeof(RGBA));
        break;
    case 2:
        memcpy(&cur_obj1_palette_colors[2], &cur_theme_dark_gray, sizeof(RGBA));
        break;
    case 3:
        memcpy(&cur_obj1_palette_colors[2], &cur_theme_black, sizeof(RGBA));
        break;
    default:
        break;
    }

    switch (obj_palette1[3]) {
    case 0:
        memcpy(&cur_obj1_palette_colors[3], &cur_theme_white, sizeof(RGBA));
        break;
    case 1:
        memcpy(&cur_obj1_palette_colors[3], &cur_theme_light_gray, sizeof(RGBA));
        break;
    case 2:
        memcpy(&cur_obj1_palette_colors[3], &cur_theme_dark_gray, sizeof(RGBA));
        break;
    case 3:
        memcpy(&cur_obj1_palette_colors[3], &cur_theme_black, sizeof(RGBA));
        break;
    default:
        break;
    }



}
