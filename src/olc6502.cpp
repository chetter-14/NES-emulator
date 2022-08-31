#include "olc6502.h"
#include "Bus.h"


olc6502::olc6502()
{
	typedef olc6502 t;
	lookup =
	{
		{ "BRK", &t::BRK, &t::IMM, 7 },{ "ORA", &t::ORA, &t::IZX, 6 },{ "???", &t::XXX, &t::IMP, 2 },{ "???", &t::XXX, &t::IMP, 2 },{ "???", &t::XXX, &t::IMP, 2 },{ "ORA", &t::ORA, &t::ZP0, 3 },{ "ASL", &t::ASL, &t::ZP0, 5 },{ "???", &t::XXX, &t::IMP, 5 },{ "PHP", &t::PHP, &t::IMP, 3 },{ "ORA", &t::ORA, &t::IMM, 2 },{ "ASL", &t::ASL, &t::IMP, 2 },{ "???", &t::XXX, &t::IMP, 2 },{ "???", &t::NOP, &t::IMP, 4 },{ "ORA", &t::ORA, &t::ABS, 4 },{ "ASL", &t::ASL, &t::ABS, 6 },{ "???", &t::XXX, &t::IMP, 6 },
		{ "BPL", &t::BPL, &t::REL, 2 },{ "ORA", &t::ORA, &t::IZY, 5 },{ "???", &t::XXX, &t::IMP, 2 },{ "???", &t::XXX, &t::IMP, 8 },{ "???", &t::NOP, &t::IMP, 4 },{ "ORA", &t::ORA, &t::ZPX, 4 },{ "ASL", &t::ASL, &t::ZPX, 6 },{ "???", &t::XXX, &t::IMP, 6 },{ "CLC", &t::CLC, &t::IMP, 2 },{ "ORA", &t::ORA, &t::ABY, 4 },{ "???", &t::NOP, &t::IMP, 2 },{ "???", &t::XXX, &t::IMP, 7 },{ "???", &t::NOP, &t::IMP, 4 },{ "ORA", &t::ORA, &t::ABX, 4 },{ "ASL", &t::ASL, &t::ABX, 7 },{ "???", &t::XXX, &t::IMP, 7 },
	};
}

olc6502::~olc6502()
{
}

uint8_t olc6502::read(uint16_t a)
{
	return bus->read(a, false);
}

void olc6502::write(uint16_t a, uint8_t d)
{
	bus->write(a, d);
}