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


