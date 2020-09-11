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
	gproVector.h
	Interface for vectors. Sets an example for C and C++ compatible headers.

	Modified by: ____________
	Modified because: ____________
*/

#ifndef _GPRO_VECTOR_H_
#define _GPRO_VECTOR_H_

/*
#ifdef __cplusplus
// DB: link C++ symbols as if they are C where possible
extern "C" {
#else	// !__cplusplus
// DB: forward declare C types... why?
//	-> in C++ you would instantiate one of these like so: 
//		vec3 someVector;
//	-> in C you do it like this: 
//		union vec3 someVector;
//	-> this forward declaration makes the first way possible in both languages!
typedef union vec3 vec3;
#endif	// __cplusplus


// DB: declare shorthand types

typedef float float3[3];		// 3 floats form the basis of a float vector
typedef float* floatv;			// generic float vector (pointer)
typedef float const* floatkv;	// generic constant float vector (pointer)


// DB: declare 3D vector
//	-> why union? all data in the union uses the same address... in this case: 
//		'v' and 'struct...' share the same address
//	-> this means you can have multiple names for the same stuff!

// vec3
//	A 3D vector data structure.
//		member v: array (pointer) version of data
//		members x, y, z: named components of vector
union vec3
{
	float3 v;
	struct { float x, y, z; };

#ifdef __cplusplus
	// DB: in C++ we can have convenient member functions
	//	-> e.g. constructors, operators

	explicit vec3();	// default ctor
	explicit vec3(float const xc, float const yc = 0.0f, float const zc = 0.0f);	// init ctor w one or more floats
	explicit vec3(float3 const vc);	// copy ctor w generic array of floats
	vec3(vec3 const& rh);	// copy ctor

	vec3& operator =(vec3 const& rh);	// assignment operator (copy other to this)

	vec3& operator +=(vec3 const& rh);	// addition assignment operator (add other to this)

	vec3 const operator +(vec3 const& rh) const;	// addition operator (get sum of this and another)

#endif	// __cplusplus
};


// DB: declare C functions (all equivalents of above C++ functions are here)
//	-> return pointers so you can chain operations (they just take pointers)

floatv vec3default(float3 v_out);	// default init
floatv vec3init(float3 v_out, float const xc, float const yc, float const zc);	// init w floats
floatv vec3copy(float3 v_out, float3 const v_rh);	// init w array of floats (same as assign and both copy ctors)

floatv vec3add(float3 v_lh_sum, float3 const v_rh);	// add other to lh vector

floatv vec3sum(float3 v_sum, float3 const v_lh, float3 const v_rh);	// get sum of lh and rh vector


#ifdef __cplusplus
// DB: end C linkage for C++ symbols
}
#endif	// __cplusplus


// DB: include inline definitions for this interface
#include "_inl/gproVector.inl"


#endif	// !_GPRO_VECTOR_H_
*/
#include <cmath>
#include <iostream>



//Code from Peter Shirley(https://raytracing.github.io/books/RayTracingInOneWeekend.html#outputanimage/addingaprogressindicator)
//Code from Daniel S. Buckstein
//Edited by Jason  Kmieciak

using std::sqrt;
// this class is ued to store colors,locations, directions, offsets in a single class for use
class vec3 {
public:
    vec3() : e{ 0,0,0 } {}//sets the class to have three variables 
    vec3(float e0, float e1, float e2) : e{ e0, e1, e2 } {}//sets the variables to be floats
	//constructor
    float x() const { return e[0]; }
    float y() const { return e[1]; }
    float z() const { return e[2]; }
	//operator overloads
    vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }
    float operator[](int i) const { return e[i]; }
    float& operator[](int i) { return e[i]; }

    vec3& operator+=(const vec3& v) {// add equal operator overload
        e[0] += v.e[0];
        e[1] += v.e[1];
        e[2] += v.e[2];
        return *this;
    }

    vec3& operator*=(const float t) {//pointer = operator overload
        e[0] *= t;
        e[1] *= t;
        e[2] *= t;
        return *this;
    }

    vec3& operator/=(const float t) {//divide and equal operator overload
        return *this *= 1 / t;
    }

    float length() const {//length of variables setr in class
        return sqrt(length_squared());
    }

    float length_squared() const {//square root of variables set in class
        return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
    }

public:
    float e[3];//seting a fourth changable variable for vec3 class
};

// Type aliases for vec3
using point3 = vec3;   // 3D point
using color = vec3;    // RGB color
//inline functions for vec3 class 
inline std::ostream& operator<<(std::ostream& out, const vec3& v) {
	return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

inline vec3 operator+(const vec3& u, const vec3& v) {
	return vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

inline vec3 operator-(const vec3& u, const vec3& v) {
	return vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

inline vec3 operator*(const vec3& u, const vec3& v) {
	return vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

inline vec3 operator*(float t, const vec3& v) {
	return vec3(t * v.e[0], t * v.e[1], t * v.e[2]);
}

inline vec3 operator*(const vec3& v, float t) {
	return t * v;
}

inline vec3 operator/(vec3 v, float t) {
	return (1 / t) * v;
}

inline float dot(const vec3& u, const vec3& v) {
	return u.e[0] * v.e[0]
		+ u.e[1] * v.e[1]
		+ u.e[2] * v.e[2];
}

inline vec3 cross(const vec3& u, const vec3& v) {
	return vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
		u.e[2] * v.e[0] - u.e[0] * v.e[2],
		u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

inline vec3 unit_vector(vec3 v) {
	return v / v.length();
}
#endif	// !_GPRO_VECTOR_H_