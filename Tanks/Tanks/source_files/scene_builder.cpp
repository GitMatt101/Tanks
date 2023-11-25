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
	Entity* bottomWall = new Entity();
	bottomWall->createPolygonalShape(createRectangle(dim1, dim2), vec3(0.0f, 0.0f, 0.0f), vec4(0.6f, 0.6f, 0.6f, 1.0f), vec4(0.6f, 0.6f, 0.6f, 1.0f));
	bottomWall->setXShiftValue((float)width / 2);
	bottomWall->setYShiftValue(bottomWall->getHeight() / 2 * bottomWall->getYScaleValue());
	bottomWall->setXScaleValue((float)width);
	Entity* topWall = new Entity();
	topWall->createPolygonalShape(createRectangle(dim1, dim2), vec3(0.0f, 0.0f, 0.0f), vec4(0.6f, 0.6f, 0.6f, 1.0f), vec4(0.6f, 0.6f, 0.6f, 1.0f));
	topWall->setYShiftValue((float)height - topWall->getHeight() / 2 * topWall->getYScaleValue());
	topWall->setXShiftValue((float)width / 2);
	topWall->setXScaleValue((float)width);

	Entity* leftWall = new Entity();
	leftWall->createPolygonalShape(createRectangle(dim2, dim1), vec3(0.0f, 0.0f, 0.0f), vec4(0.6f, 0.6f, 0.6f, 1.0f), vec4(0.6f, 0.6f, 0.6f, 1.0f));
	leftWall->setXShiftValue(leftWall->getWidth() / 2 * leftWall->getXScaleValue());
	leftWall->setYShiftValue((float)height / 2);
	leftWall->setYScaleValue((float)height);
	Entity* rightWall = new Entity();
	rightWall->createPolygonalShape(createRectangle(dim2, dim1), vec3(0.0f, 0.0f, 0.0f), vec4(0.6f, 0.6f, 0.6f, 1.0f), vec4(0.6f, 0.6f, 0.6f, 1.0f));
	rightWall->setXShiftValue((float)width - rightWall->getWidth() / 2 * rightWall->getXScaleValue());
	rightWall->setYShiftValue((float)height / 2);
	rightWall->setYScaleValue((float)height);

	Entity* midLeftWall = new Entity();
	midLeftWall->createPolygonalShape(createRectangle(dim2, dim1), vec3(0.0f, 0.0f, 0.0f), vec4(0.6f, 0.6f, 0.6f, 1.0f), vec4(0.6f, 0.6f, 0.6f, 1.0f));
	midLeftWall->setXShiftValue((float)width / 6 + midLeftWall->getWidth() / 2 * midLeftWall->getXScaleValue());
	midLeftWall->setYShiftValue((float)height / 2);
	midLeftWall->setYScaleValue((float)height / 2);
	Entity* midRightWall = new Entity();
	midRightWall->createPolygonalShape(createRectangle(dim2, dim1), vec3(0.0f, 0.0f, 0.0f), vec4(0.6f, 0.6f, 0.6f, 1.0f), vec4(0.6f, 0.6f, 0.6f, 1.0f));
	midRightWall->setXShiftValue((float)width - midLeftWall->getXShiftValue());
	midRightWall->setYShiftValue((float)height / 2);
	midRightWall->setYScaleValue((float)height / 2);

	vector<Entity*> walls;
	walls.push_back(bottomWall);
	walls.push_back(topWall);
	walls.push_back(leftWall);
	walls.push_back(rightWall);
	walls.push_back(midLeftWall);
	walls.push_back(midRightWall);
	return walls;
}

vector<Entity*> createEnemies(char* controlPointsFile)
{
	Entity* enemy1 = new Entity();
	vector<vec3> controlPoints = readPolygonVertices(controlPointsFile);
	enemy1->createHermiteShape(controlPoints, vec3(0.0f, 0.2f, 0.0f), vec4(1.0f, 0.0f, 0.0f, 1.0f), vec4(1.0f, 0.0f, 0.0f, 1.0f));
	enemy1->setXShiftValue((float)width / 12);
	enemy1->setYShiftValue((float)height / 3);

	Entity* enemy2 = new Entity();
	enemy2->createHermiteShape(controlPoints, vec3(0.0f, 0.2f, 0.0f), vec4(1.0f, 0.0f, 0.0f, 1.0f), vec4(1.0f, 0.0f, 0.0f, 1.0f));
	enemy2->setXShiftValue((float)width - enemy1->getXShiftValue());
	enemy2->setYShiftValue(enemy1->getYShiftValue());

	Entity* enemy3 = new Entity();
	enemy3->createHermiteShape(controlPoints, vec3(0.0f, 0.2f, 0.0f), vec4(1.0f, 0.0f, 0.0f, 1.0f), vec4(1.0f, 0.0f, 0.0f, 1.0f));
	enemy3->setXShiftValue(enemy1->getXShiftValue());
	enemy3->setYShiftValue((float)height - enemy1->getYShiftValue());

	Entity* enemy4 = new Entity();
	enemy4->createHermiteShape(controlPoints, vec3(0.0f, 0.2f, 0.0f), vec4(1.0f, 0.0f, 0.0f, 1.0f), vec4(1.0f, 0.0f, 0.0f, 1.0f));
	enemy4->setXShiftValue(enemy2->getXShiftValue());
	enemy4->setYShiftValue((float)height - enemy2->getYShiftValue());

	vector<Entity*> enemies;
	enemies.push_back(enemy1);
	enemies.push_back(enemy2);
	enemies.push_back(enemy3);
	enemies.push_back(enemy4);
	return enemies;
}