#include "addr.h"
#include "bus.h"
#include <cstring>

#include <iostream>

MEM_SPACE::MEM_SPACE(const std::string &name, uint32_t s, uint32_t size, BUS * bus) : ar(s, size) {
	std::cout << "initializing mem space: " << name << " at address 0x" << std::hex << s << " with size 0x" << std::hex << size << "\n";
	m_name = name;
	data = new char[size];
	m_bus = bus;
	m_bus->mem_map.insert(this);
	// std::cout << "memory size: 0x" << std::hex << strlen(data) << std::endl;
}

uint32_t MEM_SPACE::load32(uint32_t address) {
	if (ar.is_addressable(address)) {
		uint32_t offset = ar.local_address_offset(address);
		std::cout << "address offset is in " << m_name << " is 0x" << std::hex << offset << std::endl;

		uint32_t ld_val{0};
		for (uint32_t i = 0; i < sizeof(uint32_t) / sizeof(char); i++) {
			// std::cout << "\t" << std::hex << ((int)data[offset + i] & 0xFF) << std::endl;
			ld_val |= (data[offset + i] & 0xFF) << (i * 8);
		}
		std::cout << "reading data 0x" << std::hex << ld_val << " from address 0x" << std::hex << address << std::endl;
		return ld_val;
	} else {
		std::cout << "model " << m_name << "is not addressable with address " << std::hex << address << std::endl;
		exit(-1);
	}
}

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
	// if (is_addressable(address)) {
		// std::cout << "address offset is 0x" << std::hex << address - start << std::endl;
		return address - start;
	// } else {
		// return 0xFFFFFFFF;
	// }
}

