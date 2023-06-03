#include "Pacman.h"
#include "Drawer.h"
#include "SDL.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

#include "Avatar.h"
#include "World.h"
#include "Ghost.h"

char* currentImage="open_left_32.png";

Pacman* Pacman::Create(Drawer* aDrawer)
{
	Pacman* pacman = new Pacman(aDrawer);

	if (!pacman->Init())
	{
		delete pacman;
		pacman = NULL;
	}

	return pacman;
}

Pacman::Pacman(Drawer* aDrawer)
: myDrawer(aDrawer)
, myTimeToNextUpdate(0.f)
, myNextMovement(-1.f,0.f)
, myCurrentMovement(-1.f,0.f)
, myScore(0)
, myFps(0)
, myLives(3)
, myGhostGhostCounter(0.f)
{
	myAvatar = new Avatar(Vector2f(13*22,22*22));
	myGhost = new Ghost(Vector2f(10*22,14*22));
	myGhost2 = new Ghost(Vector2f(11 * 22, 14 * 22));
	myGhost2->SetImage("ghost_32_cyan.png");
	myGhost3 = new Ghost(Vector2f(12 * 22, 14 * 22));
	myGhost3->SetImage("ghost_32_orange.png");
	myGhost4 = new Ghost(Vector2f(13 * 22, 14 * 22));
	myGhost4->SetImage("ghost_32_pink.png");
	myGhost5 = new Ghost(Vector2f(14 * 22, 14 * 22));
	myGhost5->SetImage("ghost_32_red.png");


	myWorld = new World();
}

Pacman::~Pacman(void)
{
}

bool Pacman::Init()
{
	myWorld->Init();

	return true;
}

