#pragma once
#include <cstdint>
#include <array>
#include "olc6502.h"


class Bus 
{
public:
	// Devices on bus
	olc6502 cpu;
	std::array<uint8_t, 64 * 1024> ram;

	Bus();
	~Bus();

	// Bus read & write
	void write(uint16_t addr, uint8_t data);
	uint8_t read(uint16_t addr, bool readOnly = false);
};