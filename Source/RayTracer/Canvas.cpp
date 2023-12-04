#include "Canvas.h"
#include <SDL.h>
#include  "Color.h"

Canvas::Canvas(int width, int height, const Renderer& renderer)
{
	m_size = { width, height };
	m_texture = SDL_CreateTexture(renderer.m_renderer,
		SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING,
		width, height);

	m_buffer.resize(width * height);
}

Canvas::~Canvas()
{
	if (m_texture != nullptr)
	{
		SDL_DestroyTexture(m_texture);
	}
}

void Canvas::Update()
{
	// set texture with buffer rgba_t data
	SDL_UpdateTexture(m_texture, nullptr, m_buffer.data(), m_size.x * sizeof(Color::rgba_t));
}

void Canvas::Clear(const Color::color4_t& color)
{
	Color::rgba_t rgba = Color::ColorToRGBA(color);
	std::fill(m_buffer.begin(), m_buffer.end(), rgba);
}

void Canvas::DrawPoint(const glm::ivec2& point, const Color::color4_t& color)
{
	if (point.x < 0 || point.x >= m_size.x || point.y < 0 || point.y >= m_size.y)
	{
		return;
	}

	m_buffer[point.x + (point.y * m_size.x)] = Color::ColorToRGBA(color);
}
