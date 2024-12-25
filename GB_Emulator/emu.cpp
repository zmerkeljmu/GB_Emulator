#include "cart.h"
#include "cpu.h"
#include "common.h"
#include <iostream>

int main() {
	std::string filepath = "C:/Users/David/Documents/CS/EMU/pokemon_red.gb";
	cartridge cart(filepath);

	cart.print_header_data();
	Mmu mem(&cart);


	Cpu cpu(&mem);

	cpu.print_flags();

	u8 test = 0;
	u8set_bit(3, &test, 1);
	printf("%d\n", test);
	printf("%d\n", u8read_bit(2, &test));
	u8set_bit(1, &test, 1);
	printf("%d\n", test);

	test = 255;
	test++;
	printf("%d\n", test);

	cpu.reg_b = 0xFF;
	cpu.reg_c = 0x00;
	
	u16 res = cpu.read_bc();
	printf("Register BC: 0x%04x\n", res);


	cpu.write_af(0x14AB);

	printf("AF REGISTER: 0x%04x\n", cpu.read_af());
}