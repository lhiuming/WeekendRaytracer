#include <iostream>

#include "vec3.h"
#include "ray.h"
#include "hitable.h"
#include "hitable_list.h"
#include "sphere.h"
#include "camera.h"
#include <random>

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
    camera mainCam{};

    // file header
    int width = 1080;
    int height = 540;
    std::cout << "P3\n" << width << " " << height << "\n255\n";

    // color data; start from upper-left of the image
    // NOTE: we use a right-hand coordinate for camera space, with camera looking at -z axis
    std::random_device rand_dev;
    std::default_random_engine rand_engine(rand_dev());
    auto rand_gen = std::uniform_real_distribution<float>();
    int n_sample = 128;
    for (int j = height - 1; j >= 0; j--) {
        for (int i = 0; i < width; i++) {
            vec3 col(0, 0, 0);
            for (int k = 0; k < n_sample; ++k) {
                float u = float(i + rand_gen(rand_engine)) / float(width);
                float v = float(j + rand_gen(rand_engine)) / float(height);
                col += color(mainCam.get_ray(u, v), scene);
            }
            col /= n_sample;
            int ir = int(255.99 * col.r());
            int ig = int(255.99 * col.g());
            int ib = int(255.99 * col.b());
            std::cout << ir << " " << ig << " " << ib << "\n";
        }
    }

    return 0;
}
