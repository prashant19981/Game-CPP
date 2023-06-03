#ifndef AVATAR_H
#define AVATAR_H

#include "MovableGameEntity.h"
#include "Vector2f.h"
#include <string>
class Avatar : public MovableGameEntity
{
public:
	Avatar(const Vector2f& aPosition);
	~Avatar(void);

	void Update(float aTime);

	void DrawMovableObject(Drawer* aDrawer);
	void Animate(std::string position);
	void ChangeImage(char* anImage) { avatarImage = anImage; }
	void setOrientation(std::string orientation) { currentOrientation = orientation; }
	void setAnimation(bool value) { shouldAnimate = value; }

private:

	char* avatarImage;
	bool open;
	std::string currentOrientation;
	bool shouldAnimate;
};

#endif //AVATAR_H