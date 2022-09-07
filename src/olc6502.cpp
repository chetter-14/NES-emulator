#include "olc6502.h"
#include "Bus.h"


olc6502::olc6502()
{
	typedef olc6502 t;
	// we initialize all the instruction objects with the appropriate names, functions and cycles number
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
	// it's empty
}

// BUS

// read from memory via the bus
uint8_t olc6502::read(uint16_t a)
{
	return bus->read(a, false);
}

// write to memory via the bus
void olc6502::write(uint16_t a, uint8_t d)
{
	bus->write(a, d);
}

// FLAGS

// whether the specified flag is set or not
uint8_t olc6502::getFlag(FLAGS6502 f)
{
	return (status & f) > 0 ? 1 : 0;
}

// bool parameter indicates whether to set (true) or unset (false) the bit (flag)
void olc6502::setFlag(FLAGS6502 f, bool v)
{
	if (v)
		status |= f;
	else
		status &= ~f;
}

// EXTERNAL INPUTS

// execute a clock cycle
void olc6502::clock()
{
	if (cycles == 0)
	{
		opcode = read(pc);
		pc++;

		cycles = lookup[opcode].cycles;

		uint8_t additional_cycle1 = (this->*lookup[opcode].addrmode)();	// call the function of addressing mode
		uint8_t additional_cycle2 = (this->*lookup[opcode].operate)();	// call the function to perform an operation

		cycles += (additional_cycle1 & additional_cycle2);			// why & operand ? 
	}
	cycles--;
}

// resets the cpu: registers, flags, stack pointer, program counter, etc.
void olc6502::reset()
{
	a = 0;
	x = 0;
	y = 0;
	stkp = 0xFD;
	status = 0x00 | U;

	addr_abs = 0xFFFC;
	uint16_t lo = read(addr_abs);
	uint16_t hi = read(addr_abs + 1);

	pc = (hi << 8) | lo;

	addr_rel = 0x0000;
	addr_abs = 0x0000;
	fetched = 0x00;

	cycles = 8;
}

// interrupt request (if 'disable interrupt' flag is set to 0)
// stops the current execution, saves status and program counter on stack, 
// jumps to the other location and begins executing those instructions
void olc6502::irq()
{
	if (getFlag(I) == 0)
	{
		write(0x0100 + stkp, (pc >> 8) & 0x00FF);
		stkp--;
		write(0x0100 + stkp, pc & 0x00FF);
		stkp--;

		setFlag(B, 0);
		setFlag(U, 1);
		setFlag(I, 1);
		write(0x0100 + stkp, status);
		stkp--;

		addr_abs = 0xFFFE;
		uint16_t lo = read(addr_abs);
		uint16_t hi = read(addr_abs + 1);

		pc = (hi << 8) | lo;

		cycles = 7;
	}
}

// non-maskable interrupt
// this interrupt can not be ignored
// the logic is the same as with irq()
void olc6502::nmi()
{
	write(0x0100 + stkp, (pc >> 8) & 0x00FF);
	stkp--;
	write(0x0100 + stkp, pc & 0x00FF);
	stkp--;

	setFlag(B, 0);
	setFlag(U, 1);
	setFlag(I, 1);
	write(0x0100 + stkp, status);
	stkp--;

	addr_abs = 0xFFFA;
	uint16_t lo = read(addr_abs);
	uint16_t hi = read(addr_abs + 1);

	pc = (hi << 8) | lo;

	cycles = 8;
}

// ADDRESSING MODES

// implied 
// the address is implicitly stated in opcode
uint8_t olc6502::IMP()
{
	fetched = a;
	return 0;
}

// immediate
// the second byte of the instruction contains the address
uint8_t olc6502::IMM()
{
	addr_abs = pc++;
	return 0;
}

// zero page
// the second byte is the address on the 0x00__ page
uint8_t olc6502::ZP0()
{
	addr_abs = read(pc);
	pc++;
	addr_abs &= 0x00FF;
	return 0;
}

