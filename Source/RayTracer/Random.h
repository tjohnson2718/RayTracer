#pragma once
#include <cstdlib>
#include <algorithm>
#include <glm/glm.hpp>
#include <glm/gtx/norm.hpp>
#include <glm/gtc/random.hpp>

class Random
{
public:
    static void seedRandom(unsigned int seed)
    {
        std::srand(seed);
    }

    static float random01()
    {
        return static_cast<float>(std::rand()) / RAND_MAX;
    }

    static float random(float min, float max)
    {
        if (min > max) {
            std::swap(min, max);
        }

        return min + (max - min) * random01();
    }

    inline static glm::vec3 random(const glm::vec3& min, const glm::vec3& max) { return glm::linearRand(min, max); }

    inline static glm::vec3 randomInUnitSphere()
    {
        glm::vec3 v;
        // generate random vectors between -1 <-> +1, return vector if length is less than 1
        do
        {
            v = random(glm::vec3{ -1, -1, -1 }, glm::vec3{ 1, 1, 1 });
        } while (glm::length2(v) >= 1.0f);

        return v;
    }
};