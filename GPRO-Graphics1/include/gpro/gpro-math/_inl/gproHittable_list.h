//Code from Peter Shirley(https://raytracing.github.io/books/RayTracingInOneWeekend.html#outputanimage/addingaprogressindicator)
//Edited by Jason  Kmieciak
#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include <memory>
#include <vector>
#include <gpro\gpro-math\_inl\gproRay.h>
#include <gpro\gpro-math\_inl\gproHittable.h>

using std::shared_ptr;
using std::make_shared;

class hittable_list : public hittable { // class of hittables list
public:
    hittable_list() {}
    hittable_list(shared_ptr<hittable> object) { add(object); }

    void clear() { objects.clear(); }
    void add(shared_ptr<hittable> object) { objects.push_back(object); }

    virtual bool hit(
        const ray& r, float tmin, float tmax, hit_record& rec) const override;

public:
    std::vector<shared_ptr<hittable>> objects;
};

bool hittable_list::hit(const ray& r, float t_min, float t_max, hit_record& rec) const {//stores the list of hittables that the ray comes in contact with
    hit_record temp_rec;
    bool hit_anything = false;
    auto closest_so_far = t_max;

    for (const auto& object : objects) {
        if (object->hit(r, t_min, closest_so_far, temp_rec)) {
            hit_anything = true;
            closest_so_far = temp_rec.t;
            rec = temp_rec;
        }
    }

    return hit_anything;
}

#endif