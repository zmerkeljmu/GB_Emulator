#include "dma.h"

DMA::DMA(Mmu* mmu) {
    this->mmu = mmu;
    this->init_address = 0;
    this->cycles_remaining = 0;
    this->dma_active = false;
}

void DMA::execute_dma_transfer(u8 address) {
    init_address = address << 8; // Calculate source address
    cycles_remaining = 160;     // DMA transfer takes 160 cycles (1 byte per cycle)
    dma_active = true;          // Mark DMA as active
}

void DMA::tick(u8 cycles) {
    if (dma_active && cycles_remaining > 0) {
        u8 bytes_to_transfer = std::min(cycles, cycles_remaining);
        for (u8 i = 0; i < bytes_to_transfer; ++i) {
            u8 data = mmu->read_byte(init_address + (160 - cycles_remaining));
            mmu->write_byte(0xFE00 + (160 - cycles_remaining), data);
            --cycles_remaining;
        }

        if (cycles_remaining == 0) {
            dma_active = false;
        }
    }
}

bool DMA::is_dma_active() const {
    return dma_active;
}
