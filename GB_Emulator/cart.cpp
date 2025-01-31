#include "cart.h"
#include <iostream>
#include <fstream>
#include <vector>

cartridge::cartridge(std::string file_name) {

	std::streampos file_size;
	std::ifstream rom_file;
	
	rom_file.open(file_name, std::ios_base::in | std::ios_base::binary);

	if (rom_file.is_open()) {
		std::cout << "file opened sucessfully" << std::endl;
	}
	else {
		std::cout << "file not opened sucessfully";
		exit(-1);
	}
	
	rom_file.seekg(0, std::ios::end);
	file_size = rom_file.tellg();
	rom_file.seekg(0, std::ios::beg);

	std::cout << "File size: " << file_size << std::endl;
	
	rom_file.read(rom_data, file_size);

	char* addr = rom_data;

	std::cout << rom_file.gcount() << " chars used" << std::endl;

	rom_file.close();
	
	header = (rom_header*) (addr + 0x100);
}

void cartridge::print_header_data() {
    printf("Title: %s\n", header->title);
    switch (header->cart_type) {
        case 0x00: printf("ROM ONLY\n"); break;
        case 0x01: printf("MBC1\n"); break;
        case 0x02: printf("MBC1+RAM\n"); break;
        case 0x03: printf("MBC1+RAM+BATTERY\n"); break;
        case 0x05: printf("MBC2\n"); break;
        case 0x06: printf("MBC2+BATTERY\n"); break;
        case 0x08: printf("ROM+RAM\n"); break;
        case 0x09: printf("ROM+RAM+BATTERY\n"); break;
        case 0x0B: printf("MMM01\n"); break;
        case 0x0C: printf("MMM01+RAM\n"); break;
        case 0x0D: printf("MMM01+RAM+BATTERY\n"); break;
        case 0x0F: printf("MBC3+TIMER+BATTERY\n"); break;
        case 0x10: printf("MBC3+TIMER+RAM+BATTERY\n"); break;
        case 0x11: printf("MBC3\n"); break;
        case 0x12: printf("MBC3+RAM\n"); break;
        case 0x13: printf("MBC3+RAM+BATTERY\n"); break;
        case 0x19: printf("MBC5\n"); break;
        case 0x1A: printf("MBC5+RAM\n"); break;
        case 0x1B: printf("MBC5+RAM+BATTERY\n"); break;
        case 0x1C: printf("MBC5+RUMBLE\n"); break;
        case 0x1D: printf("MBC5+RUMBLE+RAM\n"); break;
        case 0x1E: printf("MBC5+RUMBLE+RAM+BATTERY\n"); break;
        case 0x20: printf("MBC6\n"); break;
        case 0x22: printf("MBC7+SENSOR+RUMBLE+RAM+BATTERY\n"); break;
        case 0xFC: printf("POCKET CAMERA\n"); break;
        case 0xFD: printf("BANDAI TAMA5\n"); break;
        case 0xFE: printf("HuC3\n"); break;
        case 0xFF: printf("HuC1+RAM+BATTERY\n"); break;
        default: printf("Unknown cartridge type\n"); break;
    }
}

u8 cartridge::read_rom(u16 address) {
	return rom_data[address];
}

u8 cartridge::read_external_ram(u16 address) {
	return external_ram[address - EXTERNAL_START];
}

void cartridge::write_external_ram(u16 address, u8 byte) {
	external_ram[address - EXTERNAL_START] = byte;
}


