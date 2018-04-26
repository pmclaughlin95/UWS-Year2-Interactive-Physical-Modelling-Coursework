/*

Name:Paul McLaughlin

Student ID:B00268411

I declare that the following code was produced by Alistair Buchanan, Paul McLaughlin, Jack Wayne as a group assignment for the IPM module and that this is our own work.

I am aware of the penalties incurred by submitting in full or in part work that is not our own and that was developed by third parties that are not appropriately acknowledged.

*/
#pragma once
#include <glm.hpp>
using namespace glm;
class Movement
{
public:
	void Euler(float *dt, vec3 *velocity, vec3 *position, vec3 *acceleration);
	void Vertlet(float *dt, vec3 *velocity, vec3 *position, vec3 *acceleration, vec3 *force, float mass);
};


