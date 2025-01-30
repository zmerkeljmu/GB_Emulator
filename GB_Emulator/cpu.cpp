#include "cpu.h"


Cpu::Cpu(Mmu* memory) {

	pc = 0x100;
	sp = 0xFFFE;
	reg_a = 0x01;
	reg_f = 0xB0;
	reg_b = 0x00;
	reg_c = 0x13;
	reg_d = 0x00;
	reg_e = 0xD8;
	reg_h = 0x01;
	reg_l = 0x4D;

	ime = false;
	halted = false;
	cb = false;
	pending_ei = false;
	mem = memory;

	debug = true;

	// Create or overwrite the log file on initialization
	std::ofstream logfile("cpu_log.txt");
	logfile.close();

	bootrom();
}

int Cpu::step() {
    bool set_ime = this->pending_ei;
    int cycles = 0;

    if (handle_interrupts())
        cycles += 5;

    if (!halted) {
        //fetch	
        if (debug) {
            log_state();
        }
        instruction inst = fetch_instruction();
        //decode
        //execute
        cycles += inst.function(this);
    } else {
        cycles += 1;
    }

    if (set_ime) {
        this->ime = true;
        this->pending_ei = false;
    }
    return cycles;
}



instruction Cpu::fetch_instruction() {
	u8 opcode = this->read_pc();
	instruction inst;
	if (!this->cb) 
		inst = instruction_list.base[opcode];
	else {
		inst = instruction_list.cb[opcode];
		this->cb = false;
	}
	return inst;
}

u8 Cpu::read_pc() {
	u8 res = this->mem->read_byte(this->pc);
	this->pc++;
	return res;
}

void Cpu::set_carry_flag() {
	u8set_bit(C_FLAG, &this->reg_f, 1);
}

void Cpu::clear_carry_flag() {
	u8set_bit(C_FLAG, &this->reg_f, 0);
}

bool Cpu::read_carry_flag() {
	return u8read_bit(C_FLAG, &this->reg_f);
}

void Cpu::set_hc_flag() {
	u8set_bit(H_FLAG, &this->reg_f, 1);
}

void Cpu::clear_hc_flag() {
	u8set_bit(H_FLAG, &this->reg_f, 0);
}

bool Cpu::read_hc_flag() {
	return u8read_bit(H_FLAG, &this->reg_f);

}

void Cpu::set_s_flag() {
	u8set_bit(S_FLAG, &this->reg_f, 1);
}

void Cpu::clear_s_flag() {
	u8set_bit(S_FLAG, &this->reg_f, 0);
}

bool Cpu::read_s_flag() {
	return u8read_bit(S_FLAG, &this->reg_f);

}

void Cpu::set_zero_flag() {
	u8set_bit(Z_FLAG, &this->reg_f, 1);
}

void Cpu::clear_zero_flag() {
	u8set_bit(Z_FLAG, &this->reg_f, 0);
}

bool Cpu::read_zero_flag() {
	return u8read_bit(Z_FLAG, &this->reg_f);
}

void Cpu::print_flags() {
	printf("F register: %#02x\nZero Flag: %d\nS Flag: %d\nH Flag: %d\nC Flag: %d\n", this->reg_f, this->read_zero_flag(), this->read_s_flag(), this->read_hc_flag(), this->read_carry_flag());
}


u16 Cpu::read_af() {
	u16 a = reg_a;
	u16 f = reg_f;
	return (a << 8) | f;
}

u16 Cpu::read_bc() {
	u16 b = reg_b;
	u16 c = reg_c;
	return (b << 8) | c;
}
u16 Cpu::read_de() {
	u16 d = reg_d;
	u16 e = reg_e;
	return (d << 8) | e;
}
u16 Cpu::read_hl() {
	u16 h = reg_h;
	u16 l = reg_l;
	return (h << 8) | l;
}

void Cpu::write_af(u16 value) {
	u8 high_bits = (u8) (value >> 8);
	u8 low_bits = (u8) value;
	this->reg_a = high_bits;
	this->reg_f = low_bits;
}

void Cpu::write_bc(u16 value) {
	u8 high_bits = (u8) (value >> 8);
	u8 low_bits = (u8) value;
	this->reg_b = high_bits;
	this->reg_c = low_bits;
}

void Cpu::write_de(u16 value) {
	u8 high_bits = (u8)(value >> 8);
	u8 low_bits = (u8) value;
	this->reg_d = high_bits;
	this->reg_e = low_bits;
}

void Cpu::write_hl(u16 value) {
	u8 high_bits = (u8)(value >> 8);
	u8 low_bits = (u8) value;
	this->reg_h = high_bits;
	this->reg_l = low_bits;
}

