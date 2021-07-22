#include "bus.h"
#include <iostream>

BUS::BUS() { // : mem_control(0x1f801000, 36), ram(0x1f801060, 4), cache_control(0xfffe0130, 4) {
	m_bios 			= new BIOS(this);
	mem_control 	= new MEM_SPACE(MEMORY_CONTROLLER_START_ADDRESS	, MEMORY_CONTROLLER_SIZE, this);
	ram_control 	= new MEM_SPACE(RAM_CTRL_START_ADDRESS			, DWORD_SIZE, this);
	cache_control 	= new MEM_SPACE(CACHE_CTRL_START_ADDRESS		, DWORD_SIZE, this);


	// BIOS * mem_bios = new BIOS;

	// mem_map.insert(&mem_control);
	// mem_map.insert(&ram);
	// mem_map.insert(&cache_control);
	// mem_map.insert(&mem_bios);

	std::cout << "Initializing BUS" << std::endl;
	// m_bios = new BIOS;
}

uint32_t BUS::load32(uint32_t address) {
	uint32_t offset = m_bios->ar.local_address_offset(address);

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
		std::cout << "BIOS Address Range: 0x" << m_bios->ar.start
			<< " - 0x" << m_bios->ar.end << std::endl;
		// enter some error handling
		exit(-1);
		return 0;
	}
}

void BUS::store32(uint32_t address, uint32_t value) {
	// if (address % 4 != 0) {
	// 	std::cout << "address 0x" << std::hex << address << " is not word aligned" << std::endl;
	// 	exit(-1);
	// }

	// uint32_t offset = mem_control.ar.local_address_offset(address);
	
	// if (offset == 0) {
	// 	std::cout << "Writing Expansion 1 base address" << std::endl;
	// 	if (value != 0x1f000000) {
	// 		std::cout << "writing invalid value 0x" << std::hex << value << " to expansion address 1" << std::endl;
	// 		// exit(-1);
	// 	}
	// } else if (offset == 0x4) {
	// 	std::cout << "Writing Expansion 2 base address" << std::endl;
	// 	if (value != 0x1f802000) {
	// 		std::cout << "writing invalid value 0x" << std::hex << value << " to expansion address 2" << std::endl;
	// 		// exit(-1);
	// 	}
	// } else {
	// 	std::cout << "Unhandled memory write to MEM_CONTROL::0x" << std::hex << address << std::endl;
	// 	// exit(-1);
	// }
}