#include "Canvas.h"
Canvas::Canvas(int width, int height, const Renderer& renderer)
{
	m_size = { <set size with width and height> };
	m_texture = SDL_CreateTexture(renderer.m_renderer,
		<RGBA 8888>, SDL_TEXTUREACCESS_STREAMING,
		width, height);

	m_buffer.<resize vector to hold width* height elements>
}

Canvas::~Canvas()
{
	<if m_texture not nullptr SDL Destroy Texture https ://wiki.libsdl.org/SDL2/SDL_DestroyTexture
	Links to an external site.>
}

void Canvas::Update()
{
	// set texture with buffer rgba_t data
	SDL_UpdateTexture(<https://wiki.libsdl.org/SDL2/SDL_UpdateTexture
	Links to an external site.>);
}

void Canvas::Clear(const color4_t& color)
{
	rgba_t rgba = <convert color to RGBA>
		std::fill(<fill m_buffer with rgba(https://en.cppreference.com/w/cpp/algorithm/fill
	Links to an external site.)>);
}

void Canvas::DrawPoint(const glm::ivec2& point, const color4_t& color)
{
	if (< point is outside of canvas bounds(point < 0 or >= size width or size height>) return;
		m_buffer[point.x + (point.y * m_size.x)] = <convert color to RGBA>;
}