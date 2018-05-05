#ifndef RAY_H
#define RAY_H

#include "vec3.h"


class ray {

    vec3 m_origin;
    vec3 m_direction;

public:

    ray() = default;
    ray(const vec3 &origin, const vec3 &direction) : m_origin(origin), m_direction(direction) { }

    vec3 origin() const { return m_origin; }
    vec3 direction() const { return m_direction; }
    vec3 point_at(float t) const { return m_origin + t * m_direction; }

};

#endif // RAY_H
