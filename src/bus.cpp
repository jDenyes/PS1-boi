#include "bus.h"
#include <iostream>

BUS::BUS() {
	std::cout << "Initializing BUS" << std::endl;
	m_bios = new BIOS;
}

uint32_t BUS::load32(uint32_t address) {
	uint32_t offset = m_bios->m_range.local_address_offset(address);
	
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
