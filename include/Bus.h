#ifndef BUS_H
#define BUS_H

#include <cstdint>
#include <array>
#include "nes_cpu.h"

class Bus
{
public:
	Bus() { }
	~Bus() { }

public:	// Devices on bus
	NES_cpu cpu;

	// RAM of the emulator
	std::array<uint8_t, 64 * 1024> ram;

public:	// Bus read and write
	void write(uint16_t addr, uint8_t data);
	uint8_t read(uint16_t addr, bool bReadOnly = false);
};

#endif