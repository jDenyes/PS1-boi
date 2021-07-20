#pragma once

#include <stdint.h>
#include "bus.h"

#define RESET_PC_VAL 0xbfc00000

class INSTRUCTION {
private:
	uint32_t inst_get_op_code_bits();
	uint32_t inst_get_t_bits();
	uint32_t inst_get_immediate_bits();
public:
	INSTRUCTION(uint32_t inst);
	uint32_t m_inst;
	uint32_t m_opcode;
	uint32_t m_t;
	uint32_t m_immediate;
};

class CPU {
private:
	void reset_pc();
	void decode_and_execute(uint32_t inst);
	uint32_t load32(uint32_t address);
	
	void print_regs();
	
	uint32_t r_pc;
	uint32_t regs[32];

	// CPU Operations
	void op_lui(INSTRUCTION inst);
	void op_ori(INSTRUCTION inst);
public:
	CPU();

	void fetch_next_instruction();
	void print_pc();
	BUS * m_bus;
};
