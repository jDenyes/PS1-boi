#pragma once
#include "bios.h"

class BUS {
public:
	BUS();
	uint32_t load32(uint32_t address);
	void store32(uint32_t address, uint32_t value);
	BIOS * m_bios;
	ADDR_RANGE mem_control;
};