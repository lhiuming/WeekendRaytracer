#ifndef SPHERE_H
#define SPHERE_H

#include <cmath>
#include "hitable.h"

class sphere : public hitable {
public:
    vec3 center;
    float radius;

    sphere(): radius(0) {}
    sphere(const vec3& center, float radius) : center(center), radius(radius) {}

    bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const override;
};

inline bool sphere::hit(const ray& r, float t_min, float t_max, hit_record& rec) const {
    // if the quad eq has solution
    vec3 oc = r.origin() - center;
    float a = dot(r.direction(), r.direction());
    float b = dot(r.direction(), oc); // note: 2 is eleminated
    float c = dot(oc, oc) - radius * radius;
    float discriminant = b * b - a * c; // note: 4 is eliminated
    if (discriminant > 0) { // note: fine to ignore the 0 case
        float t = (-b - std::sqrt(discriminant)) / a; // note: 2 is eliminated in the denominator
        if (t_min <= t && t < t_max ) {
            rec.t = t;
            rec.point = r.point_at(t);
            rec.normal = (rec.point - center) / radius;
            return true;
        }
        t = (-b + std::sqrt(discriminant)) / a;
        if (t_min <= t && t < t_max) {
            rec.t = t;
            rec.point = r.point_at(t);
            rec.normal = (rec.point - center) / radius;
            return true;
        }
    }
    return false;
}

#endif // SPHERE_H
