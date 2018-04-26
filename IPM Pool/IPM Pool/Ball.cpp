/*

Name:Paul McLaughlin

Student ID:B00268411

I declare that the following code was produced by Alistair Buchanan, Paul McLaughlin, Jack Wayne as a group assignment for the IPM module and that this is our own work.

I am aware of the penalties incurred by submitting in full or in part work that is not our own and that was developed by third parties that are not appropriately acknowledged.

*/
#include "Ball.h"

Ball::~Ball()
{
}
void Ball::Draw() {
	glBegin(GL_POLYGON);
		const int NPOINTS = 64;
		const float TWOPI = M_PI * 2;
		const float STEP = TWOPI / NPOINTS;
		glColor3f(float(ballColour.x),float(ballColour.y),float(ballColour.z));
		for (float angle = 0; angle < TWOPI; angle += STEP)
		{
			glVertex2f(position.x + radius*cos(angle), position.y + radius*sin(angle));
		}
	glEnd();
}
void Ball::Move(vec3 &velocityIn) {
	
}
 
void Ball::Update(float& dt) {

		
	if (pocketed!=true)
	{
		//movement.Euler(&dt, &velocity, &position, &acceleration);
		movement.Vertlet(&dt, &velocity, &position, &acceleration, &force, mass);
		
	}
	else {
		velocity = vec3(0);
		position = vec3(-1);
	}
		
		//velocity -= friction;

}