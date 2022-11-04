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

private:
	Bus* bus = nullptr;
	void write(uint16_t addr, uint8_t data);
	uint8_t read(uint16_t addr);
};


#endif