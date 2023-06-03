#include "Avatar.h"
#include "Drawer.h"
#include <string>
#include <iostream>

Avatar::Avatar(const Vector2f& aPosition)
: MovableGameEntity(aPosition, "open_left_32.png")
{
	avatarImage = "open_left_32.png";
	open = true;
	currentOrientation = "left";
	shouldAnimate = true;

}

Avatar::~Avatar(void)
{
}

void Avatar::Update(float aTime)
{

	//std::cout << "xValue: " << myCurrentTileX<<"\n";
	//std::cout << "yValue: " << myCurrentTileY << "\n";
	int tileSize = 22;
	//Checking the tile values
	if (myCurrentTileX == 5 && myCurrentTileY == 4) {
		std::cout << "At point\n";
	}

	Vector2f destination(myNextTileX * tileSize, myNextTileY * tileSize);
	Vector2f direction = destination - myPosition;

	float distanceToMove = aTime * 30.f;

	if (distanceToMove > direction.Length())
	{
		myPosition = destination;
		myCurrentTileX = myNextTileX;
		myCurrentTileY = myNextTileY;
	}
	else
	{
		direction.Normalize();
		myPosition += direction * distanceToMove;
	}
	Animate(currentOrientation);
}
void Avatar::DrawMovableObject(Drawer* aDrawer)
{
	aDrawer->Draw(avatarImage, (int)myPosition.myX + 220, (int)myPosition.myY + 60);
}
//Method to animate packman
void Avatar::Animate(std::string position) {
	if (shouldAnimate) {
		if (position == "left") {
			if (open) {
				open = false;
				avatarImage = "closed_left_32.png";
			}
			else {
				open = true;
				avatarImage = "open_left_32.png";
			}
		}
		else if (position == "right") {
			if (open) {
				open = false;
				avatarImage = "closed_right_32.png";
			}
			else {
				open = true;
				avatarImage = "open_right_32.png";
			}

		}
		else if (position == "up") {
			if (open) {
				open = false;
				avatarImage = "closed_up_32.png";
			}
			else {
				open = true;
				avatarImage = "open_up_32.png";
			}

		}
		else if (position == "down") {
			if (open) {
				open = false;
				avatarImage = "closed_down_32.png";
			}
			else {
				open = true;
				avatarImage = "open_down_32.png";
			}

		}
	}

}
