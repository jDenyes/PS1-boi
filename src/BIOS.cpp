#include "BIOS.h"
#include <fstream>
#include <iostream>

BIOS::BIOS() : BIOS("../bin/SCPH1001.BIN") {
	// default constructor 
	// std::cout << "default construtor invoked" << std::endl;
}

BIOS::BIOS(const std::string &path) : m_range(0xbfc00000, BIOS_SIZE) {
	std::cout << "Initializing BIOS at start address: 0x" 
		<< std::hex << m_range.start << std::endl;

	// load in BIOS image from file
	std::ifstream file(path, std::ios::binary | std::ios::ate); 
	std::streamsize image_size{0};

	if (file.is_open()) {
		image_size = file.tellg();
	} 
	
	if (image_size == BIOS_SIZE) {
		file.seekg(0, std::ios::beg);
		std::vector<char> buffer(image_size);
		
		if (file.read(buffer.data(), BIOS_SIZE)) {
			m_bios_image = buffer;
			std::cout << "Bios Image Size: 0x" << std::hex << m_bios_image.size() << std::endl;
		}
	}
}

// load 32-bit value from BIOS Image
uint32_t BIOS::load32(uint32_t offset) {
	uint32_t ld_val{0};
	// std::cout << "Bios Image at offset: 0x" << std::hex << offset << std::endl;
	for (uint32_t i = 0; i < sizeof(uint32_t) / sizeof(char); i++) {
		// std::cout << "\t" << std::hex << ((int)m_bios_image[offset + i] & 0xFF) << std::endl;
		ld_val |= (m_bios_image[offset + i] & 0xFF) << (i * 8);
	}
	std::cout << "load32 val: 0x" << std::hex << ld_val << std::endl;
	return ld_val;
}
