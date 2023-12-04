#include "Sphere.h"
#include "Ray.h"

bool Sphere::Hit(const ray_t& ray, float minDistance, float maxDistance, raycastHit_t& raycastHit)
{
    glm::vec3 oc = ray.origin - m_center;
    float a = glm::dot(ray.direction, ray.direction);
    float b = 2 * glm::dot(ray.direction, oc);
    float c = glm::dot(oc, oc) - (m_radius * m_radius);

    // b^2 - 4ac
    float discriminant = (b * b) - (4 * a * c);

    // 0 = 1 hit
    // 1 = 2 hit

    if (discriminant >= 0)
    {
        float t = (-b - sqrt(discriminant)) / (2 * a);
        if (t > minDistance && t < maxDistance)
        {
            raycastHit.distance = t;
            raycastHit.point = ray.At(t);
            raycastHit.normal = (raycastHit.point - m_center) / m_radius;

            raycastHit.material = GetMaterial();

            return true;
        }
        t = (-b + sqrt(discriminant)) / (2 * a);
        if (t > minDistance && t < maxDistance)
        {
            raycastHit.distance = t;
            raycastHit.point = ray.At(t);
            raycastHit.normal = (raycastHit.point - m_center) / m_radius;

            raycastHit.material = GetMaterial();

            return true;
        }
    }

    return false;
}