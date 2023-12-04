#include <iostream>
#include <chrono>
#include <ctime>
#include "Renderer.h"
#include "Random.h"
#include "Canvas.h"
#include "Material.h"
#include "Scene.h"
#include "Sphere.h"


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

	if (!renderer.CreateWindow("Renderer", 800, 700))
	{
		std::cout << "Failed to Create Window";
	}

	Canvas canvas(400, 300, renderer);

	float aspectRatio = canvas.GetSize().x / (float)canvas.GetSize().y;
	std::shared_ptr<Camera> camera = std::make_shared<Camera>(glm::vec3{ 0, 0, 1 }, glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 1, 0 }, 70.0f, aspectRatio);
	
	Scene scene(30); // sky color could be set with the top and bottom color
	scene.SetCamera(camera);

	// create material
	//auto material = std::make_shared<Lambertian>(Color::color3_t{ 0, 1, 0 });

	// create material
	auto lambertian = std::make_shared<Lambertian>(Color::color3_t{ 0, 0, 1 });
	auto metal = std::make_shared<Metal>(Color::color3_t{ 1, 1, 1 }, 0.0f);

	// create objects -> add to scene
	for (int i = 0; i < 10; i++)
	{
		std::shared_ptr<Material> material = (rand() % 2) ? std::dynamic_pointer_cast<Material>(lambertian) : std::dynamic_pointer_cast<Material>(metal);
		auto sphere = std::make_unique<Sphere>(glm::vec3{ Random::random(-3, 3), Random::random(-3, 3), Random::random(-5, 0) }, Random::random(0.2f, 1), material);
		scene.AddObject(std::move(sphere));
	}
	canvas.Clear({ 0, 0, 0, 1 });
	scene.Render(canvas, 50);
	canvas.Update();
	
	bool quit = false;
	while (!quit)
	{
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