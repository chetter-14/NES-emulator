#include "olc6502.h"
#include "Bus.h"


olc6502::olc6502()
{
	typedef olc6502 t;
	lookup =
	{
		{ "BRK", &t::BRK, &t::IMM, 7 },{ "ORA", &t::ORA, &t::IZX, 6 },{ "???", &t::XXX, &t::IMP, 2 },{ "???", &t::XXX, &t::IMP, 2 },{ "???", &t::XXX, &t::IMP, 2 },{ "ORA", &t::ORA, &t::ZP0, 3 },{ "ASL", &t::ASL, &t::ZP0, 5 },{ "???", &t::XXX, &t::IMP, 5 },{ "PHP", &t::PHP, &t::IMP, 3 },{ "ORA", &t::ORA, &t::IMM, 2 },{ "ASL", &t::ASL, &t::IMP, 2 },{ "???", &t::XXX, &t::IMP, 2 },{ "???", &t::NOP, &t::IMP, 4 },{ "ORA", &t::ORA, &t::ABS, 4 },{ "ASL", &t::ASL, &t::ABS, 6 },{ "???", &t::XXX, &t::IMP, 6 },
		{ "BPL", &t::BPL, &t::REL, 2 },{ "ORA", &t::ORA, &t::IZY, 5 },{ "???", &t::XXX, &t::IMP, 2 },{ "???", &t::XXX, &t::IMP, 8 },{ "???", &t::NOP, &t::IMP, 4 },{ "ORA", &t::ORA, &t::ZPX, 4 },{ "ASL", &t::ASL, &t::ZPX, 6 },{ "???", &t::XXX, &t::IMP, 6 },{ "CLC", &t::CLC, &t::IMP, 2 },{ "ORA", &t::ORA, &t::ABY, 4 },{ "???", &t::NOP, &t::IMP, 2 },{ "???", &t::XXX, &t::IMP, 7 },{ "???", &t::NOP, &t::IMP, 4 },{ "ORA", &t::ORA, &t::ABX, 4 },{ "ASL", &t::ASL, &t::ABX, 7 },{ "???", &t::XXX, &t::IMP, 7 },
		{ "JSR", &t::JSR, &t::ABS, 6 },{ "AND", &t::AND, &t::IZX, 6 },{ "???", &t::XXX, &t::IMP, 2 },{ "???", &t::XXX, &t::IMP, 8 },{ "BIT", &t::BIT, &t::ZP0, 3 },{ "AND", &t::AND, &t::ZP0, 3 },{ "ROL", &t::ROL, &t::ZP0, 5 },{ "???", &t::XXX, &t::IMP, 5 },{ "PLP", &t::PLP, &t::IMP, 4 },{ "AND", &t::AND, &t::IMM, 2 },{ "ROL", &t::ROL, &t::IMP, 2 },{ "???", &t::XXX, &t::IMP, 2 },{ "BIT", &t::BIT, &t::ABS, 4 },{ "AND", &t::AND, &t::ABS, 4 },{ "ROL", &t::ROL, &t::ABS, 6 },{ "???", &t::XXX, &t::IMP, 6 },
		{ "BMI", &t::BMI, &t::REL, 2 },{ "AND", &t::AND, &t::IZY, 5 },{ "???", &t::XXX, &t::IMP, 2 },{ "???", &t::XXX, &t::IMP, 8 },{ "???", &t::NOP, &t::IMP, 4 },{ "AND", &t::AND, &t::ZPX, 4 },{ "ROL", &t::ROL, &t::ZPX, 6 },{ "???", &t::XXX, &t::IMP, 6 },{ "SEC", &t::SEC, &t::IMP, 2 },{ "AND", &t::AND, &t::ABY, 4 },{ "???", &t::NOP, &t::IMP, 2 },{ "???", &t::XXX, &t::IMP, 7 },{ "???", &t::NOP, &t::IMP, 4 },{ "AND", &t::AND, &t::ABX, 4 },{ "ROL", &t::ROL, &t::ABX, 7 },{ "???", &t::XXX, &t::IMP, 7 },
		{ "RTI", &t::RTI, &t::IMP, 6 },{ "EOR", &t::EOR, &t::IZX, 6 },{ "???", &t::XXX, &t::IMP, 2 },{ "???", &t::XXX, &t::IMP, 8 },{ "???", &t::NOP, &t::IMP, 3 },{ "EOR", &t::EOR, &t::ZP0, 3 },{ "LSR", &t::LSR, &t::ZP0, 5 },{ "???", &t::XXX, &t::IMP, 5 },{ "PHA", &t::PHA, &t::IMP, 3 },{ "EOR", &t::EOR, &t::IMM, 2 },{ "LSR", &t::LSR, &t::IMP, 2 },{ "???", &t::XXX, &t::IMP, 2 },{ "JMP", &t::JMP, &t::ABS, 3 },{ "EOR", &t::EOR, &t::ABS, 4 },{ "LSR", &t::LSR, &t::ABS, 6 },{ "???", &t::XXX, &t::IMP, 6 },
		{ "BVC", &t::BVC, &t::REL, 2 },{ "EOR", &t::EOR, &t::IZY, 5 },{ "???", &t::XXX, &t::IMP, 2 },{ "???", &t::XXX, &t::IMP, 8 },{ "???", &t::NOP, &t::IMP, 4 },{ "EOR", &t::EOR, &t::ZPX, 4 },{ "LSR", &t::LSR, &t::ZPX, 6 },{ "???", &t::XXX, &t::IMP, 6 },{ "CLI", &t::CLI, &t::IMP, 2 },{ "EOR", &t::EOR, &t::ABY, 4 },{ "???", &t::NOP, &t::IMP, 2 },{ "???", &t::XXX, &t::IMP, 7 },{ "???", &t::NOP, &t::IMP, 4 },{ "EOR", &t::EOR, &t::ABX, 4 },{ "LSR", &t::LSR, &t::ABX, 7 },{ "???", &t::XXX, &t::IMP, 7 },
		{ "RTS", &t::RTS, &t::IMP, 6 },{ "ADC", &t::ADC, &t::IZX, 6 },{ "???", &t::XXX, &t::IMP, 2 },{ "???", &t::XXX, &t::IMP, 8 },{ "???", &t::NOP, &t::IMP, 3 },{ "ADC", &t::ADC, &t::ZP0, 3 },{ "ROR", &t::ROR, &t::ZP0, 5 },{ "???", &t::XXX, &t::IMP, 5 },{ "PLA", &t::PLA, &t::IMP, 4 },{ "ADC", &t::ADC, &t::IMM, 2 },{ "ROR", &t::ROR, &t::IMP, 2 },{ "???", &t::XXX, &t::IMP, 2 },{ "JMP", &t::JMP, &t::IND, 5 },{ "ADC", &t::ADC, &t::ABS, 4 },{ "ROR", &t::ROR, &t::ABS, 6 },{ "???", &t::XXX, &t::IMP, 6 },
		{ "BVS", &t::BVS, &t::REL, 2 },{ "ADC", &t::ADC, &t::IZY, 5 },{ "???", &t::XXX, &t::IMP, 2 },{ "???", &t::XXX, &t::IMP, 8 },{ "???", &t::NOP, &t::IMP, 4 },{ "ADC", &t::ADC, &t::ZPX, 4 },{ "ROR", &t::ROR, &t::ZPX, 6 },{ "???", &t::XXX, &t::IMP, 6 },{ "SEI", &t::SEI, &t::IMP, 2 },{ "ADC", &t::ADC, &t::ABY, 4 },{ "???", &t::NOP, &t::IMP, 2 },{ "???", &t::XXX, &t::IMP, 7 },{ "???", &t::NOP, &t::IMP, 4 },{ "ADC", &t::ADC, &t::ABX, 4 },{ "ROR", &t::ROR, &t::ABX, 7 },{ "???", &t::XXX, &t::IMP, 7 },
		{ "???", &t::NOP, &t::IMP, 2 },{ "STA", &t::STA, &t::IZX, 6 },{ "???", &t::NOP, &t::IMP, 2 },{ "???", &t::XXX, &t::IMP, 6 },{ "STY", &t::STY, &t::ZP0, 3 },{ "STA", &t::STA, &t::ZP0, 3 },{ "STX", &t::STX, &t::ZP0, 3 },{ "???", &t::XXX, &t::IMP, 3 },{ "DEY", &t::DEY, &t::IMP, 2 },{ "???", &t::NOP, &t::IMP, 2 },{ "TXA", &t::TXA, &t::IMP, 2 },{ "???", &t::XXX, &t::IMP, 2 },{ "STY", &t::STY, &t::ABS, 4 },{ "STA", &t::STA, &t::ABS, 4 },{ "STX", &t::STX, &t::ABS, 4 },{ "???", &t::XXX, &t::IMP, 4 },
		{ "BCC", &t::BCC, &t::REL, 2 },{ "STA", &t::STA, &t::IZY, 6 },{ "???", &t::XXX, &t::IMP, 2 },{ "???", &t::XXX, &t::IMP, 6 },{ "STY", &t::STY, &t::ZPX, 4 },{ "STA", &t::STA, &t::ZPX, 4 },{ "STX", &t::STX, &t::ZPY, 4 },{ "???", &t::XXX, &t::IMP, 4 },{ "TYA", &t::TYA, &t::IMP, 2 },{ "STA", &t::STA, &t::ABY, 5 },{ "TXS", &t::TXS, &t::IMP, 2 },{ "???", &t::XXX, &t::IMP, 5 },{ "???", &t::NOP, &t::IMP, 5 },{ "STA", &t::STA, &t::ABX, 5 },{ "???", &t::XXX, &t::IMP, 5 },{ "???", &t::XXX, &t::IMP, 5 },
		{ "LDY", &t::LDY, &t::IMM, 2 },{ "LDA", &t::LDA, &t::IZX, 6 },{ "LDX", &t::LDX, &t::IMM, 2 },{ "???", &t::XXX, &t::IMP, 6 },{ "LDY", &t::LDY, &t::ZP0, 3 },{ "LDA", &t::LDA, &t::ZP0, 3 },{ "LDX", &t::LDX, &t::ZP0, 3 },{ "???", &t::XXX, &t::IMP, 3 },{ "TAY", &t::TAY, &t::IMP, 2 },{ "LDA", &t::LDA, &t::IMM, 2 },{ "TAX", &t::TAX, &t::IMP, 2 },{ "???", &t::XXX, &t::IMP, 2 },{ "LDY", &t::LDY, &t::ABS, 4 },{ "LDA", &t::LDA, &t::ABS, 4 },{ "LDX", &t::LDX, &t::ABS, 4 },{ "???", &t::XXX, &t::IMP, 4 },
		{ "BCS", &t::BCS, &t::REL, 2 },{ "LDA", &t::LDA, &t::IZY, 5 },{ "???", &t::XXX, &t::IMP, 2 },{ "???", &t::XXX, &t::IMP, 5 },{ "LDY", &t::LDY, &t::ZPX, 4 },{ "LDA", &t::LDA, &t::ZPX, 4 },{ "LDX", &t::LDX, &t::ZPY, 4 },{ "???", &t::XXX, &t::IMP, 4 },{ "CLV", &t::CLV, &t::IMP, 2 },{ "LDA", &t::LDA, &t::ABY, 4 },{ "TSX", &t::TSX, &t::IMP, 2 },{ "???", &t::XXX, &t::IMP, 4 },{ "LDY", &t::LDY, &t::ABX, 4 },{ "LDA", &t::LDA, &t::ABX, 4 },{ "LDX", &t::LDX, &t::ABY, 4 },{ "???", &t::XXX, &t::IMP, 4 },
		{ "CPY", &t::CPY, &t::IMM, 2 },{ "CMP", &t::CMP, &t::IZX, 6 },{ "???", &t::NOP, &t::IMP, 2 },{ "???", &t::XXX, &t::IMP, 8 },{ "CPY", &t::CPY, &t::ZP0, 3 },{ "CMP", &t::CMP, &t::ZP0, 3 },{ "DEC", &t::DEC, &t::ZP0, 5 },{ "???", &t::XXX, &t::IMP, 5 },{ "INY", &t::INY, &t::IMP, 2 },{ "CMP", &t::CMP, &t::IMM, 2 },{ "DEX", &t::DEX, &t::IMP, 2 },{ "???", &t::XXX, &t::IMP, 2 },{ "CPY", &t::CPY, &t::ABS, 4 },{ "CMP", &t::CMP, &t::ABS, 4 },{ "DEC", &t::DEC, &t::ABS, 6 },{ "???", &t::XXX, &t::IMP, 6 },
		{ "BNE", &t::BNE, &t::REL, 2 },{ "CMP", &t::CMP, &t::IZY, 5 },{ "???", &t::XXX, &t::IMP, 2 },{ "???", &t::XXX, &t::IMP, 8 },{ "???", &t::NOP, &t::IMP, 4 },{ "CMP", &t::CMP, &t::ZPX, 4 },{ "DEC", &t::DEC, &t::ZPX, 6 },{ "???", &t::XXX, &t::IMP, 6 },{ "CLD", &t::CLD, &t::IMP, 2 },{ "CMP", &t::CMP, &t::ABY, 4 },{ "NOP", &t::NOP, &t::IMP, 2 },{ "???", &t::XXX, &t::IMP, 7 },{ "???", &t::NOP, &t::IMP, 4 },{ "CMP", &t::CMP, &t::ABX, 4 },{ "DEC", &t::DEC, &t::ABX, 7 },{ "???", &t::XXX, &t::IMP, 7 },
		{ "CPX", &t::CPX, &t::IMM, 2 },{ "SBC", &t::SBC, &t::IZX, 6 },{ "???", &t::NOP, &t::IMP, 2 },{ "???", &t::XXX, &t::IMP, 8 },{ "CPX", &t::CPX, &t::ZP0, 3 },{ "SBC", &t::SBC, &t::ZP0, 3 },{ "INC", &t::INC, &t::ZP0, 5 },{ "???", &t::XXX, &t::IMP, 5 },{ "INX", &t::INX, &t::IMP, 2 },{ "SBC", &t::SBC, &t::IMM, 2 },{ "NOP", &t::NOP, &t::IMP, 2 },{ "???", &t::SBC, &t::IMP, 2 },{ "CPX", &t::CPX, &t::ABS, 4 },{ "SBC", &t::SBC, &t::ABS, 4 },{ "INC", &t::INC, &t::ABS, 6 },{ "???", &t::XXX, &t::IMP, 6 },
		{ "BEQ", &t::BEQ, &t::REL, 2 },{ "SBC", &t::SBC, &t::IZY, 5 },{ "???", &t::XXX, &t::IMP, 2 },{ "???", &t::XXX, &t::IMP, 8 },{ "???", &t::NOP, &t::IMP, 4 },{ "SBC", &t::SBC, &t::ZPX, 4 },{ "INC", &t::INC, &t::ZPX, 6 },{ "???", &t::XXX, &t::IMP, 6 },{ "SED", &t::SED, &t::IMP, 2 },{ "SBC", &t::SBC, &t::ABY, 4 },{ "NOP", &t::NOP, &t::IMP, 2 },{ "???", &t::XXX, &t::IMP, 7 },{ "???", &t::NOP, &t::IMP, 4 },{ "SBC", &t::SBC, &t::ABX, 4 },{ "INC", &t::INC, &t::ABX, 7 },{ "???", &t::XXX, &t::IMP, 7 }
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

void olc6502::clock()
{
	if (cycles == 0)
	{

	}
}