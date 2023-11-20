#include "../header files/interactions.h"
#include <math.h>

#define SHIFT_VALUE 10.0f

void moveTank(float xShift, float yShift)
{
	player->setXShiftValue(player->getXShiftValue() + xShift);
	player->setYShiftValue(player->getYShiftValue() + yShift);
	player->getCannon()->setXShiftValue(player->getCannon()->getXShiftValue() + xShift);
	player->getCannon()->setYShiftValue(player->getCannon()->getYShiftValue() + yShift);
	player->getCockpit()->setXShiftValue(player->getCockpit()->getXShiftValue() + xShift);
	player->getCockpit()->setYShiftValue(player->getCockpit()->getYShiftValue() + yShift);
}

bool checkWallCollision(float xShift, float yShift)
{
	float xPlayerBottomWorld = (float)width / 2 + player->getHitbox().cornerBot.x * player->getXScaleValue() + player->getXShiftValue() + xShift;
	float yPlayerBottomWorld = (float)height / 2 + player->getHitbox().cornerBot.y * player->getYScaleValue() + player->getYShiftValue() + yShift;
	float xPlayerTopWorld = (float)width / 2 + player->getHitbox().cornerTop.x * player->getXScaleValue() + player->getXShiftValue() + xShift;
	float yPlayerTopWorld = (float)height / 2 + player->getHitbox().cornerTop.y * player->getYScaleValue() + player->getYShiftValue() + yShift;
	for (Entity* wall : walls)
	{
		float xWallBottomWorld = (float)width / 2 + wall->getHitbox().cornerBot.x * wall->getXScaleValue() + wall->getXShiftValue();
		float yWallBottomWorld = (float)height / 2 + wall->getHitbox().cornerBot.y * wall->getYScaleValue() + wall->getYShiftValue();
		float xWallTopWorld = (float)width / 2 + wall->getHitbox().cornerTop.x * wall->getXScaleValue() + wall->getXShiftValue();
		float yWallTopWorld = (float)height / 2 + wall->getHitbox().cornerTop.y * wall->getYScaleValue() + wall->getYShiftValue();
		if (xPlayerBottomWorld <= xWallTopWorld && xPlayerTopWorld >= xWallBottomWorld
			&& yPlayerBottomWorld <= yWallTopWorld && yPlayerTopWorld >= yWallBottomWorld)
			return true;
	}
	return false;
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
		case 'w':
			if (!checkWallCollision(0.0f, SHIFT_VALUE))
				moveTank(0.0f, SHIFT_VALUE);
			player->setRotationValue(0.0f);
			break;
		case 'a':
			if (!checkWallCollision(-SHIFT_VALUE, 0.0f))
				moveTank(-SHIFT_VALUE, 0.0f);
			player->setRotationValue(90.0f);
			break;
		case 's':
			if (!checkWallCollision(0.0f, -SHIFT_VALUE))
				moveTank(0.0f, -SHIFT_VALUE);
			player->setRotationValue(180.0f);
			break;
		case 'd':
			if (!checkWallCollision(SHIFT_VALUE, 0.0f))
				moveTank(SHIFT_VALUE, 0.0f);
			player->setRotationValue(270.0f);
			break;
		case ' ':
			player->shoot();
			break;
		default:
			break;
	}
}

void mouseMovement(int x, int y)
{
	float m = ((float)(height - y) - ((float)height / 2 + player->getYShiftValue())) / ((float)x - ((float)width / 2 + player->getXShiftValue()));
	float angle = degrees(atan(m));
	if ((float)height - y > (float)height / 2 + player->getYShiftValue() && x < (float)width / 2 + player->getXShiftValue())
		angle = 180.0f + angle;
	else if ((float)height - y < (float)height / 2 + player->getYShiftValue() && x < (float)width / 2 + player->getXShiftValue())
		angle += 180.0f;
	float xShift = cos(radians(angle)) * player->getCannon()->getXScaleValue();
	float yShift = sin(radians(angle)) * player->getCannon()->getYScaleValue();
	player->getCannon()->setXShiftValue(player->getXShiftValue() + xShift);
	player->getCannon()->setYShiftValue(player->getYShiftValue() + yShift);
	player->getCannon()->setRotationValue(-90.0f + angle);
}