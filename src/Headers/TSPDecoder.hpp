#ifndef __TSPDECODER_H__
#define __TSPDECODER_H__

#include "TSPInstance.hpp"
#include "brkga_mp_ipr/fitness_type.hpp"
#include "brkga_mp_ipr/chromosome.hpp"

class TSPDecoder
{
private:
	std::vector<int> selected_rooms_;

public:
	TSPDecoder(TSPInstance &instance);
	~TSPDecoder();
	BRKGA::fitness_t decode(BRKGA::Chromosome &chromosome, bool /* not-used */);
	TSPInstance &instance;
	void DecodeRooms(BRKGA::Chromosome &chromosome);
	void Reset();
	void PrintSolution(BRKGA::Chromosome &chromosome);
};

#endif // __TSPDECODER_H__