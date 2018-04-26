/*

Name:Paul McLaughlin

Student ID:B00268411

I declare that the following code was produced by Alistair Buchanan, Paul McLaughlin, Jack Wayne as a group assignment for the IPM module and that this is our own work.

I am aware of the penalties incurred by submitting in full or in part work that is not our own and that was developed by third parties that are not appropriately acknowledged.

*/
#pragma once
#include "Ball.h"
#include <glm.hpp>
#include "Box.h"
class Table
{
public:
	Table(vec2 windowDimensions, int pocketDiameter);
	virtual ~Table();
	void Draw();
	Box *topBox;
	Box *bottomBox;
	Box *leftTopBox;
	Box *leftBottomBox;
	Box *rightTopBox;
	Box *rightBottomBox;//the 6 cushions	
};