bool Pacman::Update(float aTime)
{
	//std::cout << myFps;
	if (!UpdateInput())
		return false;

	if (CheckEndGameCondition())

	{
		//std::cout << "WIN Calling Drawtext\n";
		myDrawer->DrawText("You win!", "freefont-ttf\\sfd\\FreeMono.ttf", 20, 70);
		return true;
	}
	else if (myLives <= 0)
	{
		//std::cout << "Lose Calling Drawtext\n";
		myDrawer->DrawText("You lose!", "freefont-ttf\\sfd\\FreeMono.ttf", 20, 70);	
		return true;
	}

	MoveAvatar();
	myAvatar->Update(aTime);
	myGhost->Update(aTime, myWorld);
	myGhost2->Update(aTime, myWorld);
	myGhost3->Update(aTime, myWorld);
	myGhost4->Update(aTime, myWorld);
	myGhost5->Update(aTime, myWorld);

	if (myWorld->HasIntersectedDot(myAvatar->GetPosition()))
		myScore += 10;

	myGhostGhostCounter -= aTime;

	if (myWorld->HasIntersectedBigDot(myAvatar->GetPosition()))
	{
		myScore += 20;
		myGhostGhostCounter = 20.f;
		myGhost->myIsClaimableFlag = true;
		myGhost2->myIsClaimableFlag = true;
		myGhost3->myIsClaimableFlag = true;
		myGhost4->myIsClaimableFlag = true;
		myGhost5->myIsClaimableFlag = true;
	}

	if (myGhostGhostCounter <= 0)
	{
		myGhost->myIsClaimableFlag = false;
		myGhost2->myIsClaimableFlag = false;
		myGhost3->myIsClaimableFlag = false;
		myGhost4->myIsClaimableFlag = false;
		myGhost5->myIsClaimableFlag = false;
	}

	if ((myGhost->GetPosition() - myAvatar->GetPosition()).Length() < 10.f)
	{
		if (myGhostGhostCounter <= 0.f)
		{
			myLives--;

			myAvatar->SetPosition(Vector2f(13*22,22*22));
			// reset direction and destination values
			myAvatar->setOrientation("left");
			myAvatar->setAnimation(true);
			//myAvatar->SetNextTile()
			myAvatar->SetNextTile(myAvatar->GetPosition().myX / 22, myAvatar->GetPosition().myY / 22);
			myCurrentMovement = Vector2f(-1.f, 0.f);
			myGhost->SetPosition(Vector2f(13*22,8*22));
			myGhost->SetNextTile(myGhost->GetPosition().myX / 22, myGhost->GetPosition().myY / 22);

			myGhost2->SetPosition(Vector2f(13 * 22, 8 * 22));
			myGhost2->SetNextTile(myGhost->GetPosition().myX / 22, myGhost->GetPosition().myY / 22);

			myGhost3->SetPosition(Vector2f(13 * 22, 8 * 22));
			myGhost3->SetNextTile(myGhost->GetPosition().myX / 22, myGhost->GetPosition().myY / 22);

			myGhost4->SetPosition(Vector2f(13 * 22, 8 * 22));
			myGhost4->SetNextTile(myGhost->GetPosition().myX / 22, myGhost->GetPosition().myY / 22);

			myGhost5->SetPosition(Vector2f(13 * 22, 8 * 22));
			myGhost5->SetNextTile(myGhost->GetPosition().myX / 22, myGhost->GetPosition().myY / 22);
			
		}
		else if (myGhost->myIsClaimableFlag && !myGhost->myIsDeadFlag)
		{
			myScore += 50;
			myGhost->myIsDeadFlag = true;
			myGhost->Die(myWorld);
		}
	}
	else if ((myGhost2->GetPosition() - myAvatar->GetPosition()).Length() < 10.f) {
		if (myGhostGhostCounter <= 0.f)
		{
			myLives--;

			myAvatar->SetPosition(Vector2f(13 * 22, 22 * 22));
			// reset direction and destination values
			myAvatar->setOrientation("left");
			myAvatar->setAnimation(true);
			//myAvatar->SetNextTile()
			myAvatar->SetNextTile(myAvatar->GetPosition().myX / 22, myAvatar->GetPosition().myY / 22);
			myCurrentMovement = Vector2f(-1.f, 0.f);
			myGhost->SetPosition(Vector2f(10 * 22, 10 * 22));
			myGhost->SetNextTile(myGhost->GetPosition().myX / 22, myGhost->GetPosition().myY / 22);
			myGhost->setDesiredMovementX(0);
			myGhost->setDesiredMovementY(-1);

			myGhost2->SetPosition(Vector2f(10 * 22, 10 * 22));
			myGhost2->SetNextTile(myGhost->GetPosition().myX / 22, myGhost->GetPosition().myY / 22);
			myGhost2->setDesiredMovementX(0);
			myGhost2->setDesiredMovementY(-1);

			myGhost3->SetPosition(Vector2f(16 * 22, 10 * 22));
			myGhost3->SetNextTile(myGhost->GetPosition().myX / 22, myGhost->GetPosition().myY / 22);
			myGhost3->setDesiredMovementX(0);
			myGhost3->setDesiredMovementY(-1);

			myGhost4->SetPosition(Vector2f(16 * 22, 10 * 22));
			myGhost4->SetNextTile(myGhost->GetPosition().myX / 22, myGhost->GetPosition().myY / 22);
			myGhost4->setDesiredMovementX(0);
			myGhost4->setDesiredMovementY(-1);

			myGhost5->SetPosition(Vector2f(13 * 22, 13 * 22));
			myGhost5->SetNextTile(myGhost->GetPosition().myX / 22, myGhost->GetPosition().myY / 22);
			myGhost5->setDesiredMovementX(0);
			myGhost5->setDesiredMovementY(-1);

		}
		else if (myGhost2->myIsClaimableFlag && !myGhost2->myIsDeadFlag)
		{
			myScore += 50;
			myGhost2->myIsDeadFlag = true;
			myGhost2->Die(myWorld);
		}
	}
	else if ((myGhost3->GetPosition() - myAvatar->GetPosition()).Length() < 10.f)
	{
		if (myGhostGhostCounter <= 0.f)
		{
			myLives--;

			myAvatar->SetPosition(Vector2f(13 * 22, 22 * 22));
			// reset direction and destination values
			myAvatar->setOrientation("left");
			myAvatar->setAnimation(true);
			//myAvatar->SetNextTile()
			myAvatar->SetNextTile(myAvatar->GetPosition().myX / 22, myAvatar->GetPosition().myY / 22);
			myCurrentMovement = Vector2f(-1.f, 0.f);
			myGhost->SetPosition(Vector2f(13 * 22, 13 * 22));
			myGhost->SetNextTile(myGhost->GetPosition().myX / 22, myGhost->GetPosition().myY / 22);

			myGhost2->SetPosition(Vector2f(13 * 22, 13 * 22));
			myGhost2->SetNextTile(myGhost->GetPosition().myX / 22, myGhost->GetPosition().myY / 22);

			myGhost3->SetPosition(Vector2f(13 * 22, 13 * 22));
			myGhost3->SetNextTile(myGhost->GetPosition().myX / 22, myGhost->GetPosition().myY / 22);

			myGhost4->SetPosition(Vector2f(13 * 22, 13 * 22));
			myGhost4->SetNextTile(myGhost->GetPosition().myX / 22, myGhost->GetPosition().myY / 22);

			myGhost5->SetPosition(Vector2f(13 * 22, 13 * 22));
			myGhost5->SetNextTile(myGhost->GetPosition().myX / 22, myGhost->GetPosition().myY / 22);

		}
		else if (myGhost3->myIsClaimableFlag && !myGhost3->myIsDeadFlag)
		{
			myScore += 50;
			myGhost3->myIsDeadFlag = true;
			myGhost3->Die(myWorld);
		}

	}
	else if ((myGhost4->GetPosition() - myAvatar->GetPosition()).Length() < 10.f)
	{
		if (myGhostGhostCounter <= 0.f)
		{
			myLives--;

			myAvatar->SetPosition(Vector2f(13 * 22, 22 * 22));
		
			myAvatar->setOrientation("left");
			myAvatar->setAnimation(true);
			//reset characters
			myAvatar->SetNextTile(myAvatar->GetPosition().myX / 22, myAvatar->GetPosition().myY / 22);
			myCurrentMovement = Vector2f(-1.f, 0.f);
			myGhost->SetPosition(Vector2f(13 * 22, 13 * 22));
			myGhost->SetNextTile(myGhost->GetPosition().myX / 22, myGhost->GetPosition().myY / 22);

			myGhost2->SetPosition(Vector2f(13 * 22, 13 * 22));
			myGhost2->SetNextTile(myGhost->GetPosition().myX / 22, myGhost->GetPosition().myY / 22);

			myGhost3->SetPosition(Vector2f(13 * 22, 13 * 22));
			myGhost3->SetNextTile(myGhost->GetPosition().myX / 22, myGhost->GetPosition().myY / 22);

			myGhost4->SetPosition(Vector2f(13 * 22, 13 * 22));
			myGhost4->SetNextTile(myGhost->GetPosition().myX / 22, myGhost->GetPosition().myY / 22);

			myGhost5->SetPosition(Vector2f(13 * 22, 13 * 22));
			myGhost5->SetNextTile(myGhost->GetPosition().myX / 22, myGhost->GetPosition().myY / 22);

		}
		else if (myGhost4->myIsClaimableFlag && !myGhost4->myIsDeadFlag)
		{
			myScore += 50;
			myGhost4->myIsDeadFlag = true;
			myGhost4->Die(myWorld);
		}

	}
	else if ((myGhost5->GetPosition() - myAvatar->GetPosition()).Length() < 10.f)
	{
		if (myGhostGhostCounter <= 0.f)
		{
			myLives--;

			myAvatar->SetPosition(Vector2f(13 * 22, 22 * 22));
			// reset direction and destination values
			myAvatar->setOrientation("left");
			myAvatar->setAnimation(true);
			//myAvatar->SetNextTile()
			myAvatar->SetNextTile(myAvatar->GetPosition().myX / 22, myAvatar->GetPosition().myY / 22);
			myCurrentMovement = Vector2f(-1.f, 0.f);
			myGhost->SetPosition(Vector2f(10 * 22, 14 * 22));
			myGhost->SetNextTile(myGhost->GetPosition().myX / 22, myGhost->GetPosition().myY / 22);

			myGhost2->SetPosition(Vector2f(11 * 22, 14 * 22));
			myGhost2->SetNextTile(myGhost->GetPosition().myX / 22, myGhost->GetPosition().myY / 22);

			myGhost3->SetPosition(Vector2f(12 * 22, 14 * 22));
			myGhost3->SetNextTile(myGhost->GetPosition().myX / 22, myGhost->GetPosition().myY / 22);

			myGhost4->SetPosition(Vector2f(13 * 22, 14 * 22));
			myGhost4->SetNextTile(myGhost->GetPosition().myX / 22, myGhost->GetPosition().myY / 22);

			myGhost5->SetPosition(Vector2f(14 * 22, 14 * 22));
			myGhost5->SetNextTile(myGhost->GetPosition().myX / 22, myGhost->GetPosition().myY / 22);

		}
		else if (myGhost5->myIsClaimableFlag && !myGhost5->myIsDeadFlag)
		{
			myScore += 50;
			myGhost->myIsDeadFlag = true;
			myGhost->Die(myWorld);
		}
	}
	
	if (aTime > 0)
		myFps = (int) (1 / aTime);

	return true;
}

