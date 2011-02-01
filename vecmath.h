/*
 * math.h
 *
 *	Dot product
 *	Cross product
 *	Vector Addition
 *	Vector Subtraction
 *	Vector Scaling (vector*scalar)
 *	Vector Copy (Copy one vector into another)
 *	Vector Clear (zero each component)
 *	Vector Inverse (flip the sign of each component)
 *	Vector Magnitude (determine the length of a vector)
 *	Vector Normalize (make a vector unit length)
 *
 *  Created on: Jan 19, 2011
 *      Author: Allison Nelson
 */

#ifndef MATH_H_
#define MATH_H_

//Vector typedefs
typedef float vec_t;
typedef vec_t vec2_t[2];
typedef vec_t vec3_t[3];
typedef vec_t vec4_t[4];
typedef vec_t vec5_t[5];

//declare some vectors vec3_t vec1, vec2, vec3;
//assign X component vec1[0] = 1.0;
//assign Y component vec1[1] = 1.0;
//assign Z component vec1[2] = 1.0;

//adds two vectors
#define VectorAdd(v1, v2, out)\
		{\
			out[0] = v1[0]+v2[0];\
			out[1] = v1[1]+v2[1];\
			out[2] = v1[2]+v2[2];\
		}

//subtracts two vectors
#define VectorSubtract(v1, v2, out)\
		{\
			out[0] = v2[0]-v1[0];\
			out[1] = v2[1]-v1[1];\
			out[2] = v2[2]-v1[2];\
		}

//multiplies a vector by a scalar
#define VectorScale(v1, scale, out)\
		{\
			out[0] = scale*v1[0];\
			out[1] = scale*v1[1];\
			out[2] = scale*v1[2];\
		}

//takes the inverse of a vector
#define VectorInverse(v1)\
		{\
			v1[0] = -1*(v1[0]);\
			v1[1] = -1*(v1[1]);\
			v1[2] = -1*(v1[2]);\
		}

//copys one vector to another
#define VectorCopy(v1,out)\
		{\
			out[0] = v1[0];\
			out[1] = v1[1];\
			out[2] = out[2];\
		}

//finds the dot product of two vectors
#define DotProduct(v1, v2, out)\
		{\
			out = (v1[0]*v2[0])+(v1[1]*v2[1])+(v1[2]*v2[2]);\
		}

//clears each component of a vector
#define VectorClear(v1)\
		{\
			v1[0] = 0;\
			v1[1] = 0;\
			v1[2] = 0;\
		}

//finds the magnitude of a vector - implementation can be found in math.c
double VectorMagnitude(vec3_t v1);

//normalizes a vector
#define VectorNormalize(v1,magn,out)\
		{\
			out[0] = v1[0]/magn;\
			out[1] = v1[1]/magn;\
			out[2] = v1[2]/magn;\
		}

#endif /* MATH_H_ */
