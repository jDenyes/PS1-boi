#include "op_code.h"
// #include "cpu.h"
#include <iostream> 

void CPU::op_lui(INSTRUCTION inst) {
	std::cout << "0x" << std::hex << inst.m_opcode << ": load immediate upper inst" << std::endl;
	regs[inst.m_t] = inst.m_immediate << 16;
}

void CPU::op_ori(INSTRUCTION inst) {
	std::cout << "0x" << std::hex << inst.m_opcode << ": ori immediate inst" << std::endl;
	regs[inst.m_t] |= inst.m_immediate; 
}