#ifndef __TSPDECODER_H__
#define __TSPDECODER_H__

#include "TSPInstance.hpp"
#include "brkga_mp_ipr/fitness_type.hpp"
#include "brkga_mp_ipr/chromosome.hpp"
#include <cmath>
#include <iostream>
#include <fstream>
#include <iomanip>

class TSPDecoder
{
private:
public:
	TSPDecoder();
	TSPDecoder(TSPInstance &instance);
	~TSPDecoder();
	BRKGA::fitness_t decode(BRKGA::Chromosome &chromosome, bool /* not-used */);
	TSPInstance instance;
	void printSolution(BRKGA::Chromosome &chromosome, std::fstream &file);
};

#endif // __TSPDECODER_H__