bool Pacman::UpdateInput()
{
	const Uint8 *keystate = SDL_GetKeyboardState(NULL);
	
	//std::cout <<  + "Input Pressed\n";
	if (keystate[SDL_SCANCODE_UP]) {
		myNextMovement = Vector2f(0.f, -1.f);
		//std::cout << "Up Pressed\n";
	}
	else if (keystate[SDL_SCANCODE_DOWN]) {
		myNextMovement = Vector2f(0.f, 1.f);
		//std::cout << "Down Pressed\n";
		
	}
	else if (keystate[SDL_SCANCODE_RIGHT]) {
		myNextMovement = Vector2f(1.f, 0.f);
		//std::cout << "Right Pressed\n";

		
	}
	else if (keystate[SDL_SCANCODE_LEFT]) {
		myNextMovement = Vector2f(-1.f, 0.f);
		//std::cout << "left Pressed\n";
		
	}

	if (keystate[SDL_SCANCODE_ESCAPE])
		return false;

	return true;
}

void Pacman::MoveAvatar()
{
	int nextTileX = myAvatar->GetCurrentTileX() + myNextMovement.myX;
	int nextTileY = myAvatar->GetCurrentTileY() + myNextMovement.myY;
	//std::cout << std::to_string(myAvatar->GetCurrentTileX()) + " CurrentX\n";
	//std::cout << std::to_string(myAvatar->GetCurrentTileY()) + " CurrentY\n";


	if (myAvatar->IsAtDestination())
	{
		if (myWorld->TileIsValid(nextTileX, nextTileY))
		{
			

			myAvatar->SetNextTile(nextTileX, nextTileY);
			myAvatar->setAnimation(true);  // animate only when the next tile is valid
			if (myNextMovement.myX == 1.f) {
				myAvatar->setOrientation("right"); //Setting up the orientation of Packman based on user inputs
				myCurrentMovement = Vector2f(1.f, 0.f); 
			}
			else if (myNextMovement.myX == -1.f) {
				myAvatar->setOrientation("left");
				myCurrentMovement = Vector2f(-1.f, 0.f);// value only changed when next tile is valid, fixes the problem of
				                                        // of Packman getting stuck
			}
			else if (myNextMovement.myY == 1.f) {
				myAvatar->setOrientation("down");
				myCurrentMovement = Vector2f(0.f, 1.f);
			}
			else if (myNextMovement.myY == -1.f) {
				myAvatar->setOrientation("up");
				myCurrentMovement = Vector2f(0.f, -1.f);
			}
			//

		}
		else {
			//std::cout << "Invalid Tile\n";
			myNextMovement = myCurrentMovement;
			myAvatar->setAnimation(false);// If next tile is invalid then animation is stopped
			
		}
	}
}

