#pragma once

#include <stdint.h>
#include "bus.h"

#define RESET_PC_VAL 0xbfc00000

class INSTRUCTION {
private:
public:
	INSTRUCTION();
	INSTRUCTION(uint32_t inst);

	// alu / mem operations
	uint32_t get_op();
	uint32_t get_t();
	uint32_t get_i();
	uint32_t get_se_i();
	uint32_t get_s();

	// 0-op
	uint32_t get_0_op();
	uint32_t get_d();
	uint32_t get_shift_i();

	// jmp
	uint32_t get_j_address();

	uint32_t m_inst;
	// uint32_t m_opcode;
	// uint32_t m_t;
	// uint32_t m_immediate;
};

class CPU {
private:
	void reset_pc();
	void decode_and_execute(INSTRUCTION inst);
	uint32_t load32(uint32_t address);
	
	void print_regs();
	
	uint32_t r_pc;
	uint32_t regs[32];

	// Cop0 register 12
	uint32_t status_register;

	INSTRUCTION next_inst;

	// CPU Operations

	void op_j(INSTRUCTION inst);
	void op_addiu(INSTRUCTION inst);
	void op_ori(INSTRUCTION inst);
	void op_lui(INSTRUCTION inst);
	void op_or(INSTRUCTION inst);
	void op_sw(INSTRUCTION inst);
	void op_cop0(INSTRUCTION inst);

	// Op Code 0
	void op_sll(INSTRUCTION inst);

	// COP_0 Op
	void op_cop_mtc0(INSTRUCTION inst);
	
public:
	CPU();

	void fetch_next_instruction();
	void print_pc();
	BUS * m_bus;
};
