#include "cpu.h"
#include "op_code.h"
#include <iostream>

CPU::CPU() {
	std::cout << "Initializing CPU" << std::endl;
	reset_pc();
	print_regs();
	m_bus = new BUS;
	std::cout << "CPU Init complete\n" << std::endl;
}

void CPU::fetch_next_instruction() {
	// uint32_t pc = r_pc;

	// fetch instruction at PC
	std::cout << "fetching instruction from address: 0x" << std::hex << r_pc << std::endl;

	INSTRUCTION inst = next_inst;
	next_inst = INSTRUCTION(load32(r_pc));
	// uint32_t inst = load32(r_pc);
	r_pc += 0x4;
	std::cout << "executing instruction: 0x" << inst.m_inst << std::endl;
	decode_and_execute(inst);
}

uint32_t CPU::load32(uint32_t address) {
	return m_bus->load32(address);
}

void CPU::reset_pc() {
	r_pc = RESET_PC_VAL;
	next_inst = INSTRUCTION(0);

	for (int i = 0; i < 32; i ++) {
		regs[i] = 0xdeadbeef;
	}
	regs[0] = 0;
}

void CPU::decode_and_execute(INSTRUCTION inst) {
	std::cout << "opcode: 0x" << std::hex << inst.get_op() << std::endl; 

	bool op_code_handled = true;
	// INSTRUCTION decoded_inst(inst);

	switch(inst.get_op()) {
		case LUI:
			op_lui(inst);
			break;
		case ORI:
			op_ori(inst);
			break;
		case SW:
			op_sw(inst);
			break;
		case ADDIU:
			op_addiu(inst);
			break;
		case J:
			op_j(inst);
			break;
		case 0:
			switch(inst.get_0_op()) {
				case SLL:
					op_sll(inst);
					break;
			default:
				op_code_handled = false;
				std::cout << "0 : 0x" << std::hex << inst.get_0_op() << " opcode not handled" 
					<< std::endl;
				exit(-1);
				break;
			}
			break;
	default:
		op_code_handled = false;
		std::cout << "0x" << std::hex << inst.get_op() << " opcode not handled" << std::endl;
		exit(-1);
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

INSTRUCTION::INSTRUCTION() : INSTRUCTION(0x0) {
}

INSTRUCTION::INSTRUCTION(uint32_t inst) : m_inst(inst) {
}


// basic arithmetic operations & st / ld operations

// 10 10 28 AC
// AC 28 10 10
// 1010 1100 0010 1000 0001 0000 0001 0000
// op_code = 0x2B
// opcode	| 	s		|	t		|	i						|
// 1010 11	| 	00 001  | 	0 1000	|	0001 0000 0001 0000		|

// b: 31 - 26
uint32_t INSTRUCTION::get_op() {
	return (m_inst >> 26) & 0x3F;
}

// b: 25 - 21
uint32_t INSTRUCTION::get_s() {
	return (m_inst >> 21) & 0x1F;
}

// b: 20 - 16
uint32_t INSTRUCTION::get_t() {
	return (m_inst >> 16) & 0x1F; 
}

// b: 15 - 0
uint32_t INSTRUCTION::get_i() {
	return m_inst & 0xFFFF; 
}

// c-style casts automatically sign extend
// b: 15 - 0
uint32_t INSTRUCTION::get_se_i() {
	return (int32_t) (m_inst & 0xFFFF); 
}

// shift operations, 0x0 opcode

//		|	b[31:26]	|	b[25:16]	|	b[15:11]		|	b[10:6]			|	b[5:0]		|
// 		|	opcode		| 				|	register index	|	shift immediate	|	0 op code	|
// sll	|	0000 00		| 	00 001  	| 	0 1000			|	001 00			|	0 0000		|


// b: 15 - 11
uint32_t INSTRUCTION::get_d() {
	return (m_inst >> 11) & 0x01F; 
}

// b: 10 - 6
uint32_t INSTRUCTION::get_shift_i() {
	return (m_inst >> 6) & 0x01F;  
}

// b: 5 - 0
uint32_t INSTRUCTION::get_0_op() {
	return (m_inst & 0x03F);  
}

// jump operations 0x2 opcode

// 0bf00054
// 0000 1011 1111 0000 0000 0000 0101 0100
// 0000 10 	| 1111
// 0x2		|
// b[31:26]	| b[25:0]
// opcode	| address

uint32_t INSTRUCTION::get_j_address() {
	return m_inst & 0x3FFFFFF;  
}
