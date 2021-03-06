//Code from Peter Shirley(https://raytracing.github.io/books/RayTracingInOneWeekend.html#outputanimage/addingaprogressindicator)
//Edited by Jason  Kmieciak
#ifndef RAY_H
#define RAY_H

#include <gpro\gpro-math\gproVector.h>

class ray {//class for the P(t) that computes the color is seen along the ray
public:
    ray() {}
    ray(const point3& origin, const vec3& direction)
        : orig(origin), dir(direction)
    {}

    point3 origin() const { return orig; }
    vec3 direction() const { return dir; }

    point3 at(float t) const {
        return orig + t * dir;
    }

public:
    point3 orig;
    vec3 dir;
};

#endif

