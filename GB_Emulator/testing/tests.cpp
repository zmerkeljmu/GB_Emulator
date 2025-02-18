#include "cart.h"
#include "common.h"
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include <vector>
#include <sstream>
#include <string>
#include "tests.h"

void test_json_individual(Cpu* cpu, int hexval, bool cb) {
    using json = nlohmann::json;
    std::string pathname;
    if (cb)
        pathname = "C:\\Users\\David\\Documents\\CS\\EMU\\json\\sm83\\v1\\CB {}.json";
    else
        pathname = "C:\\Users\\David\\Documents\\CS\\EMU\\json\\sm83\\v1\\{}.json";
    std::stringstream ss;
    ss << std::hex << std::setw(2) << std::setfill('0') << hexval;
    std::string hexString = ss.str();

    size_t placeholderPos = pathname.find("{}");
    if (placeholderPos != std::string::npos) {
        pathname.replace(placeholderPos, 2, hexString);
    }
    std::cout << pathname;

    // Load the JSON file
    std::ifstream f(pathname);
    if (!f.is_open()) {
        std::cerr << "Instruction doesn't exist\n";
        return;
    }
    int i = 1;
    // Parse the JSON
    json data = json::parse(f);
    int cycles_actual;
    int cycles_expected;
    bool failed = false;

    // Iterate over the array of objects
    for (const auto& el : data) {
        failed = false;
        std::cout << el["name"].get<std::string>() << "\n";

        cpu->pc = el["initial"]["pc"].get<int>();
        cpu->sp = el["initial"]["sp"].get<int>();
        cpu->reg_a = el["initial"]["a"].get<int>();
        cpu->reg_b = el["initial"]["b"].get<int>();
        cpu->reg_c = el["initial"]["c"].get<int>();
        cpu->reg_d = el["initial"]["d"].get<int>();
        cpu->reg_e = el["initial"]["e"].get<int>();
        cpu->reg_f = el["initial"]["f"].get<int>();
        cpu->reg_h = el["initial"]["h"].get<int>();
        cpu->reg_l = el["initial"]["l"].get<int>();
        cpu->ime = el["initial"]["ime"].get<int>();
        cpu->pending_ei = false;
        //reset ram
        for (int i = 0; i <= 0xFFFF; i++) {
            cpu->mem->write_byte(i, 0);
        }
        //std::cout << "Initial RAM values:" << std::endl;
        for (const auto& ramEntry : el["initial"]["ram"]) {
            //std::cout << "Address: " << ramEntry[0] << ", Value: " << ramEntry[1] << std::endl;
            cpu->mem->write_byte(ramEntry[0], ramEntry[1]);
        }


        if (cb) {
            cpu->step();
            cycles_actual = cpu->step();
        }
        else {
            cycles_actual = cpu->step();
        }
        cycles_expected = (int)el["cycles"].size();
        if (cycles_actual != cycles_expected) {
            printf("Expected cycles: %d\nActual cycles: %d\n", cycles_expected, cycles_actual);
            failed = true;
        }

        if (cpu->pc != el["final"]["pc"].get<int>()) {
            printf("Initial PC: %d\nExpected PC: %d\nActual PC: %d\n", el["initial"]["pc"].get<int>(), el["final"]["pc"].get<int>(), cpu->pc);
            failed = true;
        }
        if (cpu->sp != el["final"]["sp"].get<int>()) {
            printf("Initial SP: %d\nExpected SP: %d\nActual SP: %d\n", el["initial"]["sp"].get<int>(), el["final"]["sp"].get<int>(), cpu->sp);
            failed = true;
        }
        if (cpu->reg_a != el["final"]["a"].get<int>()) {
            printf("Initial A: %d\nExpected A: %d\nActual A: %d\n", el["initial"]["a"].get<int>(), el["final"]["a"].get<int>(), cpu->reg_a);
            failed = true;
        }
        if (cpu->reg_b != el["final"]["b"].get<int>()) {
            printf("Initial B: %d\nExpected B: %d\nActual B: %d\n", el["initial"]["b"].get<int>(), el["final"]["b"].get<int>(), cpu->reg_b);
            failed = true;
        }
        if (cpu->reg_c != el["final"]["c"].get<int>()) {
            printf("Initial C: %d\nExpected C: %d\nActual C: %d\n", el["initial"]["c"].get<int>(), el["final"]["c"].get<int>(), cpu->reg_c);
            failed = true;
        }
        if (cpu->reg_d != el["final"]["d"].get<int>()) {
            printf("Initial D: %d\nExpected D: %d\nActual D: %d\n", el["initial"]["d"].get<int>(), el["final"]["d"].get<int>(), cpu->reg_d);
            failed = true;
        }
        if (cpu->reg_e != el["final"]["e"].get<int>()) {
            printf("Initial E: %d\nExpected E: %d\nActual E: %d\n", el["initial"]["e"].get<int>(), el["final"]["e"].get<int>(), cpu->reg_e);
            failed = true;
        }
        if (cpu->reg_f != el["final"]["f"].get<int>()) {
            printf("Initial F: %d\nExpected F: %d\nActual F: %d\n", el["initial"]["f"].get<int>(), el["final"]["f"].get<int>(), cpu->reg_f);
            u8 expected_f = el["final"]["f"].get<u8>();
            printf("Z Flag\nExpected: %d\nActual: %d\n", u8read_bit(Z_FLAG, &expected_f), cpu->read_zero_flag());
            printf("S Flag\nExpected: %d\nActual: %d\n", u8read_bit(S_FLAG, &expected_f), cpu->read_s_flag());
            printf("H Flag\nExpected: %d\nActual: %d\n", u8read_bit(H_FLAG, &expected_f), cpu->read_hc_flag());
            printf("C Flag\nExpected: %d\nActual: %d\n", u8read_bit(C_FLAG, &expected_f), cpu->read_carry_flag());
            failed = true;
        }
        if (cpu->reg_h != el["final"]["h"].get<int>()) {
            printf("Initial H: %d\nExpected H: %d\nActual H: %d\n", el["initial"]["h"].get<int>(), el["final"]["h"].get<int>(), cpu->reg_h);
            failed = true;
        }
        if (cpu->reg_l != el["final"]["l"].get<int>()) {
            printf("Initial L: %d\nExpected L: %d\nActual L: %d\n", el["initial"]["l"].get<int>(), el["final"]["l"].get<int>(), cpu->reg_l);
            failed = true;
        }


        if (cpu->ime != (bool)el["final"]["ime"].get<int>()) {
            printf("Initial IME: %d\nExpected IME: %d\nActual IME: %d\n", el["initial"]["ime"].get<int>(), el["final"]["ime"].get<int>(), cpu->ime);
            failed = true;
        }

        if (failed) {
            std::cout << "Initial\n";
            std::cout << "    PC: " << el["initial"]["pc"].get<int>() << "\n";
            std::cout << "    SP: " << el["initial"]["sp"].get<int>() << "\n";
            std::cout << "    A: " << el["initial"]["a"].get<int>() << "\n";
            std::cout << "    B: " << el["initial"]["b"].get<int>() << "\n";
            std::cout << "    C: " << el["initial"]["c"].get<int>() << "\n";
            std::cout << "    D: " << el["initial"]["d"].get<int>() << "\n";
            std::cout << "    E: " << el["initial"]["e"].get<int>() << "\n";
            std::cout << "    F: " << el["initial"]["f"].get<int>() << "\n";
            std::cout << "    H: " << el["initial"]["h"].get<int>() << "\n";
            std::cout << "    L: " << el["initial"]["l"].get<int>() << "\n";

            //print intial flags
            u8 initial_f = el["initial"]["f"].get<u8>();
            printf("Z Flag initial: %d\n", u8read_bit(Z_FLAG, &initial_f));
            printf("S Flag initial: %d\n", u8read_bit(S_FLAG, &initial_f));
            printf("H Flag initial: %d\n", u8read_bit(H_FLAG, &initial_f));
            printf("C Flag initial: %d\n", u8read_bit(C_FLAG, &initial_f));


            exit(-5);

        }

        /*
        std::cout << "Final\n";
        std::cout << "    PC: " << el["final"]["pc"].get<int>() << "\n";
        std::cout << "    SP: " << el["final"]["sp"].get<int>() << "\n";
        std::cout << "    A: " << el["final"]["a"].get<int>() << "\n";
        std::cout << "    B: " << el["final"]["b"].get<int>() << "\n";
        std::cout << "    C: " << el["final"]["c"].get<int>() << "\n";
        std::cout << "    D: " << el["final"]["d"].get<int>() << "\n";
        std::cout << "    E: " << el["final"]["e"].get<int>() << "\n";
        std::cout << "    F: " << el["final"]["f"].get<int>() << "\n";
        std::cout << "    H: " << el["final"]["h"].get<int>() << "\n";
        std::cout << "    L: " << el["final"]["l"].get<int>() << "\n";
        */
        //std::cout << "Final RAM values:" << std::endl;
        for (const auto& ramEntry : el["final"]["ram"]) {
            //std::cout << "Address: " << ramEntry[0] << ", Value: " << ramEntry[1] << std::endl;
            u8 fetched_val = cpu->mem->read_byte(ramEntry[0]);
            if (fetched_val != ramEntry[1]) {
                std::cout << "Mismatch at address: " << ramEntry[0] << "\nExpected: " << ramEntry[1] << "\nActual: " << fetched_val << "\n";
                failed = true;
                exit(-5);
            }
        }

        printf("Test %d passed\n", i);
        i++;
    }
    f.close();
    return;
}

