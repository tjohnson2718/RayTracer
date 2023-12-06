#pragma once
#include "Object.h"

class Triangle : public Object
{
public:
	Triangle(const glm::vec3& v1, const glm::vec3& v2, const glm::vec3& v3, std::shared_ptr<Material> material) :
		Object{ material },
		m_v1{ v1 },
		m_v2{ v2 },
		m_v3{ v3 }
	{
	}

	bool Hit(const ray_t& ray, float minDistance, float maxDistance, raycastHit_t& hit) override;

private:
	glm::vec3 m_v1{ 0, 0, 0 };
	glm::vec3 m_v2{ 0, 0, 0 };
	glm::vec3 m_v3{ 0, 0, 0 };
};