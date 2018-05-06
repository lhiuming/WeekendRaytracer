#ifndef RAND_H
#define RAND_H

#include <random>

static std::random_device rand_dev;
static std::default_random_engine rand_engine(rand_dev());
static auto rand_gen = std::uniform_real_distribution<float>();

inline float uniform01() {
   return rand_gen(rand_engine);
}

// a brute-force way to sample in a unit spherical volume
vec3 random_in_unit_sphere() {
    vec3 p;
    do {
        p = 2 * vec3(uniform01(), uniform01(), uniform01()) - vec3(1, 1, 1);
    } while (dot(p, p) >= 1.0);
    return p;
}

#endif // RAND_H
