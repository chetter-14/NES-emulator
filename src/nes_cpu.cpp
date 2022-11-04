#include "nes_cpu.h"
#include "Bus.h"


NES_cpu::NES_cpu()
{

}

NES_cpu::~NES_cpu()
{

}

void NES_cpu::write(uint16_t addr, uint8_t data)
{
	bus->write(addr, data);
}

uint8_t NES_cpu::read(uint16_t addr)
{
	return bus->read(addr, false);
}