void test_all_json(Cpu* cpu) {
    //test all base instructions

    for (int i = 0xFB; i < 256; i++) {
        printf("%02x\n", i);
        if (i == 0x10 || i == 0x76) //skip halt and stop for now
            continue;
        test_json_individual(cpu, i, false);
    }

    //test all cb instruction
    for (int i = 0; i < 256; i++) {
        printf("%02x\n", i);
        test_json_individual(cpu, i, true);
    }

    std::cout << "all tests passed :)\n";

}

void gameloop(Gameboy* gb, bool debug) {
    while (true) {
        u8 cycles = gb->cpu->step();
        gb->timer->tick(cycles);
        if (debug)
		    std::cout << "PC: " << gb->cpu->pc << std::endl;
    }
}

void run_blargg_test(std::string filepath) {
    cartridge* cart = new cartridge(filepath);
	Mmu* mem = new Mmu(cart, true);
	Cpu* cpu = new Cpu(mem);
    PPU* ppu = new PPU(mem);
    Timer* timer = new Timer(mem);
    Gameboy* gb = new Gameboy(cpu, timer, ppu);
	cpu->debug = true;
    gameloop(gb, false);
	return;
}

int tests() {
    

    
    //std::string filepath = "C:\\Users\\David\\Documents\\CS\\EMU\\tetris.gb";
    //cartridge* cart = new cartridge(filepath);

    //cart->print_header_data();
    //Mmu* mem = new Mmu(cart, false);
    //Cpu* cpu = new Cpu(mem);
    
    
    //std::string filepath = "C:\\Users\\David\\Documents\\CS\\EMU\\gb-test-roms\\cpu_instrs\\source\\02-interrupts.s";
	//run_blargg_test(filepath);

    //test_json_individual(cpu, 0x69, false);
    //test_all_json(cpu);
    /*

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

    */





    return 0;
}




