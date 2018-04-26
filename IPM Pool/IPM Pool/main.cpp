/*

Name:Paul McLaughlin

Student ID:B00268411

I declare that the following code was produced by Alistair Buchanan, Paul McLaughlin, Jack Wayne as a group assignment for the IPM module and that this is our own work.

I am aware of the penalties incurred by submitting in full or in part work that is not our own and that was developed by third parties that are not appropriately acknowledged.

*/
#include <gl/glut.h>
#include "Ball.h"
#include <ctime>
#include <time.h>
#include <iostream>
#include <array>
#include <sstream>
#include "Table.h"
#include "Collisions.h"
using namespace glm;

bool leftDown, rightDown, middleDown, playing = true;
const int WINDOWWIDTH = 400, WINDOWHEIGHT = 800;
int mouse_x, mouse_y, power;//don't use unsigned integers for this. Ever.
GLfloat dt;
vec3 cueStartPos;
vec3 ballColour;
Ball *cueball; //mass is given in grams. cueball is ballMass, other balls are ballMass
Ball *redBalls[7];
Ball *yellowBalls[7];
Ball *blackBall;
Ball *pockets[6];
vec3 forceIntoBall;//temporary variable to check if movement is working
time_t oldTime, newTime;
Table *table;
vec3 direction;
Collisions collisions;
void Init() {	
	GLfloat cueballMass = 170, ballMass = 160;
	power = 0;
	int radius = 15, pocketRadius = 20;
	table = new Table(vec2(WINDOWWIDTH-8, WINDOWHEIGHT), pocketRadius * 2);
	cueStartPos = vec3(GLfloat(WINDOWWIDTH / 2)-4, GLfloat(WINDOWHEIGHT / 4), 1.0f);
	vec3 blackStartPos = vec3(GLfloat(WINDOWWIDTH / 2)-4, GLfloat((WINDOWHEIGHT / 4) * 3), 1.0f);
	vec3 colour_Red(1, 0, 0);
	vec3 colour_Yellow(0, 0, 1);//changed to blue to see easier, make 1,1,0 for yellow
	vec3 colour_Black(0);
	GLfloat temp = sqrt(((radius * 2)*(radius * 2)) - radius*radius);
	//offsets are built in to avoid touching which will cause collision reaction checks.
	//please don't touch this.
	cueball = new Ball(cueStartPos, radius, cueballMass, vec3(1.0, 1.0, 1.0));
	redBalls[0] = new Ball(vec3(blackStartPos.x - (radius * 2) - 1, blackStartPos.y, 1), radius, ballMass, vec3(1.0, 0, 0));
	redBalls[1] = new Ball(vec3(blackStartPos.x + (radius * 2) + 1, blackStartPos.y, 1), radius, ballMass, colour_Red);
	redBalls[2] = new Ball(vec3(blackStartPos.x, blackStartPos.y - sqrt(((radius * 4)*(radius * 4)) - ((radius * 2)*(radius * 2))) - 2, 1), radius, ballMass, colour_Red);
	redBalls[3] = new Ball(vec3(blackStartPos.x - radius - 1, blackStartPos.y + sqrt(((radius * 2)*(radius * 2)) - radius*radius) + 1, 1), radius, ballMass, colour_Red);//work out the ball y using pythagoras knowing that it must be 2*the balls radius away to be touching and is one radius away on the x axis we make a right angled triangle and work out the y distance using it
	redBalls[4] = new Ball(vec3(blackStartPos.x, blackStartPos.y + sqrt(((radius * 4)*(radius * 4)) - ((radius * 2)*(radius * 2))) + 1, 1), radius, ballMass, colour_Red);
	redBalls[5] = new Ball(vec3(blackStartPos.x + radius * 4 + 2, blackStartPos.y + sqrt(((radius * 4)*(radius * 4)) - ((radius * 2)*(radius * 2))) + 2, 1), radius, ballMass, colour_Red);
	redBalls[6] = new Ball(vec3(blackStartPos.x - radius * 4 - 2, blackStartPos.y + sqrt(((radius * 4)*(radius * 4)) - ((radius * 2)*(radius * 2))) + 2, 1), radius, ballMass, colour_Red);

	yellowBalls[0] = new Ball(vec3(blackStartPos.x - radius - 1, blackStartPos.y - sqrt(((radius * 2)*(radius * 2)) - radius*radius) - 1, 1), radius, ballMass, colour_Yellow);
	yellowBalls[1] = new Ball(vec3(blackStartPos.x + radius + 1, blackStartPos.y - sqrt(((radius * 2)*(radius * 2)) - radius*radius) - 1, 1), radius, ballMass, colour_Yellow);
	yellowBalls[2] = new Ball(vec3(blackStartPos.x + radius + 1, blackStartPos.y + sqrt(((radius * 2)*(radius * 2)) - radius*radius) + 1, 1), radius, ballMass, colour_Yellow);
	yellowBalls[3] = new Ball(vec3(blackStartPos.x - radius * 3 - 2, blackStartPos.y + sqrt(((radius * 2)*(radius * 2)) - radius*radius) + 1, 1), radius, ballMass, colour_Yellow);
	yellowBalls[4] = new Ball(vec3(blackStartPos.x + radius * 3 + 2, blackStartPos.y + sqrt(((radius * 2)*(radius * 2)) - radius*radius) + 1, 1), radius, ballMass, colour_Yellow);
	yellowBalls[5] = new Ball(vec3(blackStartPos.x - radius * 2 - 1, blackStartPos.y + sqrt(((radius * 4)*(radius * 4)) - ((radius * 2)*(radius * 2))) + 2, 1), radius, ballMass, colour_Yellow);
	yellowBalls[6] = new Ball(vec3(blackStartPos.x + radius * 2 + 1, blackStartPos.y + sqrt(((radius * 4)*(radius * 4)) - ((radius * 2)*(radius * 2))) + 2, 1), radius, ballMass, colour_Yellow);

	blackBall = new Ball(blackStartPos, radius, ballMass, colour_Black);

	pockets[0] = new Ball(vec3(pocketRadius, pocketRadius, 1), pocketRadius, 0, colour_Black);//bottom left
	pockets[1] = new Ball(vec3(pocketRadius/2, WINDOWHEIGHT/2-4, 1), pocketRadius, 0, colour_Black);//middle left
	pockets[2] = new Ball(vec3((WINDOWWIDTH - pocketRadius-8), pocketRadius, 1), pocketRadius, 0, colour_Black);//bottom right
	pockets[3] = new Ball(vec3((WINDOWWIDTH - pocketRadius/2-8), WINDOWHEIGHT / 2-4, 1), pocketRadius, 0, colour_Black);//middle right
	pockets[4] = new Ball(vec3(pocketRadius, WINDOWHEIGHT - pocketRadius-8, 1), pocketRadius, 0, colour_Black);//top left
	pockets[5] = new Ball(vec3((WINDOWWIDTH - pocketRadius - 8), WINDOWHEIGHT - pocketRadius - 8, 1), pocketRadius, 0, colour_Black);//top right
}

