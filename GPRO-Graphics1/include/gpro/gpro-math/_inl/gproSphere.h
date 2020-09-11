

//Code from Peter Shirley(https://raytracing.github.io/books/RayTracingInOneWeekend.html#outputanimage/addingaprogressindicator)
//Edited by Jason  Kmieciak
#ifndef SPHERE_H
#define SPHERE_H


#include <gpro\gpro-math\_inl\gproRay.h>
#include <gpro\gpro-math\_inl\gproHittable.h>

class sphere : public hittable {//the class holding multiple spheres
public:
    sphere() {}
    sphere(point3 cen, float r) : center(cen), radius(r) {};

    virtual bool hit(
        const ray& r, float tmin, float tmax, hit_record& rec) const override;
    
public: 
    point3 center;
    float radius{};
};
bool sphere::hit(const ray& r, float t_min, float t_max, hit_record& rec) const {//when a sphere is hit by a ray 
    vec3 oc = r.origin() - center;
    float a = r.direction().length_squared();
    float half_b = dot(oc, r.direction());
    float c = oc.length_squared() - radius * radius;
    float discriminant = half_b * half_b - a * c;

    if (discriminant > 0) {
        float root = sqrt(discriminant);

        float temp = (-half_b - root) / a;// sets the hit for the ray and when the ray is reflected
        if (temp < t_max && temp > t_min) {
            rec.t = temp;
            rec.p = r.at(rec.t);
            vec3 outward_normal = (rec.p - center) / radius;
            rec.set_face_normal(r, outward_normal);
            return true;
        }

        temp = (-half_b + root) / a;
        if (temp < t_max && temp > t_min) {
            rec.t = temp;
            rec.p = r.at(rec.t);
            vec3 outward_normal = (rec.p - center) / radius;
            rec.set_face_normal(r, outward_normal);
            return true;
        }
    }

    return false;
}


#endif