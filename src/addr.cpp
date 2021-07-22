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
}

uint32_t MEM_SPACE::load32(uint32_t address) {
	if (ar.is_addressable(address)) {
		uint32_t offset = ar.local_address_offset(address);
		std::cout << "address offset is in " << m_name << " is 0x" << std::hex << offset << std::endl;

		uint32_t ld_val{0};
		for (uint32_t i = 0; i < sizeof(uint32_t) / sizeof(char); i++) {
			ld_val |= (data[offset + i] & 0xFF) << (i * 8);
		}
		std::cout << "reading data 0x" << std::hex << ld_val << " from address 0x" << std::hex << address << std::endl;
		return ld_val;
	} else {
		std::cout << "model " << m_name << "is not addressable with address " << std::hex << address << std::endl;
		exit(-1);
	}
}

void MEM_SPACE::store32(uint32_t address, uint32_t value) {
	if (!ar.is_addressable(address)) {
		std::cout << "model " << m_name << "is not addressable with address " << std::hex << address << std::endl;
		exit(-1);
	}

	std::cout << "writing 0x" << std::hex << value << " to 0x" << std::hex << address << std::endl;
	std::cout << "original value: ";
	print_address(address);

	uint32_t offset = ar.local_address_offset(address);
	for (uint32_t i = 0; i < sizeof(uint32_t) / sizeof(char); i++) {
		uint32_t bit_mask = 0xFF << (i * 8);
		uint32_t write_val = (value & bit_mask) >> (i * 8);
		data[offset + i] = write_val;
	}
	std::cout << "new value: ";
	print_address(address);
}

// bug where if the value is XY and X is 0 then it will not print X
void MEM_SPACE::print_address(uint32_t address) {
	uint32_t offset = ar.local_address_offset(address);

	std::cout << "0x" << std::hex;
	std::cout << ((int)data[offset + 3] & 0xFF); 
	std::cout << ((int)data[offset + 2] & 0xFF);
	std::cout << ((int)data[offset + 1] & 0xFF);
	std::cout << ((int)data[offset + 0] & 0xFF);
	std::cout << std::endl;
}

MEM_CONTROLLER::MEM_CONTROLLER(BUS * bus) : MEM_SPACE("MEMORY CONTROLLER", MEMORY_CONTROLLER_START_ADDRESS, 
		MEMORY_CONTROLLER_SIZE, bus) {
	std::cout << "Initializing memory controller" << std::endl;
}

void MEM_CONTROLLER::store32(uint32_t address, uint32_t value) {
	std::cout << "storing in memory controller" << std::endl;
	uint32_t offset = ar.local_address_offset(address);
	if (offset == 0) {
		std::cout << "Writing Expansion 1 base address" << std::endl;
		if (value != 0x1f000000) {
			std::cout << "writing invalid value 0x" << std::hex << value << " to expansion address 1" << std::endl;
			exit(-1);
		}
	} else if (offset == 0x4) {
		std::cout << "Writing Expansion 2 base address" << std::endl;
		if (value != 0x1f802000) {
			std::cout << "writing invalid value 0x" << std::hex << value << " to expansion address 2" << std::endl;
			exit(-1);
		}
	} else {
		std::cout << "Unhandled memory write to MEM_CONTROL::0x" << std::hex << address << std::endl;
		return;
	}
	MEM_SPACE::store32(address, value);	
}

ADDR_RANGE::ADDR_RANGE(uint32_t s, uint32_t size) {
	start = s;
	end = size + s;
	length = size;
}

bool ADDR_RANGE::is_addressable(uint32_t address) {
	if (address >= start && address <= end) {
		return true;
	} 
	return false;
}

uint32_t ADDR_RANGE::local_address_offset(uint32_t address) {
	return address - start;
}