// indexed zero page (X)
// the second byte value which is added to the X register value 
// no carry occurs, the result is 0x00__ address
uint8_t olc6502::ZPX()
{
	addr_abs = (read(pc) + x);
	pc++;
	addr_abs &= 0x00FF;
	return 0;
}

// indexed zero page (Y)
// the same as ZPX() but with the Y register
uint8_t olc6502::ZPY()
{
	addr_abs = (read(pc) + y);
	pc++;
	addr_abs &= 0x00FF;
	return 0;
}

uint8_t olc6502::ABS()
{
	uint16_t lo = read(pc);
	pc++;
	uint16_t hi = read(pc);
	pc++;

	addr_abs = (hi << 8) | lo;
	return 0;
}

uint8_t olc6502::ABX()
{
	uint16_t lo = read(pc);
	pc++;
	uint16_t hi = read(pc);
	pc++;

	addr_abs = (hi << 8) | lo;
	addr_abs += x;

	if ((addr_abs & 0xFF00) != (hi << 8))	// if addr_abs now on the next page
		return 1;							// we may need an additional clock cycle
	else
		return 0;
}

uint8_t olc6502::ABY()
{
	uint16_t lo = read(pc);
	pc++;
	uint16_t hi = read(pc);
	pc++;

	addr_abs = (hi << 8) | lo;
	addr_abs += y;

	if ((addr_abs & 0xFF00) != (hi << 8))
		return 1;
	else
		return 0;
}

uint8_t olc6502::IND()
{
	uint16_t ptr_lo = read(pc);
	pc++;
	uint16_t ptr_hi = read(pc);
	pc++;

	uint16_t ptr = (ptr_hi << 8) | ptr_lo;

	if (ptr_lo == 0x00FF)	// simulate the hardware bug with pages
	{
		addr_abs = ( (uint16_t)read(ptr & 0xFF00) << 8) | read(ptr);
	}
	else					// execute normally
	{
		addr_abs = ( (uint16_t)read(ptr + 1) << 8) | read(ptr);
	}

	return 0;
}

uint8_t olc6502::IZX()
{
	uint16_t t = read(pc);
	pc++;

	uint16_t lo = read((t + (uint16_t)x) & 0x00FF);
	uint16_t hi = read((t + (uint16_t)x + 1) & 0x00FF);

	addr_abs = (hi << 8) | lo;
	return 0;
}

uint8_t olc6502::IZY()
{
	uint16_t t = read(pc);
	pc++;

	uint16_t lo = read(t & 0x00FF);
	uint16_t hi = read((t + 1) & 0x00FF);

	addr_abs = (hi << 8) | lo;
	addr_abs += y;

	if ((addr_abs & 0xFF00) != (hi << 8))
		return 1;
	else
		return 0;
}

uint8_t olc6502::REL()
{
	addr_rel = read(pc);
	pc++;
	if (addr_rel & 0x80)		// check whether the most significant bit is set to 1 or not
		addr_rel |= 0xFF00;		// if yes then make all the 1's in the 1st byte
	return 0;
}

// INSTRUCTIONS 

uint8_t olc6502::fetch()
{
	if (lookup[opcode].addrmode != &olc6502::IMP)
		fetched = read(addr_abs);
	return fetched;
}

uint8_t olc6502::AND()
{
	fetch();
	a = a & fetched;	
	setFlag(Z, a == 0x00);
	setFlag(N, a & 0x80);
	return 1;
}

uint8_t olc6502::BCS()
{
	if (getFlag(C) == 1)
	{
		cycles++;
		addr_abs = pc + addr_rel;

		if ((addr_abs & 0xFF00) != (pc & 0xFF00))
			cycles++;

		pc = addr_abs;
	}
	return 0;
}

uint8_t olc6502::BCC()
{
	if (getFlag(C) == 0)
	{
		cycles++;
		addr_abs = pc + addr_rel;

		if ((addr_abs & 0xFF00) != (pc & 0xFF00))
			cycles++;

		pc = addr_abs;
	}
	return 0;
}

