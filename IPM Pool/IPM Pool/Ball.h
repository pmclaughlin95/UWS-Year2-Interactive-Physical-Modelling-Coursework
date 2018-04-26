/*

Name:Paul McLaughlin

Student ID:B00268411

I declare that the following code was produced by Alistair Buchanan, Paul McLaughlin, Jack Wayne as a group assignment for the IPM module and that this is our own work.

I am aware of the penalties incurred by submitting in full or in part work that is not our own and that was developed by third parties that are not appropriately acknowledged.

*/
#pragma once
#include <gl/glut.h>
#include <glm.hpp>
#include <cmath>
#define _USE_MATH_DEFINES
#include <math.h>
#include "Movement.h"
using namespace glm;

class Ball
{
public:
	Ball(vec3 iposition, int iradius, int imass, vec3 iballcolour) { position = iposition; radius = iradius; mass = imass; ballColour = iballcolour; }
	virtual ~Ball();
	void Draw();
	void Move(vec3 &direction);
  	void Update(float& dt);
	//getters and setters using camelCase to differentiate them from proper methods
	int getRadius() { return radius; }
	float getMass() { return mass; }
	vec3 getPosition() { return position; }
	void setPosition(vec3 iposition) { position = iposition; }
	void setAcceleration(vec3 iacceleration) { acceleration = iacceleration; }
	void setForce(vec3 iforce) { force = iforce; }
	vec3 getVelocity() { return velocity; }
	void setVelocity(vec3 ivelocity) { velocity = ivelocity; }
	bool isMoving = false;
	bool pocketed = false;
private:
	Movement movement;	
	int radius = 0;
	float mass = 0;
	vec3 force = vec3(0), position = vec3(0), acceleration = vec3(0), velocity = vec3(0) , ballColour = vec3(0);
	//float friction = 0.005f;//temporary, will need an actual equation at some point
	
};

