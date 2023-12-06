#pragma once
#include <glm/glm.hpp>
class MathUtils
{
public:
	template <typename T>
	static inline T lerp(const T& a, const T& b, float t) {
		return a + t * (b - a);
	}

    inline glm::vec3 cross(const glm::vec3& v1, const glm::vec3& v2)
    {
        return glm::vec3(
            (v1.y * v2.z) - (v1.z * v2.y),
            (v1.z * v2.x) - (v1.x * v2.z),
            (v1.x * v2.y) - (v1.y * v2.x)
        );
    }

    inline static float dot(const glm::vec3& v1, const glm::vec3& v2)
    {
        return glm::dot(v1, v2);
    }

    inline glm::vec3 reflect(const glm::vec3& v, const glm::vec3& n)
    {
        //return glm::reflect(v, glm::normalize(n));
        return glm::reflect(v, n);
    }

    inline static bool approximately(float value1, float value2)
    {
        // check if the difference between the values is less than epsilon
        return (std::fabs(value1 - value2) < FLT_EPSILON);
    }

    inline static bool refract(const glm::vec3& v, const glm::vec3& n, float index, glm::vec3& refracted)
    {
        // normalize the incoming vector (v)
        glm::vec3 nv = glm::normalize(v);

        float dt = dot(nv, n);
        float discriminant = 1 - (index * index) * (1 - dt * dt);
        if (discriminant > 0)
        {
            refracted = index * (nv - (n * dt)) - (n * std::sqrt(discriminant));
            return true;
        }

        return false;
    }

    inline static float schlick(float cosine, float index)
    {
        // calculate specular reflection coefficient, or probability of reflection
        float r0 = (1.0f - index) / (1 + index);
        r0 = r0 * r0;
        return r0 + (1.0f - r0) * (float)std::pow((1.0f - cosine), 5);
    }
};