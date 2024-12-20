#include "cart.h"
#include "cpu.h"
#include "common.h"

int main() {
	std::string filepath = "C:/Users/David/Documents/CS/EMU/pokemon_red.gb";
	cartridge cart(filepath);

	cart.print_header_data();
}