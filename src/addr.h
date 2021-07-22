#pragma once

#include <stdint.h>
#include <string>

class BUS;

class ADDR_RANGE {
public:
	ADDR_RANGE(uint32_t s, uint32_t size);
	
	bool is_addressable(uint32_t address);
	uint32_t local_address_offset(uint32_t address);

	uint32_t start, end, length;
};

class MEM_SPACE {
public:
	MEM_SPACE(const std::string &name, uint32_t s, uint32_t size, BUS * m_bus);

	uint32_t load32(uint32_t address);

	ADDR_RANGE ar;
	char * data;
	BUS * m_bus;
	std::string m_name;
};
