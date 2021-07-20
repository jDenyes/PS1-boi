#pragma once
#include <string>
#include <vector>
#include "addr.h"

// 512 KB Bios Image
static const uint32_t SIZE = 512 * 1024;

class BIOS {
public:
	BIOS();
	BIOS(const std::string &path);

	uint32_t load32(uint32_t offset);

	const uint64_t BIOS_SIZE = SIZE;
	std::vector<char> m_bios_image;
	ADDR_RANGE m_range;
};