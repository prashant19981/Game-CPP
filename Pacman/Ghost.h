#ifndef GHOST_H
#define GHOST_H

#include <list>
#include "MovableGameEntity.h"

class World;
class PathmapTile;

class Ghost : public MovableGameEntity
{
public:
	Ghost(const Vector2f& aPosition);
	~Ghost(void);

	void Update(float aTime, World* aWorld);

	bool myIsClaimableFlag;
	bool myIsDeadFlag;

	void SetImage(const char* anImage);

	void Die(World* aWorld);

	void Draw(Drawer* aDrawer);
	void setDesiredMovementX(int xVal) { myDesiredMovementX = xVal; }
	void setDesiredMovementY(int yVal) { myDesiredMovementY = yVal; }
	void randomizeGhostPath();

protected:

	int myDesiredMovementX;
	int myDesiredMovementY;

	std::list<PathmapTile*> myPath;
	//Adding the four intersection points in a constant vector array
	const Vector2f intersection[4] = {Vector2f(5,19),Vector2f(5,4) ,Vector2f(20,4) ,Vector2f(20,19)};

};

#endif // GHOST_H