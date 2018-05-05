#include <iostream>

#include "vec3.h"
#include "ray.h"

bool hit_shpere(const vec3 &center, float radius, const ray &ray) {
    // if the quad eq has solution
    vec3 oc = ray.origin() - center;
    float a = dot(ray.direction(), ray.direction());
    float b = 2 * dot(ray.direction(), oc);;
    float c = dot(oc, oc) - radius * radius;
    return (b * b - 4 * a * c) >= 0;
}

vec3 color(const ray& nonUnitRay ) {
    // hit color
    if (hit_shpere(vec3(0, 0, -1), 0.5, nonUnitRay)) return vec3(.9, .4, .2);
    // sky color
    vec3 unitDir = normalized(nonUnitRay.direction());
    float t = 0.5 * (unitDir.y() + 1.0);
    return t * vec3(.5, .7, 1) + (1. - t) * vec3(1., 1., 1.);
}

int main() {
    // file header
    int width = 720;
    int height = 360;
    std::cout << "P3\n" << width << " " << height << "\n255\n";

    // color data; start from upper-left of the image
    // NOTE: we use a right-hand coordinate for camera space, with camera looking at -z axis
    vec3 lower_left_corner(-2, -1, -1);
    vec3 horizontal(4, 0, 0);
    vec3 vertical(0, 2, 0);
    vec3 origin(0, 0, 0);
    for (int j = height - 1; j >= 0; j--)
    {
        for (int i = 0; i < width; i++)
        {
            float u = float(i) / float(width);
            float v = float(j) / float(height);
            ray r(origin, lower_left_corner + u * horizontal + v * vertical);
            vec3 col = color(r);
            int ir = int(255.99 * col.r());
            int ig = int(255.99 * col.g());
            int ib = int(255.99 * col.b());
            std::cout << ir << " " << ig << " " << ib << "\n";
        }
    }

    return 0;
}