uint8_t olc6502::BEQ()
{
	if (getFlag(Z) == 1)
	{
		cycles++;
		addr_abs = pc + addr_rel;

		if ((addr_abs & 0xFF00) != (pc & 0xFF00))
			cycles++;

		pc = addr_abs;
	}
	return 0;
}

uint8_t olc6502::BMI()
{
	if (getFlag(N) == 1)
	{
		cycles++;
		addr_abs = pc + addr_rel;

		if ((addr_abs & 0xFF00) != (pc & 0xFF00))
			cycles++;

		pc = addr_abs;
	}
	return 0;
}

uint8_t olc6502::BNE()
{
	if (getFlag(Z) == 0)
	{
		cycles++;
		addr_abs = pc + addr_rel;

		if ((addr_abs & 0xFF00) != (pc & 0xFF00))
			cycles++;

		pc = addr_abs;
	}
	return 0;
}

uint8_t olc6502::BPL()
{
	if (getFlag(N) == 0)
	{
		cycles++;
		addr_abs = pc + addr_rel;

		if ((addr_abs & 0xFF00) != (pc & 0xFF00))
			cycles++;

		pc = addr_abs;
	}
	return 0;
}

uint8_t olc6502::BVC()
{
	if (getFlag(V) == 0)
	{
		cycles++;
		addr_abs = pc + addr_rel;

		if ((addr_abs & 0xFF00) != (pc & 0xFF00))
			cycles++;

		pc = addr_abs;
	}
	return 0;
}

uint8_t olc6502::BVS()
{
	if (getFlag(V) == 1)
	{
		cycles++;
		addr_abs = pc + addr_rel;

		if ((addr_abs & 0xFF00) != (pc & 0xFF00))
			cycles++;

		pc = addr_abs;
	}
	return 0;
}


uint8_t olc6502::CLC()
{
	setFlag(C, false);
	return 0;
}

uint8_t olc6502::CLD()
{
	setFlag(D, false);
	return 0;
}


uint8_t olc6502::ADC()
{
	fetch();
	uint16_t temp = (uint16_t)a + (uint16_t)fetched + (uint16_t)getFlag(C);
	setFlag(C, temp > 255);
	setFlag(Z, (temp & 0x00FF) == 0);
	setFlag(N, temp & 0x0080);
	setFlag(V, (~((uint16_t)a ^ (uint16_t)fetched)) & ((uint16_t)a ^ (uint16_t)temp) & 0x0080);
	a = temp & 0x00FF;
	return 1;
}

uint8_t olc6502::SBC()
{
	fetch();

	uint16_t invValue = (~fetched);

	uint16_t temp = (uint16_t)a + invValue + (uint16_t)getFlag(C);
	setFlag(C, temp & 0xFF00);
	setFlag(Z, (temp & 0x00FF) == 0);
	setFlag(N, temp & 0x0080);
	setFlag(V, (~((uint16_t)a ^ (uint16_t)fetched)) & ((uint16_t)a ^ (uint16_t)temp) & 0x0080);
	a = temp & 0x00FF;
	return 1;
}

// push on the stack
uint8_t olc6502::PHA()
{
	write(0x0100 + stkp, a);
	stkp--;
	return 0;
}

// pop from the stack
uint8_t olc6502::PLA()
{
	stkp++;
	a = read(0x0100 + stkp);
	setFlag(Z, a == 0x00);
	setFlag(N, a & 0x80);
	return 0;
}

uint8_t olc6502::RTI()
{
	stkp++;
	status = read(0x0100 + stkp);
	status &= ~B;	// unset the flag B
	status &= ~U;	// unset the flag U

	stkp++;
	pc = (uint16_t)read(0x0100 + stkp);
	stkp++;
	pc |= ((uint16_t)read(0x0100 + stkp) << 8);
	return 0;
}