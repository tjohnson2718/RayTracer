#include "Renderer.h"
#include <iostream>
bool Renderer::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		std::cerr << "SDL Error: " << SDL_GetError() << std::endl;
		return false;
	}
	return true;
}

void Renderer::Shutdown()
{
	if (m_window != nullptr) SDL_DestroyWindow(m_window);
	if (m_renderer != nullptr) SDL_DestroyRenderer(m_renderer);
	SDL_Quit();
}

bool Renderer::CreateWindow(const std::string& title, int width, int height)
{
	m_window = SDL_CreateWindow(title.c_str(), 100, 100, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
	if (!m_window)
	{
		std::cerr << "SDL Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return false;
	}

	m_renderer = SDL_CreateRenderer(m_window, -1, 0);
	if (!m_renderer)
	{
		std::cerr << "SDL Error: " << SDL_GetError() << std::endl;
		return false;
	}

	return true;
}
