#ifndef MOVABLEGAMEENTITY_H
#define MOVABLEGAMEENTITY_H

#include "GameEntity.h"
#include "Vector2f.h"

class MovableGameEntity : public GameEntity
{
public:
	MovableGameEntity(const Vector2f& aPosition,const char* anImage);
	~MovableGameEntity(void);

	void SetNextTile(int anX, int anY);
	//void MovableGameEntity::DrawMovable(Drawer* aDrawer);
	int GetCurrentTileX() const { return myCurrentTileX; }
	int GetCurrentTileY() const { return myCurrentTileY; }
	//void MovableGameEntity::DrawMovable(Drawer* aDrawer);
	int GetNextTileX() const { return myNextTileX; }
	int GetNextTileY() const { return myNextTileY; }

	bool IsAtDestination();

protected:

	int myCurrentTileX;
	int myCurrentTileY;

	int myNextTileX;
	int myNextTileY;
	//char* myImage;

};

#endif // MOVABLEGAMEENTITY_H