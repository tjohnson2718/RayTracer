#pragma once
#include "glm/glm.hpp"

class Color
{
public:
	using color3_t = glm::vec3;
	using color4_t = glm::vec4;
	using rgba_t = uint32_t;

	inline color4_t RGBAToColor(const rgba_t& rgba);
	inline rgba_t ColorToRGBA(const color4_t& color);

	
};