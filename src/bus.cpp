#include "BIOS.h"
#include "bus.h"
#include "addr.h"

#include <iostream>
#include <iterator>

bool is_address_word_aligned(uint32_t address);

BUS::BUS() {
	std::cout << "Initializing BUS\n" << std::endl;

	m_bios 				= new BIOS(this);
	mem_control 	= new MEM_CONTROLLER(this);
	// mem_control 	= new MEM_SPACE("MEM_CONTROLLER"	, MEMORY_CONTROLLER_START_ADDRESS	, MEMORY_CONTROLLER_SIZE, this);
	ram_control 	= new MEM_SPACE("RAM_CONTROLLER"		, RAM_CTRL_START_ADDRESS		, DWORD_SIZE	, this);
	cache_control = new MEM_SPACE("CACHE_CONTROLLER"	, CACHE_CTRL_START_ADDRESS	, DWORD_SIZE	, this);

	std::cout << "\nBUS Initialization complete" << std::endl;
}

uint32_t BUS::load32(uint32_t address) {
	uint32_t ld_val{0};

	// ensure address is word aligned
	if (!is_address_word_aligned(address)) {
		std::cout << "address 0x" << std::hex << address << " is not word aligned" << std::endl;
		exit(-1);
	}

	// loop through address mem spaces to determine which address space to write to
	bool address_space_found{false};
	std::set<MEM_SPACE *>::iterator m_iter;
	for (m_iter = mem_map.begin(); m_iter != mem_map.end(); m_iter ++) {
		MEM_SPACE * memory_space = *m_iter;
		if (memory_space->ar.is_addressable(address)) {
			ld_val = memory_space->load32(address);
			address_space_found = true;
			break;
		}
	}

	// error handling if address space does not exist
	if (address_space_found != true) {
		std::cerr << "address out of range" << std::endl;
		std::cout << "BUS unable to handle address 0x: " << std::hex << address << std::endl;
		// std::cout << "BUS Address Range: 0x" << m_bios->ar.start << " - 0x" << m_bios->ar.end << std::endl;

		// enter some error handling
		// exit(-1);
		return 0;
	} else {
		return ld_val;
	}
}

void BUS::store32(uint32_t address, uint32_t value) {
	if (!is_address_word_aligned(address)) {
		std::cout << "address 0x" << std::hex << address << " is not word aligned" << std::endl;
		exit(-1);
	}

	// loop through address mem spaces to determine which address space to write to
	bool address_space_found{false};
	std::set<MEM_SPACE *>::iterator m_iter;
	for (m_iter = mem_map.begin(); m_iter != mem_map.end(); m_iter ++) {
		MEM_SPACE * memory_space = *m_iter;
		if (memory_space->ar.is_addressable(address)) {
			std::cout << "writing model: " << memory_space->m_name << " at address 0x" << std::hex << address << std::endl;
			memory_space->store32(address, value);
			address_space_found = true;
			break;
		}
	}

	// error handling if address space does not exist
	if (address_space_found != true) {
		std::cerr << "address out of range" << std::endl;
		std::cout << "BUS unable to handle address 0x: " << std::hex << address << std::endl;
		// std::cout << "BIOS Address Range: 0x" << m_bios->ar.start << " - 0x" << m_bios->ar.end << std::endl;

		// enter some error handling
		// exit(-1);
		// return 0;
	} 

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

bool is_address_word_aligned(uint32_t address) {
	return (address % 4 == 0);
}