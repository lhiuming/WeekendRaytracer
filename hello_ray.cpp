#include <iostream>

#include "vec3.hpp"

int main()
{
    int width = 720;
    int height = 480;

    std::cout << "P3\n" << width << " " << height << "\n255\n"; // head file ?

    for (int j = height - 1; j >= 0; j--)
    {
        for (int i = 0; i < width; i++)
        {
            float r = float(i) / float(width);
            float g = float(j) / float(height);
            int ir = int(255.99 * r);
            int ig = int(255.99 * g);
            int ib = 128;
            std::cout << ir << " " << ig << " " << ib << "\n";
        }
    }
}