#include "bus.h"
#include <iostream>

BUS::BUS() : mem_control(0x1f801000, 36)  {
	std::cout << "Initializing BUS" << std::endl;
	m_bios = new BIOS;
	// ADDR_RANGE mem_control();
}

uint32_t BUS::load32(uint32_t address) {
	uint32_t offset = m_bios->m_range.local_address_offset(address);

	if (address % 4 != 0) {
		std::cout << "address 0x" << std::hex << address << " is not word aligned" << std::endl;
		exit(-1);
	}

	if (offset != 0xFFFFFFFF) { //  is it possible for the offset to be 0xFFFFFFF?
		return m_bios->load32(offset);
	} else {
		std::cerr << "address out of range" << std::endl;
		std::cout << "BIOS unable to handle address 0x: " 
			<< std::hex << address << std::endl;
		std::cout << "BIOS Address Range: 0x" << m_bios->m_range.start
			<< " - 0x" << m_bios->m_range.end << std::endl;
		// enter some error handling
		exit(-1);
		return 0;
	}
}

void BUS::store32(uint32_t address, uint32_t value) {
	if (address % 4 != 0) {
		std::cout << "address 0x" << std::hex << address << " is not word aligned" << std::endl;
		exit(-1);
	}

	uint32_t offset = mem_control.local_address_offset(address);
	
	if (offset == 0) {
		std::cout << "Writing Expansion 1 base address" << std::endl;
		if (value != 0x1f000000) {
			std::cout << "writing invalid value 0x" << std::hex << value << " to expansion address 1" << std::endl;
			// exit(-1);
		}
	} else if (offset == 0x4) {
		std::cout << "Writing Expansion 2 base address" << std::endl;
		if (value != 0x1f802000) {
			std::cout << "writing invalid value 0x" << std::hex << value << " to expansion address 2" << std::endl;
			// exit(-1);
		}
	} else {
		std::cout << "Unhandled memory write to MEM_CONTROL::0x" << std::hex << address << std::endl;
		// exit(-1);
	}
}