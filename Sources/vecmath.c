/*
 * vecmath.c
 *
 *  Created on: Jan 19, 2011
 *      Author: Allison Nelson
 */

#include "vecmath.h"
#include <stdio.h>
#include <math.h>

double vectorMagnitude(vec3_t v1)
{
	 return sqrt((v1[0]*v1[0])+(v1[1]*v1[1])+(v1[2]*v1[2]));
}

int main()
{
	printf("Vector Math Library Testing.\n");
	vec3_t v1 = {1.0,2.0,3.0};
	vec3_t v2 = {4.0,5.0,6.0};
	vec3_t output = {0.0,0.0,0.0};
	double result;
	VectorAdd(v1,v2,output);
	printf("v1+v2=%5.2f %5.2f %5.2f\n",output[0],output[1],output[2]);
	VectorSubtract(v1,v2,output);
	printf("v1-v2=%5.2f %5.2f %5.2f\n",output[0],output[1],output[2]);
	DotProduct(v1,v2,result);
	printf("v1 dot v2=%5.2f\n",result);
	result = vectorMagnitude(v1);
	printf("v1 magnitude=%5.2f\n",result);
	VectorNormalize(v1,result,output);
	printf("v1 normalized=%5.2f %5.2f %5.2f\n",output[0],output[1],output[2]);
	VectorCopy(v1,output);
	printf("v1 copied to output=%5.2f %5.2f %5.2f\n",output[0],output[1],output[2]);
	VectorScale(v1,5,output);
	printf("v1*5=%5.2f %5.2f %5.2f\n",output[0],output[1],output[2]);
	VectorInverse(v1);
	printf("v1 inverse=%5.2f %5.2f %5.2f\n",v1[0],v1[1],v1[2]);
	VectorClear(v1);
	printf("v1 clear=%5.2f %5.2f %5.2f\n",v1[0],v1[1],v1[2]);
	return 0;

}


