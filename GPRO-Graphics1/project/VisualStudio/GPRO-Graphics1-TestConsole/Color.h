//Code from Peter Shirley(https://raytracing.github.io/books/RayTracingInOneWeekend.html#outputanimage/addingaprogressindicator)
//Edited by Jason  Kmieciak
#ifndef COLOR_H
#define COLOR_H

#include "gpro/gpro-math/gproVector.h"

#include <iostream>

void write_color(std::ostream& out, color pixel_color) {
    // Write the translated [0,255] value of each color component.
    out << static_cast<int>(255.999 * pixel_color.x()) << ' '
        << static_cast<int>(255.999 * pixel_color.y()) << ' '
        << static_cast<int>(255.999 * pixel_color.z()) << '\n';
}

#endif