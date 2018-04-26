/*

Name:Paul McLaughlin

Student ID:B00268411

I declare that the following code was produced by Alistair Buchanan, Paul McLaughlin, Jack Wayne as a group assignment for the IPM module and that this is our own work.

I am aware of the penalties incurred by submitting in full or in part work that is not our own and that was developed by third parties that are not appropriately acknowledged.

*/
#include "Table.h"

Table::Table(vec2 windowDimensions, int pocketDiameter)
{
	topBox = new Box(vec2(pocketDiameter, windowDimensions.y - 0.5*pocketDiameter-8), vec2(windowDimensions.x - (pocketDiameter * 2), 0.5*pocketDiameter), true);
	bottomBox = new Box(vec2(pocketDiameter,0), vec2(windowDimensions.x - (pocketDiameter * 2), 0.5*pocketDiameter), true);
	leftTopBox = new Box(vec2(0, windowDimensions.y/2+pocketDiameter/2-4), vec2(0.5*pocketDiameter,0.5*windowDimensions.y-(pocketDiameter*2)+17), false);
	leftBottomBox = new Box(vec2(0, pocketDiameter), vec2(0.5*pocketDiameter, 0.5*windowDimensions.y - (pocketDiameter*2)+16), false);
	rightTopBox = new Box(vec2(windowDimensions.x-pocketDiameter/2, windowDimensions.y / 2 + pocketDiameter / 2 - 4), vec2(0.5*pocketDiameter, 0.5*windowDimensions.y - (pocketDiameter * 2) + 17), false);
	rightBottomBox = new Box(vec2(windowDimensions.x - pocketDiameter / 2,pocketDiameter), vec2(0.5*pocketDiameter, 0.5*windowDimensions.y - (pocketDiameter * 2) + 16), false);
}

Table::~Table(){}
void Table::Draw() {
	topBox->Draw();
	bottomBox->Draw();
	leftTopBox->Draw();
	leftBottomBox->Draw();
	rightTopBox->Draw();
	rightBottomBox->Draw();
}
