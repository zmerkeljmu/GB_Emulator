#include "ppu.h"

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

*/

PPU::PPU(Mmu* mmu) {
	this->mmu = mmu;
}

void PPU::tick(u32 cycles) {
    
    if (!mmu->read_bit_reg(hardware_reg::LCDC, lcdc::PPU_ENABLE))
        return;


    u8 state = mmu->read_ppu_mode();

    switch (state)
    {
    case State::HBLANK:
        break;
    case State::OAM_SEARCH:
        break;
    case State::PIXEL_TRANSFER:
        break;
    case State::VBLANK:
        break;
    default:
        exit(0);
        break;
    }
}

/*

void PPU::handle_hblank() {

}

void PPU::handle_oam_search() {}

void PPU::handle_pixel_transfer() {}

void PPU::handle_vblank() {}
*/







































/*
const GLuint width = 128;
const GLuint height = 192;
*/
void PPU::scan_vram(GLuint* framebuffer) {
	tile tiles[384];
    
	for (int i = 0; i < 384; i++) {
		u16 address = 0x8000 + (16 * i);
        tiles[i] = this->mmu->read_tile(address);
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