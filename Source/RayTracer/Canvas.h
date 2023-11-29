#pragma once
#include <SDL.h>
#include <vector>
#include "Color.h"

class Renderer;
class Canvas
{
public:
    Canvas(int width, int height, const Renderer& renderer);
    ~Canvas();

    void Update();

    void Clear(const Color::color4_t& color);
    void DrawPoint(const glm::ivec2& point, const Color::color4_t& color);

    // Return const reference of m_size
    const glm::ivec2& GetSize() const { return m_size; }

    // Allow Renderer to access Canvas private data
    friend class Renderer;

private:
    // Forward declaration of SDL Texture pointer
    struct SDL_Texture; // Assuming SDL_Texture is an internal type

    SDL_Texture* m_texture = nullptr;
    std::vector<Color::rgba_t> m_buffer;
    glm::ivec2 m_size = glm::ivec2(0, 0);
};