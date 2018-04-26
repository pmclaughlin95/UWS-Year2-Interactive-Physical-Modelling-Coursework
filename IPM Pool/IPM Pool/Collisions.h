/*

Name:Paul McLaughlin

Student ID:B00268411

I declare that the following code was produced by Alistair Buchanan, Paul McLaughlin, Jack Wayne as a group assignment for the IPM module and that this is our own work.

I am aware of the penalties incurred by submitting in full or in part work that is not our own and that was developed by third parties that are not appropriately acknowledged.

*/
#pragma once
#include <glm.hpp>
#include "Ball.h"
#include "Box.h"
#include <math.h>
#include <iostream>
#include <gtx\transform.hpp>
using namespace glm;
class Collisions {
public:
	bool Collisions_Detect_Circles(Ball* ball1, Ball* ball2, GLfloat dt);
	bool Collisions_Detect_Circle_Box(Ball* ball, Box* box);
	bool Collisions_Detect_Circle_Pocket(Ball* ball, Ball* pocket, GLfloat dt);//same as detect circles but pocket radius is 0
	void Collisions_React_Circles(Ball* ball1, Ball* ball2, GLfloat dt);
	void Collisions_React_Circle_Line(Ball* ball, Box* box);
	void Collisions_React_Circle_Pocket(Ball* ball);
private:
};
