#include <iostream>
#include <chrono>
#include <ctime>
#include "Renderer.h"
#include "Random.h"
#include "Canvas.h"

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

	Canvas canvas(400, 300, renderer);

	bool quit = false;
	while (!quit)
	{
		canvas.Clear({ 0, 0, 0, 1 });
		for (int i = 0; i < 1000; i++)
		{
			canvas.DrawPoint({ Random::random(canvas.GetSize().x, canvas.GetSize().y), 
				Random::random(canvas.GetSize().x, canvas.GetSize().y) }, 
				{ Color::color3_t(Random::random(1, 255)), 1 });
		}
		canvas.Update();

		renderer.PresentCanvas(canvas);
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