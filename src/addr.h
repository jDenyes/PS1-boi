#pragma once
#include <stdint.h>

class ADDR_RANGE {
public:
	ADDR_RANGE(uint32_t s, uint32_t size);
	uint32_t start, end;
	uint32_t length;
	bool is_addressable(uint32_t address);
	uint32_t local_address_offset(uint32_t address);
};