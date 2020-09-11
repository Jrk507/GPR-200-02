#ifndef RTWEEKEND_H
#define RTWEEKEND_H

#include <cmath>
#include <cstdlib>
#include <limits>
#include <memory>

//class used for setting constants needed for further ray tracing
// Usings

using std::shared_ptr;
using std::make_shared;
using std::sqrt;

// Constants

const float infinity = std::numeric_limits<float>::infinity();//sets the constant of infinity
const float pi = (float)3.1415926535897932385;//sets the constant of pi

// Utility Functions

inline float degrees_to_radians(float degrees) {
    return degrees * pi / (float)180.0;
}

// Common Headers

#include "gpro/gpro-math/gproVector.h"
#include <gpro\gpro-math\_inl\gproRay.h>

#endif