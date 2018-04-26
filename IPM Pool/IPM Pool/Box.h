/*

Name:Paul McLaughlin

Student ID:B00268411

I declare that the following code was produced by Alistair Buchanan, Paul McLaughlin, Jack Wayne as a group assignment for the IPM module and that this is our own work.

I am aware of the penalties incurred by submitting in full or in part work that is not our own and that was developed by third parties that are not appropriately acknowledged.

*/
#pragma once
#include <glm.hpp>
#include <gl/glut.h>
using namespace glm;
class Box
{
public:
	Box(vec2 iposition, vec2 idimensions, bool isTop) { position = iposition; dimensions = idimensions; top = isTop; }
	void Draw() {
		glColor3f(0.5f, 0.35f, 0.05f);
		glBegin(GL_POLYGON);
		glVertex2f(position.x, position.y);
		glVertex2f(position.x + dimensions.x, position.y);
		glVertex2f(position.x + dimensions.x, position.y + dimensions.y);
		glVertex2f(position.x, position.y + dimensions.y);
		glEnd();
	};
	vec2 getPosition() { return position; }
	vec2 getDimensions() { return dimensions; }
	bool top;
private:
	vec2 position, dimensions;
};

