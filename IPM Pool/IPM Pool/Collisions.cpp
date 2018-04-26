
/*

Name:Paul McLaughlin

Student ID:B00268411

I declare that the following code was produced by Alistair Buchanan, Paul McLaughlin, Jack Wayne as a group assignment for the IPM module and that this is our own work.

I am aware of the penalties incurred by submitting in full or in part work that is not our own and that was developed by third parties that are not appropriately acknowledged.

*/#include "Collisions.h"

bool Collisions::Collisions_Detect_Circles(Ball* ball1, Ball* ball2, GLfloat dt) {//thanks to developer.mozilla.org/en-US/docs/Games/Techniques/2D_collision_detection for help with this
	vec3 ball1Pos = ball1->getPosition();
	vec3 ball2Pos = ball2->getPosition();
	vec2 dPos(ball1Pos.x - ball2Pos.x, ball1Pos.y - ball2Pos.y);
	GLfloat distance = sqrt((dPos.x * dPos.x + dPos.y * dPos.y));
	GLfloat radius = (ball1->getRadius() + ball2->getRadius());
	if (distance < radius)
	{
		Collisions_React_Circles(ball1, ball2, dt);
		std::cout << "BallCollide" << std::endl;
		return true;		
	}
	else return false;
}

bool Collisions::Collisions_Detect_Circle_Box(Ball* ball, Box* box) {//uses halfwidths and halfheights, stackoverflow was helpful here

	float ballx = abs(ball->getPosition().x - box->getPosition().x - (box->getDimensions().x/2));
	float distancex = (box->getDimensions().x / 2) + ball->getRadius();
	if (ballx > distancex)return false;
	float bally = abs(ball->getPosition().y - box->getPosition().y - (box->getDimensions().y / 2));
	float distancey = (box->getDimensions().y / 2) + ball->getRadius();
	if (bally > distancey)return false;
	if (ballx <= (box->getDimensions().x / 2) || bally <= (box->getDimensions().y / 2)) 
	{
		Collisions_React_Circle_Line(ball, box);
		std::cout << "BoxCollide" << std::endl;
		return true;
	}
	//float distancexCorner = ballx - (box->getDimensions().x / 2);
	//float distanceyCorner = bally - (box->getDimensions().y / 2);
	//float sqrDistancexCorner = distancexCorner * distancexCorner;
	//float sqrDistanceyCorner = distanceyCorner * distanceyCorner;
	//float sqrCornerDistanceMax = ball->getRadius() * ball->getRadius();
	//
	//return sqrDistancexCorner + sqrDistanceyCorner <= sqrCornerDistanceMax;
}

bool Collisions::Collisions_Detect_Circle_Pocket(Ball* ball, Ball* pocket, GLfloat dt) {//same as ball collision but only using the balls radius so it is pocketed when the ball is half way over the pocket
	vec3 ball1Pos = ball->getPosition();
	vec3 ball2Pos = pocket->getPosition();
	vec2 dPos(ball1Pos.x - ball2Pos.x, ball1Pos.y - ball2Pos.y);
	GLfloat distance = sqrt((dPos.x * dPos.x + dPos.y * dPos.y));
	if (distance < ball->getRadius())
	{
		Collisions_React_Circle_Pocket(ball);
		std::cout << "PocketCollide" << std::endl;
		return true;
	}
	else return false;
}

void Collisions::Collisions_React_Circles(Ball* ball1, Ball* ball2, GLfloat dt) {
	
	GLfloat ball1Mass=ball1->getMass(), ball2Mass= ball2->getMass();
	vec3 ball1Velocity = ball1->getVelocity(), ball2Velocity = ball2->getVelocity();

	GLfloat newxVelocityBall1 = ((ball1Velocity.x * (ball1Mass - ball2Mass) + (2 * ball2Mass * ball2Velocity.x)) / (ball1Mass + ball2Mass));
	GLfloat newyVelocityBall1 = ((ball1Velocity.y * (ball1Mass - ball2Mass) + (2 * ball2Mass * ball2Velocity.y)) / (ball1Mass + ball2Mass));
	ball1->setVelocity(vec3(newxVelocityBall1, newyVelocityBall1, 1));
	GLfloat newxVelocityBall2 = ((ball2Velocity.x * (ball2Mass - ball1Mass) + (2 * ball1Mass*ball1Velocity.x)) / (ball1Mass + ball2Mass));
	GLfloat newyVelocityBall2 = ((ball2Velocity.y * (ball2Mass - ball1Mass) + (2 * ball1Mass*ball1Velocity.y)) / (ball1Mass + ball2Mass));
	ball2->setVelocity(vec3(newxVelocityBall2, newyVelocityBall2, 1));
}

void Collisions::Collisions_React_Circle_Line(Ball* ball, Box* box) {//simple reversing of velocities. ran out of time to get it properly implemented
	if (box->top == false)
	{
		ball->setVelocity(vec3(-ball->getVelocity().x, -ball->getVelocity().y*-1, 1));
	}
	else if (box->top == true)
	{
		ball->setVelocity(vec3(-ball->getVelocity().x*-1, -ball->getVelocity().y, 1));
	}
	


}

void Collisions::Collisions_React_Circle_Pocket(Ball* ball) {
	ball->pocketed = true;
}