#include "../header files/interactions.h"

#define SHIFT_VALUE 10.0f

void moveTank(float rotationValue, float xShift, float yShift)
{
	player.setRotationValue(rotationValue);
	player.setXShiftValue(player.getXShiftValue() + xShift);
	player.setYShiftValue(player.getYShiftValue() + yShift);
	player.getCannon()->setXShiftValue(player.getCannon()->getXShiftValue() + xShift);
	player.getCannon()->setYShiftValue(player.getCannon()->getYShiftValue() + yShift);
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
		case 'w':
			moveTank(0.0f, 0.0f, SHIFT_VALUE);
			break;
		case 'a':
			moveTank(90.0f, -SHIFT_VALUE, 0.0f);
			break;
		case 's':
			moveTank(180.0f, 0.0f, -SHIFT_VALUE);
			break;
		case 'd':
			moveTank(270.0f, SHIFT_VALUE, 0.0f);
			break;
		default:
			break;
	}
}