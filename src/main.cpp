#include "./Headers/BRKGARunner.hpp"
#include <thread>

// Rodar 10 vez para cada decoder e instancia variando seed

int main(int argc, char const *argv[])
{

	const unsigned num_generations = std::stoi(argv[1]);
	BRKGARunner runner(num_generations);
	int seeds[] = {2838, 2139, 6913, 321, 4321, 9876, 12588, 20, 1295, 129482};

	std::thread threads[10];
	for (int i = 0; i < 10; i++)
	{
		threads[i] = std::thread(&BRKGARunner::run, &runner, seeds[i]);
	}

	for (int i = 0; i < 10; i++)
	{
		threads[i].join();
	}

	return 0;
}
