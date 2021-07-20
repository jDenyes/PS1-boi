#include "cpu.h"
#include "op_code.h"
#include <iostream>

CPU::CPU() {
	std::cout << "Initializing CPU" << std::endl;
	reset_pc();
	regs[0] = 0;
	print_regs();
	m_bus = new BUS;
	std::cout << "CPU Init complete\n" << std::endl;
}

void CPU::fetch_next_instruction() {
	// uint32_t pc = r_pc;

	// fetch instruction at PC
	std::cout << "fetching instruction from address: 0x" << std::hex << r_pc << std::endl;
	uint32_t inst = load32(r_pc);
	std::cout << "executing instruction: 0x" << inst << std::endl;
	decode_and_execute(inst);
	r_pc += 0x4;
}

uint32_t CPU::load32(uint32_t address) {
	return m_bus->load32(address);
}

void CPU::reset_pc() {
	r_pc = RESET_PC_VAL;
	for (int i = 0; i < 32; i ++) {
		regs[i] = 0xdeadbeef;
	}
	regs[0] = 0;
}

void CPU::decode_and_execute(uint32_t inst) {
	// do nothing
	// PANICKING
	std::cout << "opcode: 0x" << (inst >> 26) << std::endl; 
	bool op_code_handled = true;
	INSTRUCTION decoded_inst(inst);

	switch(decoded_inst.m_opcode) {
		case LUI:
			op_lui(decoded_inst);
			break;
		case ORI:
			op_ori(decoded_inst);
			break;
		// case SW:
			// op_sw(decoded_inst);
			// break;
	default:
		op_code_handled = false;
		std::cout << "0x" << std::hex << decoded_inst.m_opcode << " opcode not handled" << std::endl;
		break;
	}
	if (op_code_handled) {
		print_regs();
	}
}

void CPU::print_pc() {
	std::cout << "\nCurrent PC: 0x" << std::hex << r_pc << std::endl;
}

void CPU::print_regs() {
	std::cout << "\nPrinting CPU Regs" << std::endl;
	for (uint32_t i = 0; i < 32; i ++) {
		std::cout << "\t" << "r" << std::dec << i << ":\t" << std::hex << "0x" << regs[i] << std::endl;
	}
	std::cout << std::endl;
}

INSTRUCTION::INSTRUCTION(uint32_t inst) {
	m_inst = inst;
	m_opcode = inst_get_op_code_bits();
	m_t = inst_get_t_bits();
	m_immediate = inst_get_immediate_bits();
}

// b: 25 - 31
uint32_t INSTRUCTION::inst_get_op_code_bits() {
	return (m_inst >> 26) & 0x2F;
}

// b: 16 - 20
uint32_t INSTRUCTION::inst_get_t_bits() {
	return (m_inst >> 16) & 0x1F; 
}

// b: 0-15
uint32_t INSTRUCTION::inst_get_immediate_bits() {
	return m_inst & 0xFFFF; 
}
