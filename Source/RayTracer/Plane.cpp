#include "Plane.h"
#include "Ray.h"
#include "MathUtils.h"

bool Plane::Hit(const ray_t& ray, float minDistance, float maxDistance, raycastHit_t& raycastHit)
{
    // Check dot product of ray direction and plane normal, if result is 0 then ray direction is parallel to plane
    // The dot product is 0 if the two vectors are perpendicular (90 degrees)
    float denominator = glm::dot(ray.direction, m_normal);
    if (MathUtils::approximately(denominator, 0.0f))
    {
        return false; // Ray direction and plane are parallel, no intersection
    }

    // Get t (distance) along ray direction to hit point
    float t = glm::dot(m_center - ray.origin, m_normal) / denominator;
    if (t < 0)
    {
        return false; // Plane is behind ray's origin, no intersection
    }

    // Check if t is outside min and max distance
    if (t < minDistance || t > maxDistance)
    {
        return false;
    }

    // Set raycast hit
    raycastHit.distance = t;
    raycastHit.point = ray.origin + t * ray.direction;
    raycastHit.normal = m_normal;
    raycastHit.material = GetMaterial();

    return true;

}