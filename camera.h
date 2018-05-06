#ifndef CAMERA_H
#define CAMERA_H

#include "vec3.h"
#include "ray.h"

class camera {
    vec3 origin;
    vec3 lower_left_corner;
    vec3 horizontal;
    vec3 vertical;
public:
    camera() :
        origin(0, 0, 2),
        lower_left_corner(-2, -1, 0),
        horizontal(4, 0, 0),
        vertical(0, 2, 0)
        {}
    ray get_ray(float u, float v) const;
};

inline ray camera::get_ray(float u, float v) const {
     return ray(origin, lower_left_corner + u * horizontal + v * vertical - origin);
}

#endif // CAMERA_H
