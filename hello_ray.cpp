#include <iostream>

#include "vec3.h"
#include "ray.h"
#include "camera.h"
#include "hitable.h"
#include "hitable_list.h"
#include "material.h"
#include "sphere.h"
#include "rand.h"

constexpr int MAX_DEPTH = 64;

vec3 color(const ray& nonUnitRay, const hitable& scene, int depth ) {
    // hit color
    hit_record record;
    if (scene.hit(nonUnitRay, 0, std::numeric_limits<float>::max(), record)) {
        vec3 attenuation;
        ray bounce;
        if (depth < MAX_DEPTH && record.p_material->scatter(nonUnitRay, record, attenuation, bounce )) {
            vec3 bounced = color(bounce, scene, depth + 1);
            return attenuation * bounced;
        } else {
            return vec3(0, 0, 0);
        }
    }
    // sky color
    float normalized_y = nonUnitRay.direction().y() / nonUnitRay.direction().length();
    float t = .5 * (normalized_y + 1.);
    return t * vec3(.5, .7, 1) + (1. - t) * vec3(1, 1, 1);
}

int main() {
    // simpel scene
    hitable_list scene(5);
    scene[0] = new sphere(vec3(0, -100.5, -1), 100, new lambertian(vec3(1, 1, 1 )));
    scene[1] = new sphere(vec3(0, 0, -1), 0.5, new matel(vec3(0, .3, .7), 0.2));
    scene[2] = new sphere(vec3(1.3, 0.5, -2), 1, new matel(vec3(1.0, .6, .6), 0));
    scene[3] = new sphere(vec3(-1.1, 0, -1), 0.5, new dielectric(1.5)); // glass
    scene[4] = new sphere(vec3(-0.5, -0.3, -0.4), 0.2, new dielectric(2.43)); // diamond
    camera mainCam{};

    // quality setting
    int resolution_up = 1;
    int n_sample = 64;

    // file header
    int width = 200 * resolution_up;
    int height = 100 * resolution_up;
    std::cout << "P3\n" << width << " " << height << "\n255\n";

    // color data; start from upper-left of the image
    // NOTE: we use a right-hand coordinate for camera space, with camera looking at -z axis
    for (int j = height - 1; j >= 0; j--) {
        for (int i = 0; i < width; i++) {
            vec3 col(0, 0, 0);
            for (int k = 0; k < n_sample; ++k) {
                float u = float(i + uniform01()) / float(width);
                float v = float(j + uniform01()) / float(height);
                col += color(mainCam.get_ray(u, v), scene, 0);
            }
            col /= float(n_sample);
            col = vec3(sqrt(col.r()), sqrt(col.g()), sqrt(col.b())); // 2.0 gamma correction
            int ir = int(255.99 * col.r());
            int ig = int(255.99 * col.g());
            int ib = int(255.99 * col.b());
            std::cout << ir << " " << ig << " " << ib << "\n";
        }
    }

    return 0;
}
