#pragma once

#include <string>

#include "addr.h"

// 512 KB Bios Image
#define BIOS_SIZE 0x80000
#define BIOS_START_ADDRESS 0xBFC00000

class BUS;
// class MEM_SPACE;

class BIOS : public MEM_SPACE {
public:
	BIOS(BUS * bus);
	BIOS(const std::string &path, BUS * bus);
	// uint32_t load32(uint32_t offset);
};