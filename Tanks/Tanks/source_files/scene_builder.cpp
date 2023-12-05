#include "../header_files/scene_builder.h"

vector<Entity*> createPlayer(Player* player)
{
	vector<Entity*> playerComponents;
	player->setXShiftValue((float)width / 2);
	player->setYShiftValue((float)height / 2);
	playerComponents.push_back(player);
	playerComponents.push_back(player->getCannon());
	playerComponents.push_back(player->getCockpit());
	for (Entity* component : playerComponents)
	{
		component->setXShiftValue(player->getXShiftValue());
		component->setYShiftValue(player->getYShiftValue());
	}
	return playerComponents;
}

vector<Entity*> createWalls(float dim1, float dim2)
{
	vec4 grey = vec4(0.6f, 0.6f, 0.6f, 1.0f);

	Entity* bottomWall = new Entity();
	bottomWall->createPolygonalShape(createRectangle(dim1, dim2), grey, grey);
	bottomWall->setXShiftValue((float)width / 2);
	bottomWall->setYShiftValue(bottomWall->getHeight() / 2 * bottomWall->getYScaleValue());
	bottomWall->setXScaleValue((float)width);
	Entity* topWall = new Entity();
	topWall->createPolygonalShape(createRectangle(dim1, dim2), grey, grey);
	topWall->setYShiftValue((float)height - topWall->getHeight() / 2 * topWall->getYScaleValue());
	topWall->setXShiftValue((float)width / 2);
	topWall->setXScaleValue((float)width);

	Entity* leftWall = new Entity();
	leftWall->createPolygonalShape(createRectangle(dim2, dim1), grey, grey);
	leftWall->setXShiftValue(leftWall->getWidth() / 2 * leftWall->getXScaleValue());
	leftWall->setYShiftValue((float)height / 2);
	leftWall->setYScaleValue((float)height);
	Entity* rightWall = new Entity();
	rightWall->createPolygonalShape(createRectangle(dim2, dim1), grey, grey);
	rightWall->setXShiftValue((float)width - rightWall->getWidth() / 2 * rightWall->getXScaleValue());
	rightWall->setYShiftValue((float)height / 2);
	rightWall->setYScaleValue((float)height);

	Entity* midLeftWall = new Entity();
	midLeftWall->createPolygonalShape(createRectangle(dim2, dim1), grey, grey);
	midLeftWall->setXShiftValue((float)width / 6 + midLeftWall->getWidth() / 2 * midLeftWall->getXScaleValue());
	midLeftWall->setYShiftValue((float)height / 2);
	midLeftWall->setYScaleValue((float)height / 2);
	Entity* midRightWall = new Entity();
	midRightWall->createPolygonalShape(createRectangle(dim2, dim1), grey, grey);
	midRightWall->setXShiftValue((float)width - midLeftWall->getXShiftValue());
	midRightWall->setYShiftValue((float)height / 2);
	midRightWall->setYScaleValue((float)height / 2);

	Entity* midTopWall = new Entity();
	midTopWall->createPolygonalShape(createRectangle(dim1, dim2), grey, grey);
	midTopWall->setXShiftValue((float)width / 2);
	midTopWall->setYShiftValue((float)height * 2 / 3);
	midTopWall->setXScaleValue((float)width / 4);
	Entity* midBottomWall = new Entity();
	midBottomWall->createPolygonalShape(createRectangle(dim1, dim2), grey, grey);
	midBottomWall->setXShiftValue(midTopWall->getXShiftValue());
	midBottomWall->setYShiftValue((float)height - midTopWall->getYShiftValue());
	midBottomWall->setXScaleValue(midTopWall->getXScaleValue());

	vector<Entity*> walls;
	walls.push_back(bottomWall);
	walls.push_back(topWall);
	walls.push_back(leftWall);
	walls.push_back(rightWall);
	walls.push_back(midLeftWall);
	walls.push_back(midRightWall);
	walls.push_back(midTopWall);
	walls.push_back(midBottomWall);
	return walls;
}

