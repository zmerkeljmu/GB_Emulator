#pragma once
#include "memory.h"

class TestMemory : public Mmu {
public:
    // Constructor
    TestMemory(cartridge* cart, bool testing) : Mmu(cart, testing) {
        // Initialize the 64KB memory array
        memset(memory, 0, sizeof(memory));
    }

    // Override the read_byte method
    u8 read_byte(u16 address) override {
        // Simply return the value from the flat memory array
        return memory[address];
    }

    // Override the write_byte method
    void write_byte(u16 address, u8 byte) override {
        // Simply write the value to the flat memory array
        memory[address] = byte;
    }

    // Override the read_bit_reg method
    bool read_bit_reg(u16 address, u8 bit) override {
        // Read the byte and check the specific bit
        return (memory[address] & (1 << bit)) != 0;
    }

    // Override the set_bit_reg method
    void set_bit_reg(u16 address, u8 bit, u8 value) override {
        // Set or clear the specific bit in the memory array
        if (value) {
            memory[address] |= (1 << bit);
        }
        else {
            memory[address] &= ~(1 << bit);
        }
    }

private:
    // 64KB memory array
    u8 memory[common::memsize] = {};
};