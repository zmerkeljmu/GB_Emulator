#include "bits.h"
#include "cpu.h"

u8 rlca_08(Cpu* cpu) {
	u8 carry = u8read_bit(7, &cpu->reg_a);
	cpu->reg_a = cpu->reg_a << 1;
	u8set_bit(0, &cpu->reg_a, carry);
	
	if (carry == 1)
		cpu->clear_carry_flag();
	else
		cpu->clear_carry_flag();
	cpu->clear_zero_flag();
	cpu->clear_hc_flag();
	cpu->clear_s_flag();
	return 1;
}
u8 rla_18(Cpu* cpu) {
	u8 carryin = cpu->read_carry_flag();
	u8 carryout = u8read_bit(7, &cpu->reg_a);
	cpu->reg_a = cpu->reg_a << 1;

	u8set_bit(0, &cpu->reg_a, carryin);
	if (carryout == 1)
		cpu->set_carry_flag();
	else
		cpu->clear_carry_flag();
	cpu->clear_zero_flag();
	cpu->clear_hc_flag();
	cpu->clear_s_flag();
	return 1;

}

u8 rrca_0F(Cpu* cpu) {
	u8 carryout = u8read_bit(0, &cpu->reg_a);
	cpu->reg_a = cpu->reg_a >> 1;
	u8set_bit(7, &cpu->reg_a, carryout);

	if (carryout == 1)
		cpu->set_carry_flag();
	else
		cpu->clear_carry_flag();
	cpu->clear_zero_flag();
	cpu->clear_s_flag();
	cpu->clear_hc_flag();

	return 1;
}
u8 rra_1F(Cpu* cpu) {
	u8 carryin = cpu->read_carry_flag();
	u8 carryout = u8read_bit(0, &cpu->reg_a);

	cpu->reg_a = cpu->reg_a >> 1;

	u8set_bit(7, &cpu->reg_a, carryin);
	if (carryout == 0)
		cpu->set_carry_flag();
	else
		cpu->clear_carry_flag();
	cpu->clear_zero_flag();
	cpu->clear_s_flag();
	cpu->clear_hc_flag();

	return 1;

}