#include "addr.h"
#include <iostream>

ADDR_RANGE::ADDR_RANGE(uint32_t s, uint32_t size) {
	start = s;
	end = size + s;
	length = size;
}

bool ADDR_RANGE::is_addressable(uint32_t address) {
	if (address >= start && address <= end) {
		std::cout << "address is addressable: 0x" << std::hex << address << std::endl;
		return true;
	} 
	std::cout << "address: 0x" << std::hex << address << " not in range: 0x" << std::hex << start << "- 0x" << std::hex << end << std::endl;
	return false;
}

uint32_t ADDR_RANGE::local_address_offset(uint32_t address) {
	if (is_addressable(address)) {
		std::cout << "address offset is 0x" << std::hex << address - start << std::endl;
		return address - start;
	} else {
		return 0xFFFFFFFF;
	}
}