bool Pacman::CheckEndGameCondition()
{
	return false;
}

bool Pacman::Draw()
{
	myWorld->Draw(myDrawer);
	myAvatar->DrawMovableObject(myDrawer);
	myGhost->Draw(myDrawer);
	myGhost2->Draw(myDrawer);
	myGhost3->Draw(myDrawer);
	myGhost4->Draw(myDrawer);
	myGhost5->Draw(myDrawer);

	std::string scoreString;
	std::stringstream scoreStream;
	scoreStream << myScore;
	scoreString = scoreStream.str();
	//std::cout << "Score Text Calling Drawtext\n";
	myDrawer->DrawText("Score", "freefont-ttf\\sfd\\FreeMono.ttf", 20, 50);
	//std::cout << "Score Value Calling Drawtext\n";
	myDrawer->DrawText(scoreString.c_str(), "freefont-ttf\\sfd\\FreeMono.ttf", 90, 50);

	std::string livesString;
	std::stringstream liveStream;
	liveStream << myLives;
	livesString = liveStream.str();
	//std::cout << "Lives Calling Drawtext\n";
	myDrawer->DrawText("Lives", "freefont-ttf\\sfd\\FreeMono.ttf", 20, 80);
	myDrawer->DrawText(livesString.c_str(), "freefont-ttf\\sfd\\FreeMono.ttf", 90, 80);

	//std::cout << "FPS Calling Drawtext\n";
	myDrawer->DrawText("FPS", "freefont-ttf\\sfd\\FreeMono.ttf", 880, 50);
	std::string fpsString;
	std::stringstream fpsStream;
	fpsStream << myFps;
	fpsString = fpsStream.str();
	myDrawer->DrawText(fpsString.c_str(), "freefont-ttf\\sfd\\FreeMono.ttf", 930, 50);

	return true;
}
