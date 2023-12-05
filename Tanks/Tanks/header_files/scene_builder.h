#pragma once
#include "entities.h"
#include "shape_reader.h"

extern const int width;
extern const int height;

vector<Entity*> createPlayer(Player* player);

vector<Entity*> createWalls(float dim1, float dim2);

vector<Entity*> createEnemies(char* controlPointsFile);

vector<Entity*> createLives(float numberOfLives, float radius, float wallThickness);