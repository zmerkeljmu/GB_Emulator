#include "16bit_load.h"
#include "cpu.h"


u8 ldbcu16_01(Cpu* cpu) {
	u16 low = cpu->read_pc();
	u16 high = cpu->read_pc();
	u16 result = (high << 8) | low;
	cpu->write_bc(result);

	return 3;
}
u8 lddeu16_11(Cpu* cpu) {
	u16 low = cpu->read_pc();
	u16 high = cpu->read_pc();
	u16 result = (high << 8) | low;
	cpu->write_de(result);

	return 3;
}
u8 ldhlu16_21(Cpu* cpu) {
	u16 low = cpu->read_pc();
	u16 high = cpu->read_pc();
	u16 result = (high << 8) | low;
	cpu->write_hl(result);

	return 3;
}
u8 ldspu16_31(Cpu* cpu) {
	u16 low = cpu->read_pc();
	u16 high = cpu->read_pc();
	u16 result = (high << 8) | low;
	cpu->sp = result;

	return 3;
}

u8 ldsphl_F9(Cpu* cpu) {
	u16 hl = cpu->read_hl();
	cpu->sp = hl;
	return 2;
}


u8 ldu16sp_08(Cpu* cpu) {
	u16 addlow = cpu->read_pc();
	u16 addhigh = cpu->read_pc();
	u16 address = (addhigh << 8) | addlow;


	u8 splow = cpu->sp & 0xFF;
	u8 sphigh = cpu->sp >> 8;
	cpu->mem->write_byte(address, splow);
	cpu->mem->write_byte(address + 1, sphigh);
	return 5;
}