#include <iostream>

#include "vec3.h"
#include "ray.h"
#include "hitable.h"
#include "hitable_list.h"
#include "sphere.h"

vec3 color(const ray& nonUnitRay, const hitable& scene ) {
    // hit color
    hit_record record;
    if (scene.hit(nonUnitRay, 0, 100, record)) {
        return (record.normal + vec3(1, 1, 1)) / 2;
    }
    // sky color
    vec3 unitDir = normalized(nonUnitRay.direction());
    float t = .5 * (unitDir.y() + 1.);
    return t * vec3(.5, .7, 1) + (1. - t) * vec3(1, 1, 1);
}

int main() {
    // simpel scene
    hitable_list scene(2);
    scene[0] = new sphere({ 0, 0, -1 }, 0.5);
    scene[1] = new sphere({ 0, -100.5, -1 }, 100);

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
            vec3 col = color(r, scene);
            int ir = int(255.99 * col.r());
            int ig = int(255.99 * col.g());
            int ib = int(255.99 * col.b());
            std::cout << ir << " " << ig << " " << ib << "\n";
        }
    }

    return 0;
}
