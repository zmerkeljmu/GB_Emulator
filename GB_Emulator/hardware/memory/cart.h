#pragma once
#include <string>
#include "common.h"

typedef struct {
	u8 entry[4];
	u8 logo[0x30];

	char title[16];

	u16 new_l_code;
	u8 sgb;
	u8 cart_type;
	u8 rom_size;
	u8 ram_size;
	u8 dest_code;
	u8 old_l_code;
	u8 version;
	u8 header_checksum;
	u16 global_checksum;
} rom_header;



class cartridge {

public:
	rom_header *header;
	
	cartridge(std::string filename);

	u8 read_rom(u16 address);

	u8 read_external_ram(u16 address);
	void write_external_ram(u16 address, u8 byte);
	void print_header_data();
private:
	char rom_data[0x7FFF];
	u8 external_ram[EXTERNAL_END - EXTERNAL_START];
};

