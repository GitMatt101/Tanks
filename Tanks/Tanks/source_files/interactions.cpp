#include "../header_files/interactions.h"
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

bool checkWallCollision(Entity* entity, float xShift, float yShift)
{
	for (Entity* wall : walls)
	{
		if (entity->getHitboxWorldCoordinates().cornerBot.x + xShift <= wall->getHitboxWorldCoordinates().cornerTop.x
			&& entity->getHitboxWorldCoordinates().cornerTop.x + xShift >= wall->getHitboxWorldCoordinates().cornerBot.x
			&& entity->getHitboxWorldCoordinates().cornerBot.y + yShift <= wall->getHitboxWorldCoordinates().cornerTop.y 
			&& entity->getHitboxWorldCoordinates().cornerTop.y + yShift >= wall->getHitboxWorldCoordinates().cornerBot.y)
			return true;
	}
	return false;
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
		case 'w':
			if (player->getRotationValue() == 90.0f)
			{
				player->rotateHitbox();
				player->setRotationValue(0.0f);
			}
			if (!checkWallCollision(player, 0.0f, SHIFT_VALUE))
				moveTank(0.0f, SHIFT_VALUE);
			break;
		case 'a':
			if (player->getRotationValue() == 0.0f)
			{
				player->rotateHitbox();
				player->setRotationValue(90.0f);
			}
			if (!checkWallCollision(player, -SHIFT_VALUE, 0.0f))
				moveTank(-SHIFT_VALUE, 0.0f);
			break;
		case 's':
			if (player->getRotationValue() == 90.0f)
			{
				player->rotateHitbox();
				player->setRotationValue(0.0f);
			}
			if (!checkWallCollision(player, 0.0f, -SHIFT_VALUE))
				moveTank(0.0f, -SHIFT_VALUE);
			break;
		case 'd':
			if (player->getRotationValue() == 0.0f)
			{
				player->rotateHitbox();
				player->setRotationValue(90.0f);
			}
			if (!checkWallCollision(player, SHIFT_VALUE, 0.0f))
				moveTank(SHIFT_VALUE, 0.0f);
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
	float m = ((float)(height - y) -  player->getYShiftValue()) / ((float)x - player->getXShiftValue());
	float angle = degrees(atan(m));
	if ((float)height - y > player->getYShiftValue() && x < player->getXShiftValue())
		angle = 180.0f + angle;
	else if ((float)height - y < player->getYShiftValue() && x < player->getXShiftValue())
		angle += 180.0f;
	else if ((float)height - y < player->getYShiftValue() && x > player->getXShiftValue())
		angle = 360.0f + angle;
	else if (angle == 0.0f && (float)x < player->getXShiftValue())
		angle = 180.0f;
	float xShift = cos(radians(angle)) * player->getCannon()->getXScaleValue();
	float yShift = sin(radians(angle)) * player->getCannon()->getYScaleValue();
	player->getCannon()->setXShiftValue(player->getXShiftValue() + xShift);
	player->getCannon()->setYShiftValue(player->getYShiftValue() + yShift);
	player->getCannon()->setRotationValue(-90.0f + angle);
}

bool checkEnemyCollision(Entity* entity)
{
	for (int i = 0; i < enemies.size(); i++)
	{
		if (entity->getHitboxWorldCoordinates().cornerBot.x <= enemies[i]->getHitboxWorldCoordinates().cornerTop.x
			&& entity->getHitboxWorldCoordinates().cornerTop.x >= enemies[i]->getHitboxWorldCoordinates().cornerBot.x
			&& entity->getHitboxWorldCoordinates().cornerBot.y <= enemies[i]->getHitboxWorldCoordinates().cornerTop.y
			&& entity->getHitboxWorldCoordinates().cornerTop.y >= enemies[i]->getHitboxWorldCoordinates().cornerBot.y)
		{
			Entity* enemy = enemies[i];
			for (int j = i; j < enemies.size() - 1; j++)
				enemies[j] = enemies[j + 1];
			enemies.pop_back();
			delete(enemy);
			i--;
			return true;
		}
	}
	return false;
}