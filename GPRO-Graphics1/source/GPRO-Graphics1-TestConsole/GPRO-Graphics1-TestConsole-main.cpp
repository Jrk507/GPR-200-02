/*
   Copyright 2020 Daniel S. Buckstein

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

/*
	GPRO-Graphics1-TestConsole-main.c/.cpp
	Main entry point source file for a Windows console application.

	Modified by: ____________
	Modified because: ____________
*/


#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <ostream>
#include <fstream>
#include "gpro/gpro-math/gproVector.h"
#include "../../project/VisualStudio/GPRO-Graphics1-TestConsole/Color.h"
#include <gpro\gpro-math\_inl\gproRay.h>

using namespace std;


/*
void testVector()
{
	// test array vector initializers and functions
	float3 av, bv, cv, dv;
	vec3default(av);								// -> a = (0, 0, 0)
	vec3init(bv, 1.0f, 2.0f, 3.0f);					// -> b = (1, 2, 3)
	vec3copy(dv, vec3init(cv, 4.0f, 5.0f, 6.0f));	// -> d = c = (4, 5, 6)
	vec3copy(av, dv);								// a = d			-> a = (4, 5, 6)
	vec3add(dv, bv);								// d += b			-> d = (4 + 1, 5 + 2, 6 + 3) = (5, 7, 9)
	vec3sum(dv, bv, bv);							// d = b + b		-> d = (1 + 1, 2 + 2, 3 + 3) = (2, 4, 6)
	vec3add(vec3sum(dv, cv, bv), av);				// d = c + b + a	-> d = (4 + 1 + 4, 5 + 2 + 5, 6 + 3 + 6) = (9, 12, 15)

#ifdef __cplusplus
	// test all constructors and operators
	vec3 a, b(1.0f, 2.0f, 3.0f), c(cv), d(c);		// default; init; copy array; copy
	a = d;											// assign						-> a = (4, 5, 6)
	d += b;											// add assign					-> d = (5, 7, 9)
	d = b + b;										// sum, init, assign			-> d = (2, 4, 6)
	d = c + b + a;									// sum, init, sum, init, assign	-> d = (9, 12, 15)
#endif	// __cplusplus
}
*/
float hit_sphere(const point3& center, float radius, const ray& r) {//colors the sphere we set in the image that is hit by the ray and colored with surface normals
	vec3 oc = r.origin() - center;
	float a = r.direction().length_squared();
	float half_b = dot(oc, r.direction());
	float c = oc.length_squared() - radius * radius;
	float discriminant = half_b * half_b - a * c;

	if (discriminant < 0) {
		return -1.0;
	}
	else {
		return (-half_b - sqrt(discriminant)) / a;
	}
}

color ray_color(const ray& r) {//the implementation of the ray class
	float t = hit_sphere(point3(0, 0, -1), (float)0.5, r);//when the ray his the sphere
	if (t > 0.0) {//sets the color for each hit
		vec3 N = unit_vector(r.at(t) - vec3(0, 0, -1));
		return 0.5 * color(N.x() + 1, N.y() + 1, N.z() + 1);
	}
	vec3 unit_direction = unit_vector(r.direction());
	t = (float)0.5 * (unit_direction.y() + (float)1.0);
	return (float)(1.0 - t) * color((float)1.0, (float)1.0, (float)1.0) + t * color((float)0.5, (float)0.7, (float)1.0);
}

int main(int const argc, char const* const argv[])
{
	//Image

	const float aspect_ratio = (float)16.0 / (float)9.0;//ratio of width and height of the image being viewed
	const int image_width = 400;//width of image 
	const int image_height = static_cast<int>(image_width / aspect_ratio);//the height of the image 
	
	// Camera(sets the viewpoint of the image in the ppm file)

	float viewport_height = 2.0;
	float viewport_width = aspect_ratio * viewport_height; 
	float focal_length = 1.0;

	vec3 origin = point3(0, 0, 0);//position of the origin in the picture
	vec3 horizontal = vec3(viewport_width, 0, 0);//horizontal position of the camera to the image
	vec3 vertical = vec3(0, viewport_height, 0);//vertical postion of the camera of the image
	vec3 lower_left_corner = origin - horizontal / 2 - vertical / 2 - vec3(0, 0, focal_length);//sets the lower corner postion for the vectors to use

	//testVector();
	ofstream img("image.ppm");	//the image created by this program


	img << "P3\n" << image_width << ' ' << image_height << "\n255\n";//size of the image
	
	for (int j = image_height - 1; j >= 0; --j) {//used to run through the image 
		for (int i = 0; i < image_width; ++i) {
			float u = float(i) / (image_width - 1);//runs through the image on the x-axis
			float v = float(j) / (image_height - 1);//runs through the image on the y-axis
			ray r(origin, lower_left_corner + u * horizontal + v * vertical - origin);//sends rays into the screen at each pixel
			color pixel_color = ray_color(r);//sets the pixels the ray reads to specific colors
			write_color(img, pixel_color);//prints the color to the image
		}
	}

	img << "\nDone.\n";


	printf("\n\n");
	system("pause");
}
