#include <iostream>
#include "Renderer.h"

int main(int argc, char* argv[])
{
	std::cout << "Hello World!";
	Renderer renderer;

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