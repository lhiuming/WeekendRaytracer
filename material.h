#ifndef MATERIAL_H
#define MATERIAL_H

#include "ray.h"
#include "hitable.h"
#include "rand.h"

class material {
public:
    virtual bool scatter(const ray& r, const hit_record& rec, vec3& attenutation, ray& scattered) const = 0;
};

/*
 *  Lambertian material
 */
class lambertian : public material {
    vec3 albedo;
public:
    lambertian(vec3 albedo) : albedo(albedo) {}
    bool scatter(const ray& r, const hit_record& rec, vec3& attenutation, ray& scattered) const override; 
};

inline bool lambertian::scatter(const ray& r, const hit_record& rec, vec3& attenutation, ray& scattered) const {
    // simulated lambertion BRDF
    scattered = ray(rec.point, rec.normal * 1.5 + random_in_unit_sphere());
    attenutation = albedo;
    return true;
}

static inline vec3 reflect(const vec3& in, const vec3& normal) {
    return in - 2 * dot(in, normal) * normal;
}

/*
 *  Smooth matalic material
 */
class matel : public material {
    float fuzz;
    vec3 albedo;
public:
    matel(const vec3& albedo, float fuzz_factor) : albedo(albedo) {
        if (fuzz_factor < 1) fuzz = fuzz_factor; else fuzz = 1;
    }
    bool scatter(const ray& r, const hit_record& rec, vec3& attenutation, ray& scattered) const override;
};

inline bool matel::scatter(const ray& r, const hit_record& rec, vec3& attenutation, ray& scattered) const {
    vec3 reflected = reflect(r.direction(), rec.normal);
    scattered = ray(rec.point, reflected + fuzz * random_in_unit_sphere()); // add some lambertian diff here
    attenutation = albedo;
    return dot(reflected, rec.normal) > 0;
}

/*
 * Dielectric
 */
class dielectric : public material {
    float r_i;
    // note: i for input, r for refracted; outward_normal is against the input ray direction
    bool refract(const vec3& i, const vec3& outward_normal, float ni_over_nr, vec3& refractred) const {
        vec3 dir = normalized(i);
        float cos_i_neg = dot(dir, outward_normal); // == -cos(theta_i)
        float discriminant = 1 - (ni_over_nr * ni_over_nr * (1 - cos_i_neg * cos_i_neg));
        if (discriminant > 0) {
            // NOTE: this part is highly diferrently from the book ! FIXME
            vec3 veritcal_comp = -outward_normal * sqrt(discriminant); // == cos(theta_r) if 2D
            vec3 horizontal_comp = ni_over_nr * (dir - outward_normal * cos_i_neg); // == sin(theta_r) if 2D
            refractred = horizontal_comp + veritcal_comp;
            return true;
        } else {
            return false;
        }
    }
public:
    dielectric(float refract_index) : r_i(refract_index) {}
    bool scatter(const ray& r, const hit_record& rec, vec3& attenutation, ray& scattered) const override;
};

inline bool dielectric::scatter(const ray& r, const hit_record& rec, vec3& attenutation, ray& scattered) const {
    attenutation = vec3(1, 1, 1);
    // refract or reflect
    vec3 outward_normal;
    float ni_over_nr;
    vec3 refracted;
    if (dot(r.direction(), rec.normal) > 0) { // from inside to outside
        outward_normal = -rec.normal;
        ni_over_nr = r_i;
    } else { // from outside to inside
        outward_normal = rec.normal;
        ni_over_nr = 1.0 / r_i;
    }
    if (refract(r.direction(), outward_normal, ni_over_nr, refracted)) {
        scattered = ray(rec.point, refracted);
        return true;
    } else {
        scattered = ray(rec.point, reflect(r.direction(), rec.normal));
        // NOTE: shoule also try return true !!!
        return false;
    }
}

#endif // MATERIAL_H
