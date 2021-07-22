#include "BIOS.h"
#include "addr.h"
#include "bus.h"

#include <fstream>
#include <iostream>
#include <cstring>

BIOS::BIOS(BUS * bus) : BIOS("../bin/SCPH1001.BIN", bus) {
	// default constructor 
	std::cout << "default construtor invoked" << std::endl;
}

BIOS::BIOS(const std::string &path, BUS * bus) : MEM_SPACE(BIOS_START_ADDRESS, BIOS_SIZE, bus) {
	// std::cout << SIZE << " " << BIOS_SIZE << std::endl;
	std::cout << "Initializing BIOS at start address: 0x" 
		<< std::hex << BIOS_START_ADDRESS << std::endl;

	// load in BIOS image from file
	std::ifstream file(path, std::ios::binary | std::ios::ate); 
	std::streamsize image_size{0};

	if (file.is_open()) {
		std::cout << "opened BIOS file for reading" << std::endl;
		image_size = file.tellg();
	} else {
		std::cout << "failed to open BIOS file for reading" << std::endl;
		exit(-1);
	}
	
	// size_t len = strlen(data);
	// std::cout << "len: " << len << " image_size: " << image_size << std::endl;

	if (image_size == strlen(data)) {
		// std::cout << "seeking beginning of bios file" << std::endl;
		file.seekg(0, std::ios::beg);
		// std::vector<char> buffer(image_size);
		
		if (file.read(data, BIOS_SIZE)) {
			std::cout << "Bios Image Size: 0x" << std::hex << BIOS_SIZE << std::endl;
		} else {
			std::cout << "unable to read bios image to data array" << std::endl;
			exit(-1);
		}
	} else {
		std::cout << "bios and image do not match" << std::endl;
		exit(-1);
	}
}

// load 32-bit value from BIOS Image
uint32_t BIOS::load32(uint32_t offset) {
	// uint32_t ld_val{0};
	// // std::cout << "Bios Image at offset: 0x" << std::hex << offset << std::endl;
	// for (uint32_t i = 0; i < sizeof(uint32_t) / sizeof(char); i++) {
	// 	// std::cout << "\t" << std::hex << ((int)m_bios_image[offset + i] & 0xFF) << std::endl;
	// 	ld_val |= (m_bios_image[offset + i] & 0xFF) << (i * 8);
	// }
	// std::cout << "load32 val: 0x" << std::hex << ld_val << std::endl;
	// return ld_val;
}
