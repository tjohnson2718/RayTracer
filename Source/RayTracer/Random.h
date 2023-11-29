#pragma once
#include <cstdlib>
#include <algorithm>

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
};