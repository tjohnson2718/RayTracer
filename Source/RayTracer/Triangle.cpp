#include "Triangle.h"
#include "MathUtils.h"


bool Triangle::Hit(const ray_t& ray, float minDistance, float maxDistance, raycastHit_t& raycastHit)
{
    // set edges of the triangle
    glm::vec3 edge1 = m_v2 - m_v1;
    glm::vec3 edge2 = m_v3 - m_v1;

    // calculate triangle normal
    glm::vec3 normal = cross(edge1, edge2);
    glm::vec3 pvec = cross(ray.direction, edge2);
    float determinant = dot(pvec, edge1);

    // if determinant is less than 0 then ray is hitting back of triangle
    // if determinant is 0 then ray is parallel to triangle surface
    if (determinant < 0 || MathUtils::approximately(determinant, 0))
    {
        return false;
    }

    float invDet = 1 / determinant;

    glm::vec3 tvec = ray.origin - m_v1;
    float u = dot(tvec, pvec) * invDet;
    if (u < 0 || u > 1)
    {
        return false;
    }

    glm::vec3 qvec = cross(tvec, edge1);
    float v = dot(qvec, ray.direction) * invDet;
    if (v < 0 || u + v > 1)
    {
        return false;
    }

    float t = dot(edge2, qvec) * invDet;
    if (t >= minDistance && t <= maxDistance)
    {
        // set raycast hit
        raycastHit.distance = t;
        raycastHit.point = ray.At(t);
        raycastHit.normal = glm::normalize(normal);
        raycastHit.material = GetMaterial();

        return true;
    }

    return false;
}