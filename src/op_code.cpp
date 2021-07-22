#include "op_code.h"
// #include "cpu.h"
#include <iostream> 

void CPU::op_lui(INSTRUCTION inst) {
	std::cout << "0x" << std::hex << inst.get_op() << ": load immediate upper inst" << std::endl;
	uint32_t i = inst.get_i();
	uint32_t t = inst.get_t();
	regs[t] = i << 16;
}

void CPU::op_ori(INSTRUCTION inst) {
	std::cout << "0x" << std::hex << inst.get_op() << ": ori immediate inst" << std::endl;
	uint32_t i = inst.get_i();
	uint32_t t = inst.get_t();
	regs[t] |= i;
}

// sw$ target(t), address(i)($src)
void CPU::op_sw(INSTRUCTION inst) {
	std::cout << "0x" << std::hex << inst.get_op() << ": sw inst" << std::endl;
	int32_t i = inst.get_se_i();
	uint32_t t = inst.get_t();
	uint32_t s = inst.get_s();
	m_bus->store32(regs[s] + i, regs[t]);
}

void CPU::op_sll(INSTRUCTION inst) {
	std::cout << "0x" << std::hex << inst.get_0_op() << ": sli inst" << std::endl;
	uint32_t i = inst.get_shift_i();
	uint32_t t = inst.get_t();
	uint32_t d = inst.get_d();
	regs[d] = regs[t] << i;
}

void CPU::op_addiu(INSTRUCTION inst) {
	std::cout << "0x" << std::hex << inst.get_op() << ": addiu inst" << std::endl;
	uint32_t i = inst.get_se_i();
	uint32_t t = inst.get_t();
	uint32_t s = inst.get_s();
	regs[t] = regs[s] + i;
}

void CPU::op_j(INSTRUCTION inst) {
	std::cout << "0x" << std::hex << inst.get_op() << ": jump inst" << std::endl;
	uint32_t j = inst.get_j_address();
	std::cout << "jumping to address " << std::hex << "0x" << j << std::endl;
	r_pc = r_pc & 0xF0000000 | (j << 2);
}


void CPU::op_or(INSTRUCTION inst) {
	std::cout << "0x" << std::hex << inst.get_op() << ": jump inst" << std::endl;
	uint32_t d = inst.get_d();
	uint32_t s = inst.get_s();
	uint32_t t = inst.get_t();
	regs[d] = regs[s] | regs[t];
}


void CPU::op_cop0(INSTRUCTION inst) {
	std::cout << "0x" << std::hex << inst.get_op() << ": op COP_0" << std::endl;
	bool op_code_handled = true;

	uint32_t cop_op = inst.get_s();

	switch (cop_op) {
		case MTC0:
			op_cop_mtc0(inst);
			break;
	default:
		op_code_handled = false;
		std::cout << "0x" << std::hex << cop_op << " opcode not handled" << std::endl;
		exit(-1);
		break;
	}
}
void CPU::op_cop_mtc0(INSTRUCTION inst) {
	std::cout << "0x" << std::hex << inst.get_op() << ": jump inst" << std::endl;

	uint32_t src_reg = inst.get_t();
	uint32_t cop0_r = inst.get_d();

	switch (cop0_r) {
		case 12:
			status_register = regs[src_reg];
			break;
	default:
		std::cout << "ERROR: unhandled COP0 Register write: " << std::dec << cop0_r << std::endl;
		break;
	}


}