void My_mouse_routine(int x, int y)
{
	mouse_x = x;
	mouse_y = -(y- WINDOWHEIGHT);
}

void Reset() {//reset doesn't reset the balls cos I can't be arsed
	power = 0;
	cueball->setPosition(cueStartPos);
	cueball->setVelocity(vec3(0));
	cueball->pocketed = false;
	forceIntoBall = vec3(0);
	cueball->isMoving = false;
}

void KeyPress(unsigned char key, int x, int y) {
	switch (key)
	{
		case 'r':
			Reset();
			break;
		case 's':
			power = 100;
			break;
		case 27:
			exit(0);
		case 32:
			if (!rightDown&&!leftDown)
			{				
				direction = normalize(vec3((-mouse_x + cueball->getPosition().x), -(mouse_y - cueball->getPosition().y), 1));
				//std::cout << direction.x << std::endl;
				//std::cout << direction.y << std::endl;

				forceIntoBall = (power / 1000.0f) * direction;
				cueball->setForce(forceIntoBall);
				power = 0;
 			}
			break;
		default:
			break;
	}
}

void Mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)leftDown = (state == GLUT_DOWN);
	if (button == GLUT_RIGHT_BUTTON)rightDown = (state == GLUT_DOWN);
	if (button == GLUT_MIDDLE_BUTTON)middleDown = (state == GLUT_DOWN);
	glutPassiveMotionFunc(My_mouse_routine);	

}

void PowerInput()
{
	if (leftDown&&power<100&&!rightDown)power += 1;
 	if (rightDown&&power>0&&!leftDown) power-= 1;
	if (middleDown)Reset();
}

void DrawString(void *font, float x, float y, const char *str)		// Draws strings onto the OpenGL screen
{
	char *ch;
	glRasterPos3f(x, y, 0.0);
	for (ch = (char*)str; *ch; ch++)
		glutBitmapCharacter(font, (int)*ch);
}

std::string IntToStr(int n)				//Converts integers to strings
{
	std::ostringstream result;
	result << n;
	return result.str();
}

void Display() {

	glClear(GL_COLOR_BUFFER_BIT);
	
	for (size_t i = 0; i < 7; i++)
	{
		redBalls[i]->Draw();
		yellowBalls[i]->Draw();
	}
	table->Draw();
	for (size_t i = 0; i < 6; i++)pockets[i]->Draw();
	cueball->Draw();
	blackBall->Draw();
 	std::string powerString = IntToStr(power);
	glColor3f(0.0, 0.0, 0.0);
	DrawString(GLUT_BITMAP_8_BY_13, 20, 50, "power: ");
	DrawString(GLUT_BITMAP_8_BY_13, 75, 50, powerString.c_str());
	glutSwapBuffers();
	glFlush();
	
}

