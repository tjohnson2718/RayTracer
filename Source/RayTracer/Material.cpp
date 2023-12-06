#include "Material.h"
#include "Random.h"
#include "MathUtils.h"

bool Lambertian::Scatter(const ray_t& ray, const raycastHit_t& raycastHit, Color::color3_t& color, ray_t& scattered) const
{
    //glm::vec3 target = <raycast hit point + raycast hit normal + random in unit sphere
    glm::vec3 target = raycastHit.point + raycastHit.normal + Random::randomInUnitSphere();
    //glm::vec3 direction = <create a direction from raycast hit point to the target and normalize it>;
    glm::vec3 direction = glm::normalize(target - raycastHit.point);

    //scattered = <set scattered ray with raycast hit point as the origin and the new direction>;
    scattered.origin = raycastHit.point;
    scattered.direction = direction;
    
    color = m_albedo;

    return true;
}

bool Metal::Scatter(const ray_t& ray, const raycastHit_t& raycastHit, glm::vec3& color, ray_t& scattered) const
{
    //glm::vec3 reflected = <get reflected ray from normalized ray direction and raycast hit normal>;
    glm::vec3 reflected = glm::reflect(glm::normalize(ray.direction), raycastHit.normal);

    // set scattered ray from reflected ray + random point in sphere (fuzz = 0 no randomness, fuzz = 1 random reflected)
    // a mirror has a fuzz value of 0 and a diffused metal surface a higher value
    //scattered = ray_t{ <raycast hit point>, <reflected + random unit sphere * fuzz> };
    scattered = ray_t{ raycastHit.point, ((reflected + Random::randomInUnitSphere()) * m_fuzz) + reflected };
    color = m_albedo;
    // make sure that reflected ray is going away from surface normal (dot product > 0, angle between vectors < 90 degrees)
    return glm::dot(scattered.direction, raycastHit.normal) > 0;
}

bool Dielectric::Scatter(const ray_t& ray, const raycastHit_t& raycastHit, glm::vec3& color, ray_t& scattered) const
{
    glm::vec3 reflected = reflect(glm::normalize(ray.direction), raycastHit.normal);
    glm::vec3 refracted;

    glm::vec3 outNormal;
    float ni_over_nt;
    float cosine;

    // ray hits inside of surface ( ray -> | -> normal )
    // ray is going out of object (ray direction is facing in the same direction of the surface normal)
    if (glm::dot(ray.direction, raycastHit.normal) > 0)
    {
        outNormal = -raycastHit.normal;
        ni_over_nt = m_index;
        cosine = m_index * glm::dot(ray.direction, raycastHit.normal) / ray.direction.length();
    }
    else
    {
        // ray hits outside of surface ( ray -> | <- normal )
        // ray is going into object (ray direction is facing in the opposite direction of the surface norma)
        outNormal = raycastHit.normal;
        ni_over_nt = 1.0f / m_index;
        cosine = -glm::dot(ray.direction, raycastHit.normal) / ray.direction.length();
    }

    // set the probability of the ray being reflected or refracted
    float reflectProbability = 1.0f;
    if (MathUtils::refract(ray.direction, outNormal, ni_over_nt, refracted))
    {
        // use schlick and cosine (angle) to determine if ray is reflected or refracted
        reflectProbability = MathUtils::schlick(cosine, m_index);
    }

    // create reflected or refracted ray
    scattered = (Random::random01() < reflectProbability) ? ray_t{ raycastHit.point, reflected } : ray_t{ raycastHit.point, refracted };
    color = m_albedo;

    return true;
}