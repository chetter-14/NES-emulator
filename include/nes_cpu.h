#ifndef NES_CPU_H
#define NES_CPU_H

#include <cstdint>

class Bus;

class NES_cpu
{
public:
	NES_cpu() { }
	~NES_cpu() { }

	void connectBus(Bus* b) { bus = b;  }

public:
	enum FLAGS6502
	{
		C = (1 << 0),	// Carry bit
		Z = (1 << 1),	// Zero
		I = (1 << 2),	// Disable Interrupts
		D = (1 << 3),	// Decimal mode (not used in this implementation)
		B = (1 << 4),	// Break
		U = (1 << 5),	// Unused
		V = (1 << 6),	// Overflow
		N = (1 << 7)	// Negative
	};



private:
	Bus* bus = nullptr;
	void write(uint16_t addr, uint8_t data);
	uint8_t read(uint16_t addr);

};


#endif