#include "ppu.h"
#include <iostream>
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

PPU::PPU(Mmu* mmu) : oam_ram{}, vram{} {
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
    calc_stat(1 << stat_reg::MODE_1);
    mmu->write_byte(hardware_reg::IF, interrupt::VBLANK);
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
    oam_ram[address - OAM_START] = byte;
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
                switch (tiles[j].data[tile_row][tile_col]) {
                case WHITE:
                    memcpy(&color, &white, sizeof(RGBA));
                    break;
                case LIGHT_GRAY:
                    memcpy(&color, &light_gray, sizeof(RGBA));
                    break;
                case DARK_GRAY:
                    memcpy(&color, &dark_gray, sizeof(RGBA));
                    break;
                case BLACK:
                    memcpy(&color, &black, sizeof(RGBA));
                    break;
                default:
                    break;
                }
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
                switch (tiles[j].data[tile_row][tile_col]) {
                case WHITE:
                    memcpy(&color, &white, sizeof(RGBA));
                    break;
                case LIGHT_GRAY:
                    memcpy(&color, &light_gray, sizeof(RGBA));
                    break;
                case DARK_GRAY:
                    memcpy(&color, &dark_gray, sizeof(RGBA));
                    break;
                case BLACK:
                    memcpy(&color, &black, sizeof(RGBA));
                    break;
                default:
                    break;
                }
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

void PPU::get_bg_line(GLuint* bg_line) {
    tile tiles[32];
    u16 map_area;

    int tile_row = ((scy + ly) / 8) % 32;
    int line_in_tile = ly % 8;

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
            tiles[num_tile] = read_tile(0x8800 + (i8)read_vram(map_area + num_tile + (32 * tile_row)) * 16);
    }
    
    for (int tile_index = 0; tile_index < 32; tile_index++) {
        for (int pixel_index = 0; pixel_index < 8; pixel_index++) {
            GLuint color = 0;
            switch (tiles[tile_index].data[line_in_tile][pixel_index]) {
            case WHITE:
                memcpy(&color, &white, sizeof(RGBA));
                break;
            case LIGHT_GRAY:
                memcpy(&color, &light_gray, sizeof(RGBA));
                break;
            case DARK_GRAY:
                memcpy(&color, &dark_gray, sizeof(RGBA));
                break;
            case BLACK:
                memcpy(&color, &black, sizeof(RGBA));
                break;
            default:
                printf("ERROR\n");
                exit(0);
                break;
            }
            bg_line[(tile_index * 8) + pixel_index] = color;
        }
    }
}

void PPU::draw_line() {
    if (ly > 143)
        return;
    GLuint bg_line[256];
    get_bg_line(bg_line);
    int display_offset;
    
    u8 bg_y = (scy + ly) % 256;
    u8 bg_x;
    for (int screen_x = 0; screen_x < 160; screen_x++) {
        bg_x = (scx + screen_x) % 256;
        display_offset = (ly * 160) + screen_x;
        display_buffer[display_offset] = bg_line[bg_x];
    }
}

void PPU::calc_stat(u8 mode) {
    prev_stat = cur_stat;
    cur_stat = (mode & stat) && (ly == lyc);

    if (cur_stat && !prev_stat)
        mmu->set_bit_reg(hardware_reg::IF, interrupt::LCD, 1);
}
