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
                DisplayPixel::White => RGB8 {
                    r: 0x9B,
                    g: 0xBC,
                    b: 0x0F,
                },
                DisplayPixel::LightGrey => RGB8 {
                    r: 0x8B,
                    g: 0xAC,
                    b: 0x0F,
                },
                DisplayPixel::DarkGrey => RGB8 {
                    r: 0x30,
                    g: 0x62,
                    b: 0x30,
                },
                DisplayPixel::Black => RGB8 {
                    r: 0x0F,
                    g: 0x38,
                    b: 0x0F,
                }

*/

PPU::PPU(Mmu* mmu) {
	this->mmu = mmu;
}

void PPU::scan_vram() {
	tile tiles[16][24];
	
	for (int i = 0; i <= 0x7F; i++) {
		u16 address = 0x8000 + (16 * i);
		
	}

}