bool Cpu::handle_interrupts() {

	u16 vector = 0;
	

	if (read_bit_IE(interrupt::VBLANK) && read_bit_IF(interrupt::VBLANK)) {
		this->halted = false;
		if (ime) {
			//if (debug)
				printf("VBLANK INTERRUPT\n");
			clear_bit_IF(interrupt::VBLANK);
			vector = interrupt::VBLANK_ADDR;
		}
	}
	else if (read_bit_IE(interrupt::LCD) && read_bit_IF(interrupt::LCD)) {
		this->halted = false;
		if (ime) {
			if (debug)
				printf("LCD INTERRUPT\n");
			clear_bit_IF(interrupt::LCD);
			vector = interrupt::LCD_ADDR;
		}
	}
	else if (read_bit_IE(interrupt::TIMER) && read_bit_IF(interrupt::TIMER)) {
		this->halted = false;
		if (ime) {
			//if (debug)
				printf("TIMER INTERRUPT\n");
			clear_bit_IF(interrupt::TIMER);
			vector = interrupt::TIMER_ADDR;
		}
	}
	else if (read_bit_IE(interrupt::SERIAL) && read_bit_IF(interrupt::SERIAL)) {
		this->halted = false;
		if (ime) {
			if (debug)
				printf("SERIAL INTERRUPT\n");
			clear_bit_IF(interrupt::SERIAL);
			vector = interrupt::SERIAL_ADDR;
		}
	}
	else if (read_bit_IE(interrupt::JOYPAD) && read_bit_IF(interrupt::JOYPAD)) {
		this->halted = false;
		if (ime) {
			if (debug)
				printf("JOYPAD INTERRUPT\n");
			clear_bit_IF(interrupt::JOYPAD);
			vector = interrupt::JOYPAD_ADDR;
		}
	}

	if (ime && (vector > 0)) {
		this->ime = false;
		push_pc();
		this->pc = vector;
		this->pending_ei = false;
		return true;
	}

	return false;
}

bool Cpu::read_bit_IE(int bit) {
	return ie_reg & (1 << bit);
}

bool Cpu::read_bit_IF(int bit) {
	return if_reg & (1 << bit);
}

void Cpu::clear_bit_IF(int bit) {
	if_reg &= ~(1 << bit);
}

void Cpu::stack_push(u8* reg_from) {
	this->sp--;
	this->mem->write_byte(this->sp, *reg_from);
	return;
}

void Cpu::push_pc() {
	u8 low = (u8)this->pc;
	u8 high = (u8)((this->pc) >> 8);
	stack_push(&high);
	stack_push(&low);
	return;
}

void Cpu::bootrom() {
	mem->write_byte(hardware_reg::SB, 0x00);
	mem->write_byte(hardware_reg::SC, 0x7E);
}

u8 Cpu::read_ie() {
	return ie_reg;
}
u8 Cpu::read_if() {
	return 0b11100000 | if_reg;
}

void Cpu::write_ie(u8 byte) {
	ie_reg = byte;
}
void Cpu::write_if(u8 byte) {
	if_reg = byte;
}

u8 Cpu::read_joyp() {
	u8 result = joyp | 0xCF; // Preserve unused upper bits (6 and 7), default lower bits to 1

	if (!(joyp & 0x10)) { // P14 = 0 -> Directional buttons selected
		result &= ~(0x0F); // Clear the lower 4 bits for directional buttons
		result |= ((!button_down) << 3) | ((!button_up) << 2) | ((!button_left) << 1) | (!button_right);
	}
	if (!(joyp & 0x20)) { // P15 = 0 -> Action buttons selected
		result &= ~(0x0F); // Clear the lower 4 bits for action buttons
		result |= ((!button_start) << 3) | ((!button_select) << 2) | ((!button_b) << 1) | (!button_a);
	}

	// Debugging output
	// printf("joyp: %x\n", result);

	return result;
}

void Cpu::write_joyp(u8 byte) {
	joyp = 0b110000 & byte;
}


void Cpu::log_state() {
	if (!cb) {
		std::ofstream logfile("cpu_log.txt", std::ios_base::app);
		if (logfile.is_open()) {
			logfile << "A:" << std::hex << std::setw(2) << std::setfill('0') << (int)reg_a << " "
					<< "F:" << std::hex << std::setw(2) << std::setfill('0') << (int)reg_f << " "
					<< "B:" << std::hex << std::setw(2) << std::setfill('0') << (int)reg_b << " "
					<< "C:" << std::hex << std::setw(2) << std::setfill('0') << (int)reg_c << " "
					<< "D:" << std::hex << std::setw(2) << std::setfill('0') << (int)reg_d << " "
					<< "E:" << std::hex << std::setw(2) << std::setfill('0') << (int)reg_e << " "
					<< "H:" << std::hex << std::setw(2) << std::setfill('0') << (int)reg_h << " "
					<< "L:" << std::hex << std::setw(2) << std::setfill('0') << (int)reg_l << " "
					<< "SP:" << std::hex << std::setw(4) << std::setfill('0') << sp << " "
					<< "PC:" << std::hex << std::setw(4) << std::setfill('0') << pc << " "
					<< "PCMEM:" << std::hex << std::setw(2) << std::setfill('0') << (int)mem->read_byte(pc) << ","
					<< std::hex << std::setw(2) << std::setfill('0') << (int)mem->read_byte(pc + 1) << ","
					<< std::hex << std::setw(2) << std::setfill('0') << (int)mem->read_byte(pc + 2) << ","
					<< std::hex << std::setw(2) << std::setfill('0') << (int)mem->read_byte(pc + 3) << " "
					<< "IE:" << std::hex << std::setw(2) << std::setfill('0') << (int)read_ie() << " "
					<< "IF:" << std::hex << std::setw(2) << std::setfill('0') << (int)read_if() << " "
					<< "IME:" << ime << " "
				<< "TAC" << std::hex << std::setw(2) << std::setfill('0') << (int)mem->read_byte(hardware_reg::TAC) << " "
					<< "TIMA" << std::hex << std::setw(2) << std::setfill('0') << (int)mem->read_byte(hardware_reg::TIMA) << "\n";
			logfile.close();
		}
	}
}
