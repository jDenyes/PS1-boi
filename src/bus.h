#pragma once

#include "BIOS.h"
#include <set>
#include "addr.h"

#define MEMORY_CONTROLLER_SIZE 0x24
#define MEMORY_CONTROLLER_START_ADDRESS	0x1F801000

#define RAM_CTRL_START_ADDRESS 0x1F801060
#define CACHE_CTRL_START_ADDRESS 0xFFFE0130

#define DWORD_SIZE 0x4

class BUS {
public:
	BUS();
	uint32_t load32(uint32_t address);
	void store32(uint32_t address, uint32_t value);
	BIOS * m_bios;
	MEM_SPACE * mem_control;
	MEM_SPACE * ram_control;
	MEM_SPACE * cache_control;
	std::set<MEM_SPACE> mem_map;
};

