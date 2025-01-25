#pragma once
#include "memory.h"

class DMA {
public:
	DMA(Mmu* mmu);
	void execute_dma_transfer(u8 address);
	void tick(u8 cycles);   
	bool is_dma_active() const;


private:
	Mmu* mmu;
	u8 cycles_remaining;
	u16 init_address;
	bool dma_active;
};