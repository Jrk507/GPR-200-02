#ifndef HITTABLE_H
#define HITTABLE_H

#include <gpro\gpro-math\gproVector.h>
#include <gpro\gpro-math\_inl\gproRay.h>

struct hit_record {//adding the ability for multiple spheres in the image to be hit by the ray
    point3 p;
    vec3 normal;
    float t;//amount of times a sphere was hit
    bool front_face;

    inline void set_face_normal(const ray& r, const vec3& outward_normal) {// sets the reflection of the ray on the image
        front_face = dot(r.direction(), outward_normal) < 0;
        normal = front_face ? outward_normal : -outward_normal;
    }
};

class hittable {
public:
    virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const = 0;
};

#endif