void GetDt() {
	newTime = glutGet(GLUT_ELAPSED_TIME);
	dt = newTime - oldTime;
	oldTime = newTime;
}
void CollisionDetection() {
	for (size_t i = 0; i < 7; i++)
	{
		for (size_t j = 0; j < 7; j++)
		{
			if (i != j)
			{
				collisions.Collisions_Detect_Circles(redBalls[i], redBalls[j], dt);
				collisions.Collisions_Detect_Circles(yellowBalls[i], yellowBalls[j], dt);
			}
			collisions.Collisions_Detect_Circles(cueball, redBalls[i], dt);
			collisions.Collisions_Detect_Circles(cueball, yellowBalls[i], dt);
			collisions.Collisions_Detect_Circles(blackBall, redBalls[i], dt);
			collisions.Collisions_Detect_Circles(blackBall, yellowBalls[i], dt);
			collisions.Collisions_Detect_Circle_Box(redBalls[i], table->bottomBox);
			collisions.Collisions_Detect_Circle_Box(redBalls[i], table->topBox);
			collisions.Collisions_Detect_Circle_Box(redBalls[i], table->leftTopBox);
			collisions.Collisions_Detect_Circle_Box(redBalls[i], table->leftBottomBox);
			collisions.Collisions_Detect_Circle_Box(redBalls[i], table->rightBottomBox);
			collisions.Collisions_Detect_Circle_Box(redBalls[i], table->rightTopBox);
			collisions.Collisions_Detect_Circle_Box(yellowBalls[i], table->bottomBox);
			collisions.Collisions_Detect_Circle_Box(yellowBalls[i], table->topBox);
			collisions.Collisions_Detect_Circle_Box(yellowBalls[i], table->leftTopBox);
			collisions.Collisions_Detect_Circle_Box(yellowBalls[i], table->leftBottomBox);
			collisions.Collisions_Detect_Circle_Box(yellowBalls[i], table->rightBottomBox);
			collisions.Collisions_Detect_Circle_Box(yellowBalls[i], table->rightTopBox);

			collisions.Collisions_Detect_Circles(redBalls[i], yellowBalls[j], dt);

		}
	}
	for (size_t i = 0; i < 6; i++)
	{
		collisions.Collisions_Detect_Circle_Pocket(cueball, pockets[i], dt);
		collisions.Collisions_Detect_Circle_Pocket(blackBall, pockets[i], dt);
		for (size_t j = 0; j < 7; j++)
		{
			collisions.Collisions_Detect_Circle_Pocket(redBalls[j], pockets[i], dt);
			collisions.Collisions_Detect_Circle_Pocket(yellowBalls[j], pockets[i], dt);
		}
	}
	collisions.Collisions_Detect_Circle_Box(cueball, table->bottomBox);
	collisions.Collisions_Detect_Circle_Box(cueball, table->topBox);
	collisions.Collisions_Detect_Circle_Box(cueball, table->leftTopBox);
	collisions.Collisions_Detect_Circle_Box(cueball, table->leftBottomBox);
	collisions.Collisions_Detect_Circle_Box(cueball, table->rightBottomBox);
	collisions.Collisions_Detect_Circle_Box(cueball, table->rightTopBox);

	collisions.Collisions_Detect_Circle_Box(blackBall, table->bottomBox);
	collisions.Collisions_Detect_Circle_Box(blackBall, table->topBox);
	collisions.Collisions_Detect_Circle_Box(blackBall, table->leftTopBox);
	collisions.Collisions_Detect_Circle_Box(blackBall, table->leftBottomBox);
	collisions.Collisions_Detect_Circle_Box(blackBall, table->rightBottomBox);
	collisions.Collisions_Detect_Circle_Box(blackBall, table->rightTopBox);
	collisions.Collisions_Detect_Circles(cueball, blackBall, dt);
}
void Update() {
	if (playing)
	{
		Display();
		GetDt();
		PowerInput();
		cueball->setVelocity(cueball->getVelocity() += forceIntoBall);
		forceIntoBall = vec3(0);
		CollisionDetection();
		for (size_t i = 0; i < 7; i++)
		{
			redBalls[i]->Update(dt);
			yellowBalls[i]->Update(dt);
		}
		cueball->Update(dt);
		blackBall->Update(dt);
		
	}
}

void Timer(int value) {
	Update();
	glutTimerFunc(0, Timer, 0);
}

int main(int argc, char **argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(WINDOWWIDTH, WINDOWHEIGHT);
	glViewport(0, 0, WINDOWWIDTH, WINDOWHEIGHT);
	glutCreateWindow("Pool");
	gluOrtho2D(0, WINDOWWIDTH, 0, WINDOWHEIGHT);
	glClearColor(0.2, 1.0, 0.4, 1.0);
	Init();
	glutDisplayFunc(Display);
	glutTimerFunc(0, Timer, 0);
	glutIdleFunc(Display);
	glutKeyboardFunc(KeyPress);
	glutMouseFunc(Mouse);
	glutMainLoop();
	return 0;
}