vector<Entity*> createEnemies(char* controlPointsFile)
{
	vector<vec3> controlPoints = readPolygonVertices(controlPointsFile);

	Entity* enemy1 = new Entity();		// In basso a sinistra
	enemy1->createHermiteShape(controlPoints, vec3(0.0f, 0.2f, 0.0f), vec4(1.0f, 0.0f, 0.0f, 1.0f), vec4(1.0f, 0.0f, 0.0f, 1.0f));
	enemy1->setXShiftValue((float)width / 12);
	enemy1->setYShiftValue((float)height / 3);

	Entity* enemy2 = new Entity();		// In basso a destra
	enemy2->createHermiteShape(controlPoints, vec3(0.0f, 0.2f, 0.0f), vec4(1.0f, 0.0f, 0.0f, 1.0f), vec4(1.0f, 0.0f, 0.0f, 1.0f));
	enemy2->setXShiftValue((float)width - enemy1->getXShiftValue());
	enemy2->setYShiftValue(enemy1->getYShiftValue());

	Entity* enemy3 = new Entity();		// In alto a sinistra
	enemy3->createHermiteShape(controlPoints, vec3(0.0f, 0.2f, 0.0f), vec4(1.0f, 0.0f, 0.0f, 1.0f), vec4(1.0f, 0.0f, 0.0f, 1.0f));
	enemy3->setXShiftValue(enemy1->getXShiftValue());
	enemy3->setYShiftValue((float)height - enemy1->getYShiftValue());

	Entity* enemy4 = new Entity();		// In alto a destra
	enemy4->createHermiteShape(controlPoints, vec3(0.0f, 0.2f, 0.0f), vec4(1.0f, 0.0f, 0.0f, 1.0f), vec4(1.0f, 0.0f, 0.0f, 1.0f));
	enemy4->setXShiftValue(enemy2->getXShiftValue());
	enemy4->setYShiftValue((float)height - enemy2->getYShiftValue());

	Entity* enemy5 = new Entity();		// In alto
	enemy5->createHermiteShape(controlPoints, vec3(0.0f, 0.2f, 0.0f), vec4(1.0f, 0.0f, 0.0f, 1.0f), vec4(1.0f, 0.0f, 0.0f, 1.0f));
	enemy5->setXShiftValue((float)width / 2);
	enemy5->setYShiftValue((float)height * 4 / 5);

	Entity* enemy6 = new Entity();		// In basso
	enemy6->createHermiteShape(controlPoints, vec3(0.0f, 0.2f, 0.0f), vec4(1.0f, 0.0f, 0.0f, 1.0f), vec4(1.0f, 0.0f, 0.0f, 1.0f));
	enemy6->setXShiftValue(enemy5->getXShiftValue());
	enemy6->setYShiftValue((float)height - enemy5->getYShiftValue());

	vector<Entity*> enemies;
	enemies.push_back(enemy1);
	enemies.push_back(enemy2);
	enemies.push_back(enemy3);
	enemies.push_back(enemy4);
	enemies.push_back(enemy5);
	enemies.push_back(enemy6);
	return enemies;
}

vector<Entity*> createLives(float numberOfLives, float radius, float wallThickness)
{
	vec4 red = vec4(1.0f, 0.0f, 0.0f, 1.0f);
	vector<Entity*> lives;
	for (int i = 0; i < numberOfLives; i++)
		lives.push_back(new Entity());
	int i = 0;
	for (Entity* heart : lives)
	{
		heart->createPolygonalShape(createHeart(radius, radius, 100), red, red);
		heart->setYShiftValue((float)height - heart->getHeight() / 2 * heart->getYScaleValue() - wallThickness);
		heart->setXShiftValue(wallThickness + heart->getWidth() / 2 * heart->getXScaleValue() + i * (heart->getWidth() * heart->getXScaleValue() + 5.0f));
		i++;
	}
	return lives;
}