#pragma once

#ifndef ADDR_H
#define ADDR_H

#include <stdint.h>
#include "bus.h"

class BUS;

class ADDR_RANGE {
public:
	ADDR_RANGE(uint32_t s, uint32_t size);
	uint32_t start, end;
	uint32_t length;
	bool is_addressable(uint32_t address);
	uint32_t local_address_offset(uint32_t address);
};

class MEM_SPACE {
public:
	MEM_SPACE(uint32_t s, uint32_t size, BUS * m_bus);
	ADDR_RANGE ar;
	char *data;
	BUS * m_bus;
};

#endif
