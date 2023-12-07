#include <iostream>
#include <chrono>
#include <ctime>
#include "Renderer.h"
#include "Random.h"
#include "Canvas.h"
#include "Material.h"
#include "Scene.h"
#include "Sphere.h"
#include "Triangle.h"
#include "Plane.h"
#include "Mesh.h"

class InitilizeScene
{
public:
	static void InitScene02(Scene& scene, const Canvas& canvas)
	{
		float aspectRatio = canvas.GetSize().x / canvas.GetSize().y;
		std::shared_ptr<Camera> camera = std::make_shared<Camera>(glm::vec3{ 0, 2, 10 }, glm::vec3{ 0, 1, 0 }, glm::vec3{ 0, 1, 0 }, 20.0f, aspectRatio);
		scene.SetCamera(camera);

		//auto triangle = std::make_unique<Triangle>(glm::vec3{ -1, 0, 0 }, glm::vec3{ 1, 0, 0 }, glm::vec3{ 0, 2, 0 }, std::make_shared<Lambertian>(color3_t{ 1, 0, 0 }));
		//scene.AddObject(std::move(triangle));

		auto plane = std::make_unique<Plane>(glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 1, 0 }, std::make_shared<Lambertian>(Color::color3_t{ 0.2f }));
		scene.AddObject(std::move(plane));

		auto mesh = std::make_unique<Mesh>(std::make_shared<Lambertian>(Color::color3_t{ 0, 0, 1 }));
		mesh->Load("models/cube.obj", glm::vec3{ 0, 0.5f, 0 }, glm::vec3{ 0, 45, 0 });
		scene.AddObject(std::move(mesh));
	}
};

int main(int argc, char* argv[])
{
	const int width = 800;
	const int height = 700;
	const int samples = 10;
	const int depth = 5;

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

	if (!renderer.CreateWindow("Renderer", width, height))
	{
		std::cout << "Failed to Create Window";
	}

	Canvas canvas(width, height, renderer);

	float aspectRatio = canvas.GetSize().x / (float)canvas.GetSize().y;
	std::shared_ptr<Camera> camera = std::make_shared<Camera>(glm::vec3{ 0, 1, 10 }, glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 1, 0 }, 20.0f, aspectRatio);

	Scene scene(glm::vec3{ 1.0f }, glm::vec3{ 0.5f, 0.7f, 1.0f });	
	scene.SetCamera(camera);

	// create material
	auto lambertian = std::make_shared<Lambertian>(Color::color3_t{ 0, 0, 1 });
	auto metal = std::make_shared<Metal>(Color::color3_t{ 1, 1, 1 }, 0.0f);

	std::shared_ptr<Material> material = std::make_shared<Lambertian>(Color::color3_t{ 0.2f });
	auto plane = std::make_unique<Plane>(glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 1, 0 }, material);
	scene.AddObject(std::move(plane));

	InitilizeScene::InitScene02(scene, canvas);

	// create objects -> add to scene
	//auto mesh = std::make_unique<Mesh>(std::make_shared<Lambertian>(Color::color3_t{ 0, 0, 1 }));
	//mesh->Load("models/cube.obj", glm::vec3{ 0, 0.5f, 0 }, glm::vec3{ 0, 45, 0 });
	//scene.AddObject(std::move(mesh));

	/*
	for (int x = -10; x < 10; x++)
	{
		for (int z = -10; z < 10; z++)
		{

			std::shared_ptr<Material> material;

			// create random material
			float r = Random::random01();
			if (r < 0.3f)		material = std::make_shared<Lambertian>(glm::rgbColor(glm::vec3{ Random::random(0, 360), 1.0f, 1.0f }));
			else if (r < 0.6f)	material = std::make_shared<Metal>(Color::color3_t{ Random::random(0.5f, 1.0f) }, Random::random(0, 0.5f));
			else if (r < 0.9f)	material = std::make_shared<Dielectric>(Color::color3_t{ 1.0f }, Random::random(1.1f, 2));
			else				material = std::make_shared<Emissive>(glm::rgbColor(glm::vec3{ Random::random(0, 360), 1.0f, 1.0f }), 5.0f);

			// set random sphere radius
			float radius = Random::random(0.2f, 0.3f);
			// create sphere using random radius and material
			auto sphere = std::make_unique<Sphere>(glm::vec3{ x + Random::random(-0.5f, 0.5f), radius, z + Random::random(-0.5f, 0.5f) }, radius, material);
			// add sphere to the scene
			scene.AddObject(std::move(sphere));
		}
	}
	*/
	//auto mesh = std::make_unique<Mesh>(std::make_shared<Lambertian>(Color::color3_t{ 0, 0, 1 }));
		
	/*
	for (int i = 0; i < 10; i++)
	{
		std::shared_ptr<Material> material = (rand() % 2) ? std::dynamic_pointer_cast<Material>(lambertian) : std::dynamic_pointer_cast<Material>(metal);
		auto sphere = std::make_unique<Sphere>(glm::vec3{ Random::random(-3, 3), Random::random(-3, 3), Random::random(-5, 0) }, Random::random(0.2f, 1), material);
		scene.AddObject(std::move(sphere));
	}
	*/

	//material = std::dynamic_pointer_cast<Material>(lambertian);
	//auto triangle = std::make_unique<Triangle>(glm::vec3(-1, 0, 0), glm::vec3(1, 0, 0), glm::vec3(0, 1, 0), material);
	//scene.AddObject(std::move(triangle));

	canvas.Clear({ 0, 0, 0, 1 });
	scene.Render(canvas, samples, depth);
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