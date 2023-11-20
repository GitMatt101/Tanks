#pragma once
#include "../header files/entities.h"

extern Player* player;
extern vector<Entity*> walls;

extern const int width;
extern const int height;

void keyboard(unsigned char key, int x, int y);

void mouseMovement(int x, int y);