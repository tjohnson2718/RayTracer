#include <iostream>
#include <chrono>
#include <ctime>
#include "Renderer.h"
#include "Random.h"

int main(int argc, char* argv[])
{
	std::cout << "Hello World!";
	Renderer renderer;
	auto currentTime = std::chrono::system_clock::now();
	auto currentTimeInSeconds = std::chrono::duration_cast<std::chrono::seconds>(currentTime.time_since_epoch());
	unsigned int seed = static_cast<unsigned int>(currentTimeInSeconds.count());
	Random::seedRandom(seed);



	if (!renderer.Initialize())
	{
		std::cout << "Failed to Initialize Renderer";
	}

	if (!renderer.CreateWindow("Renderer", 400, 300))
	{
		std::cout << "Failed to Create Window";
	}

	bool quit = false;
	while (!quit)
	{
		SDL_Event event;
		SDL_PollEvent(&event);
		switch (event.type)
		{
		case SDL_QUIT:
			quit = true;
			break;
		}
	}

	renderer.Shutdown();

	return 0;
}