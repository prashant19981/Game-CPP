#include "Ghost.h"
#include "World.h"
#include "PathmapTile.h"
#include "Drawer.h"

Ghost::Ghost(const Vector2f& aPosition)
: MovableGameEntity(aPosition, "ghost_32.png")
{
	myIsClaimableFlag = false;
	myIsDeadFlag = false;

	myDesiredMovementX = 0;
	myDesiredMovementY = -1;
}

Ghost::~Ghost(void)
{
}

void Ghost::Die(World* aWorld)
{
	myPath.clear();
	aWorld->GetPath(myCurrentTileX, myCurrentTileY, 13, 13, myPath);
}

void Ghost::Update(float aTime, World* aWorld)
{
	float speed = 30.f;
	int nextTileX = GetCurrentTileX() + myDesiredMovementX;
	int nextTileY = GetCurrentTileY() + myDesiredMovementY;

	if (myIsDeadFlag)
		speed = 120.f;

	if (IsAtDestination())
	{
		if (!myPath.empty())
		{
			PathmapTile* nextTile = myPath.front();
			myPath.pop_front();
			SetNextTile(nextTile->myX, nextTile->myY);
		}
		else if (aWorld->TileIsValid(nextTileX, nextTileY))
		{
			SetNextTile(nextTileX, nextTileY);
			myIsDeadFlag = false;
		}
		else
		{
			myIsDeadFlag = false;
			//Randomize ghost movement
			randomizeGhostPath();

			//myIsDeadFlag = false;
		}
		//Check if ghost's next tile is intersection points
		for (int i = 0;i < 4; i++) {
			if (intersection[i].myX == myNextTileX && intersection[i].myY == myNextTileY) {
				randomizeGhostPath();
				break;
			}
			
		}

	}
	// When the ghost object is at 12,14 or 12,12 tiles we put the motion of the ghost towards upside
	if ((myNextTileX == 12 && myNextTileY == 14) || (myNextTileX ==12) && myNextTileY == 12) {
		myDesiredMovementX = 0;
		myDesiredMovementY = -1;
	}

	int tileSize = 22;
	Vector2f destination(myNextTileX * tileSize, myNextTileY * tileSize);
	Vector2f direction = destination - myPosition;

	float distanceToMove = aTime * speed;

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
}

void Ghost::SetImage(const char* anImage)
{
	myImage = anImage;
}

void Ghost::Draw(Drawer* aDrawer)
{
	if (myIsDeadFlag)
		aDrawer->Draw("Ghost_Dead_32.png", (int)myPosition.myX + 220, (int)myPosition.myY + 60);
	else if (myIsClaimableFlag)
		aDrawer->Draw("Ghost_Vulnerable_32.png", (int)myPosition.myX + 220, (int)myPosition.myY + 60);
	else
		aDrawer->Draw(myImage, (int)myPosition.myX + 220, (int)myPosition.myY + 60);
}


void Ghost::randomizeGhostPath() { // Function to make the movement of ghosts 
	                               //random whenever it encounters an invalid tile
	int random = rand() % 4;
	if (random == 0)
	{
		myDesiredMovementX = 0;
		myDesiredMovementY = 1;
	}
	else if (random == 1)
	{
		myDesiredMovementX = -1;
		myDesiredMovementY = 0;
	}
	else if (random == 2)
	{
		myDesiredMovementX = 0;
		myDesiredMovementY = -1;

	}
	else
	{
		myDesiredMovementX = 1;
		myDesiredMovementY = 0;
	}
}
