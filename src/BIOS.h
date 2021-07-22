#pragma once
#include <string>
#include <vector>
#include "addr.h"
#include "bus.h"

// 512 KB Bios Image
#define BIOS_SIZE 0x80000
#define BIOS_START_ADDRESS 0xBFC00000

class BIOS : public MEM_SPACE {
public:
	BIOS(BUS * bus);
	BIOS(const std::string &path, BUS * bus);
	uint32_t load32(uint32_t offset);
	// const uint64_t BIOS_SIZE = SIZE;
	// std::vector<char> m_bios_image;
	// ADDR_RANGE m_range;
};