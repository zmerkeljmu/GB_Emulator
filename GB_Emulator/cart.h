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
	char *rom_data;
	
	cartridge(std::string filename);

	void print_header_data();
};

