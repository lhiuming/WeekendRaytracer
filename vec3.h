#ifndef VEC3_H
#define VEC3_H

#include <math.h>
#include <stdlib.h>

class vec3 {

    float e[3];

public:

    vec3() { }

    vec3(float e0, float e1, float e2) { e[0] = e0; e[1] = e1; e[2] = e2; }

    // Candy accessors
    inline float x() const { return e[0]; }
    inline float y() const { return e[1]; }
    inline float z() const { return e[2]; }
    inline float r() const { return e[0]; }
    inline float g() const { return e[1]; }
    inline float b() const { return e[2]; }
    
    // Indexers
    inline float operator[](int i) const { return e[i]; }
    inline float& operator[](int i) { return e[i]; }

    // Unary arithmetic operators
    inline const vec3& operator+() const { return *this; }
    inline vec3 operator-() const { return vec3(-x(), -y(), -z()); }

    // Assignements
    inline vec3& operator+=(const vec3 &other) { 
        e[0] += other.e[0];  e[1] += other.e[1];  e[2] += other.e[2]; return *this;
    }
    inline vec3& operator-=(const vec3 &other) { 
        e[0] -= other.e[0];  e[1] -= other.e[1];  e[2] -= other.e[2]; return *this;
    }
    inline vec3& operator*=(const vec3 &other) {
        e[0] *= other.e[0];  e[1] *= other.e[1];  e[2] *= other.e[2]; return *this;
    }
    inline vec3& operator/=(const vec3 &other) {
        e[0] /= other.e[0];  e[1] /= other.e[1];  e[2] /= other.e[2]; return *this;
    }
    inline vec3& operator*=(float t) { e[0] *= t; e[1] *= t; e[2] *= t; return *this; }
    inline vec3& operator/=(float t) { e[0] /= t; e[1] /= t; e[2] /= t; return *this; }

    // Vector ops
    inline float length2() const { return e[0] * e[0] + e[1] * e[1] + e[2] * e[2]; }
    inline float length() const { return sqrt( length2() ); }
    inline void normalize() { (*this)/=length(); }

};


// Binary arithmetic operators
inline vec3 operator+(const vec3 &v1, const vec3 &v2) {
    return { v1.x() + v2.x(), v1.y() + v2.y(), v1.z() + v2.z() };
}

inline vec3 operator-(const vec3 &v1, const vec3 &v2) {
    return { v1.x() - v2.x(), v1.y() - v2.y(), v1.z() - v2.z() };
}

inline vec3 operator*(const vec3 &v1, const vec3 &v2) {
    return { v1.x() * v2.x(), v1.y() * v2.y(), v1.z() * v2.z() };
}

inline vec3 operator*(float a, const vec3& v) {
    return { a * v.x(), a * v.y(), a * v.z() };
}

inline vec3 operator*(const vec3& v, float a) {
    return { a * v.x(), a * v.y(), a * v.z() };
}

inline vec3 operator/(const vec3 &v, float a) {
    return {v.x() / a, v.y() / a, v.z() / a};
}

// Vector operations
inline vec3 normalized(const vec3& v) { return v / v.length(); }

inline float dot(const vec3& v1, const vec3& v2) {
    return v1.x() * v2.x() + v1.y() * v2.y() + v1.z() * v2.z();
}

#endif
