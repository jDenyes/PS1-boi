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
	virtual void store32(uint32_t address, uint32_t value);
	void print_address(uint32_t address);

	ADDR_RANGE ar;
	char * data;
	BUS * m_bus;
	std::string m_name;
};

#define MEMORY_CONTROLLER_SIZE 0x24
#define MEMORY_CONTROLLER_START_ADDRESS	0x1F801000

class MEM_CONTROLLER : public MEM_SPACE {
public:
	MEM_CONTROLLER(BUS * bus);
	void store32(uint32_t address, uint32_t value);
};