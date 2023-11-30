#pragma once
#include "glm/glm.hpp"

class Color
{
public:
	using color3_t = glm::vec3;
	using color4_t = glm::vec4;
	using rgba_t = uint32_t;

	inline static color4_t RGBAToColor(const rgba_t& rgba) {
		// Extract the color components from the 32-bit unsigned integer
		uint8_t r = (rgba >> 24) & 0xFF;
		uint8_t g = (rgba >> 16) & 0xFF;
		uint8_t b = (rgba >> 8) & 0xFF;
		uint8_t a = rgba & 0xFF;

		// Normalize the components to the range [0, 1]
		float inv255 = 1.0f / 255.0f;
		return color4_t(r * inv255, g * inv255, b * inv255, a * inv255);
	}

	inline static rgba_t ColorToRGBA(const color4_t& color)
	{
		uint8_t r = static_cast<uint8_t>(color.r * 255.0f);
		uint8_t g = static_cast<uint8_t>(color.g * 255.0f);
		uint8_t b = static_cast<uint8_t>(color.b * 255.0f);
		uint8_t a = static_cast<uint8_t>(color.a * 255.0f);

		// Pack the components into a 32-bit unsigned integer
		return (static_cast<uint32_t>(r) << 24) |
			(static_cast<uint32_t>(g) << 16) |
			(static_cast<uint32_t>(b) << 8) |
			(static_cast<uint32_t>(a));
	}

	friend class Canvas;
};