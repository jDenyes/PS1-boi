#include "cpu.h"
#include "BIOS.h"
#include "bus.h"
#include <iostream>

int main() {
	CPU cpu;
	uint32_t i{0};
	while (i < 10) {
		cpu.print_pc();
		cpu.fetch_next_instruction();
		i ++;
	}
	// BIOS bios("../bin/SCPH1001.BIN");
	// BUS bus;
	// cpu.load32(0xbfc00000 + 0xFFFFFFFF);
	// cpu.print_pc();
	
	// cpu.m_bus->m_bios->load32(0x1000);
	// bios.load32(0x1000);
	// std::cout << bios.BIOS_SIZE << std::endl;
}