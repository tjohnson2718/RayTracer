#pragma once
#include "Ray.h"
#include <glm/glm.hpp>

class Camera
{
public:
	Camera(const glm::vec3& eye, const glm::vec3& target, const glm::vec3& up, float fov, float aspectRatio);

	void LookAt(const glm::vec3& eye, const glm::vec3& target, const glm::vec3& up);
	ray_t GetRay(const glm::vec2& point) const;

private:
	void CalculateViewPlane();

private:
	// eye position
	glm::vec3 m_eye{ 0 };

	// camera axis
	glm::vec3 m_right{ 0 };
	glm::vec3 m_up{ 0 };
	glm::vec3 m_forward{ 0 };

	// view plane origin and horizontal and vertical axis
	glm::vec3 m_lowerLeft{ 0 };
	glm::vec3 m_horizontal{ 0 };
	glm::vec3 m_vertical{ 0 };

	float m_fov{ 0 }; // field of view (angle is in degrees)
	float m_aspectRatio{ 0 }; // screen width / screen height (800 / 600 = 1.333)
};
