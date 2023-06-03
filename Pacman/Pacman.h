#ifndef PACMAN_H
#define PACMAN_H

#include "Vector2f.h"

struct SDL_Surface;
class Drawer;
class Avatar;
class World;
class Ghost;

class Pacman
{
public:
	static Pacman* Create(Drawer* aDrawer);
	~Pacman(void);

	bool Update(float aTime);
	bool Draw();

private:
	Pacman(Drawer* aDrawer);
	bool Init();
	bool UpdateInput();
	void MoveAvatar();
	bool CheckEndGameCondition();

	Drawer* myDrawer;

	float myTimeToNextUpdate;
	float myGhostGhostCounter;

	int myLives;
	int myScore;
	int myFps;

	Vector2f myNextMovement;
	Vector2f myCurrentMovement; 

	Avatar* myAvatar;
	Ghost* myGhost;
	Ghost* myGhost2;
	Ghost* myGhost3;
	Ghost* myGhost4;
	Ghost* myGhost5;

	World* myWorld;

};

#endif // PACMAN_H