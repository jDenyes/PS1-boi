#pragma once
#include "bios.h"

class BUS {
public:
	BUS();
	uint32_t load32(uint32_t address);
	BIOS * m_bios;
};