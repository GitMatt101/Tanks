#include "../header_files/entities.h"
#include <math.h>
#include "../header_files/VAO_manager.h"
#include "../header_files/interactions.h"
#include "../header_files/hermite.h"

#define DEFAULT_SIZE 25.0f
#define DEFAULT_PROJECTILE_SPEED 10.0f
#define P_VAL 100

Entity::Entity()
{
	alive = true;
	xShiftValue = 0.0f;
	yShiftValue = 0.0f;
	xScaleValue = DEFAULT_SIZE;
	yScaleValue = DEFAULT_SIZE;
	rotationValue = 0.0f;
}

void Entity::createPolygonalShape(vector<vec3> polygonVertices, vec3 center, vec4 color1, vec4 color2)
{
	vertices.push_back(center);
	colors.push_back(color2);
	float xMin = polygonVertices[0].x;
	float yMin = polygonVertices[0].y;
	float xMax = polygonVertices[0].x;
	float yMax = polygonVertices[0].y;
	for (vec3 vertex : polygonVertices) {
		vertices.push_back(vec3(vertex.x, vertex.y, 0.0f));
		colors.push_back(color1);
		if (vertex.x < xMin)
			xMin = vertex.x;
		else if (vertex.x > xMax)
			xMax = vertex.x;
		if (vertex.y < yMin)
			yMin = vertex.y;
		else if (vertex.y > yMax)
			yMax = vertex.y;
	}
	hitbox.cornerBot = vec3(xMin, yMin, 0.0f);
	hitbox.cornerTop = vec3(xMax, yMax, 0.0f);
}

void Entity::createHermiteShape(vector<vec3> controlPoints, vec3 center, vec4 color1, vec4 color2)
{
	Shape derivative;
	Shape polygonal;
	polygonal.cpCoordinates = controlPoints;
	float* t = new float[polygonal.cpCoordinates.size()];
	for (int i = 0; i < polygonal.cpCoordinates.size(); i++)
		t[i] = (float)i / (float)(polygonal.cpCoordinates.size() - 1);

	float p_t = 0, p_b = 0, p_c = 0;
	float passotg = 1.0f / (float)(P_VAL - 1);

	float tgmapp, ampiezza;
	int is = 0;

	vertices.push_back(center);
	colors.push_back(color2);

	for (int i = 0; i < controlPoints.size(); i++)
		derivative.cpCoordinates.push_back(vec3(0.0f, 0.0f, 0.0f));

	for (float tg = 0.0f; tg <= 1.0f; tg += passotg)
	{
		if (tg > t[is + 1])
			is++;
		ampiezza = (t[is + 1] - t[is]);
		tgmapp = (tg - t[is]) / ampiezza;

		float x = controlPoints[is].x * PHI0(tgmapp) + DX(is, t, &derivative, &polygonal) * PHI1(tgmapp) * ampiezza + controlPoints[is + 1].x * PSI0(tgmapp) + DX(is + 1, t, &derivative, &polygonal) * PSI1(tgmapp) * ampiezza;
		float y = controlPoints[is].y * PHI0(tgmapp) + DY(is, t, &derivative, &polygonal) * PHI1(tgmapp) * ampiezza + controlPoints[is + 1].y * PSI0(tgmapp) + DY(is + 1, t, &derivative, &polygonal) * PSI1(tgmapp) * ampiezza;

		vertices.push_back(vec3(x, y, 0.0f));
		colors.push_back(color1);
	}
	vertices.push_back(controlPoints[controlPoints.size() - 1]);
	colors.push_back(color1);
	float xMin = vertices[0].x;
	float yMin = vertices[0].y;
	float xMax = vertices[0].x;
	float yMax = vertices[0].y;
	for (vec3 vertex : vertices)
	{
		if (vertex.x < xMin)
			xMin = vertex.x;
		else if (vertex.x > xMax)
			xMax = vertex.x;
		if (vertex.y < yMin)
			yMin = vertex.y;
		else if (vertex.y > yMax)
			yMax = vertex.y;
	}
	hitbox.cornerBot = vec3(xMin, yMin, 0.0f);
	hitbox.cornerTop = vec3(xMax, yMax, 0.0f);
}

void Entity::initVAO()
{
	initShapeVAO(this);
}

void Entity::updateVAO()
{
	updateShapeVAO(this);
}

GLuint* Entity::getVAO()
{
	return &VAO;
}

GLuint* Entity::getVerticesVBO()
{
	return &VBO_V;
}

GLuint* Entity::getColorsVBO()
{
	return &VBO_C;
}

vector<vec3>* Entity::getVertices()
{
	return &vertices;
}

vector<vec4>* Entity::getVerticesColors()
{
	return &colors;
}

int Entity::getNumberOfVertices()
{
	return vertices.size();
}

int Entity::getNumberOfControlPoints()
{
	return nCP;
}

mat4* Entity::getModel()
{
	return &model;
}

float Entity::getXShiftValue()
{
	return xShiftValue;
}

float Entity::getYShiftValue()
{
	return yShiftValue;
}

float Entity::getXScaleValue()
{
	return xScaleValue;
}

float Entity::getYScaleValue()
{
	return yScaleValue;
}

float Entity::getRotationValue()
{
	return rotationValue;
}

void Entity::setXShiftValue(float value)
{
	xShiftValue = value;
}

void Entity::setYShiftValue(float value)
{
	yShiftValue = value;
}

void Entity::setXScaleValue(float value)
{
	xScaleValue = value;
}

void Entity::setYScaleValue(float value)
{
	yScaleValue = value;
}

void Entity::setRotationValue(float value)
{
	rotationValue = value;
}

Hitbox Entity::getHitbox()
{
	return hitbox;
}

vec3 Entity::getMidPoint()
{
	float x = (hitbox.cornerBot.x + hitbox.cornerTop.x) / 2;
	float y = (hitbox.cornerBot.y + hitbox.cornerTop.y) / 2;
	return vec3(x, y, 0.0f);
}

float Entity::getWidth()
{
	return hitbox.cornerTop.x - hitbox.cornerBot.x;
}

float Entity::getHeight()
{
	return hitbox.cornerTop.y - hitbox.cornerBot.y;
}

Hitbox Entity::getHitboxWorldCoordinates()
{
	float xBottom = (float)width / 2 + hitbox.cornerBot.x * xScaleValue + xShiftValue;
	float yBottom = (float)height / 2 + hitbox.cornerBot.y * yScaleValue + yShiftValue;
	float xTop = (float)width / 2 + hitbox.cornerTop.x * xScaleValue + xShiftValue;
	float yTop = (float)height / 2 + hitbox.cornerTop.y * yScaleValue + yShiftValue;
	return { vec3(xBottom, yBottom, 0.0f), vec3(xTop, yTop, 0.0f) };
}



Player::Player() 
{
	vec4 color1 = vec4(0.0f, 0.2f, 0.0f, 1.0f);
	vec4 color2 = vec4(0.6f, 0.2f, 0.2f, 1.0f);
	vec3 center = vec3(0.0f, 0.0f, 0.0f);
	createPolygonalShape(createRectangle(1.2f, 2.0f), center, color1, color2);
	cannon = new Entity();
	cockpit = new Entity();
	cannon->createPolygonalShape(createRectangle(0.2f, 1.6f), vec3(0.0f, 0.0f, 0.0f), vec4(0.3f, 0.3f, 0.3f, 1.0f), vec4(0.3f, 0.3f, 0.3f, 1.0f));
	cannon->setYShiftValue((cannon->getHitbox().cornerTop.y - cannon->getHitbox().cornerBot.y) / 2 * cannon->getYScaleValue());
	cockpit->createPolygonalShape(createCircle(vec3(0.0f, 0.0f, 0.0f), 0.3f, 0.3f, 100), vec3(0.0f, 0.0f, 0.0f), vec4(0.0f, 0.3f, 0.0f, 1.0f), vec4(0.0f, 0.3f, 0.0f, 1.0f));
}

Entity* Player::getCannon()
{
	return cannon;
}

Entity* Player::getCockpit()
{
	return cockpit;
}

vector<Projectile*> Player::getProjectiles()
{
	return projectiles;
}

void Player::shoot()
{
	float x = xShiftValue + 2 * (cannon->getXShiftValue() - xShiftValue);
	float y = yShiftValue + 2 * (cannon->getYShiftValue() - yShiftValue);
	Projectile* projectile = new Projectile(x, y, cannon->getRotationValue());
	projectiles.push_back(projectile);
}

void Player::removeProjectile(int index)
{
	for (int i = index; i < projectiles.size() - 1; i++)
		projectiles[i] = projectiles[i + 1];
	projectiles.pop_back();
}

void Player::rotateHitbox()
{
	vec4 t1 = vec4(hitbox.cornerBot.x, hitbox.cornerTop.y, 0.0f, 1.0f);
	vec4 b1 = vec4(hitbox.cornerTop.x, hitbox.cornerBot.y, 0.0f, 1.0f);
	mat4 model = mat4(1.0);
	model = rotate(model, radians(-90.0f), vec3(0.0f, 0.0f, 1.0f));
	hitbox.cornerTop = model * t1;
	hitbox.cornerBot = model * b1;
}



Projectile::Projectile(float x, float y, float angle)
{
	m = tan(radians(90.0f + angle));
	rotationValue = angle;
	xShiftValue = x;
	yShiftValue = y;
	xShift = DEFAULT_PROJECTILE_SPEED * cos(radians(90.0f + angle));
	yShift = m * xShift;
	float greyScale = 0.3f;
	createHermiteShape(readPolygonVertices((char*)"projectile.txt"), vec3(0.0f, 0.0f, 0.0f), vec4(greyScale, greyScale, greyScale, 1.0f), vec4(greyScale, greyScale, greyScale, 1.0f));
	xScaleValue = (float)DEFAULT_SIZE * 2 / 3;
	yScaleValue = (float)DEFAULT_SIZE * 2 / 3;
	inScene = false;
	bounces = 0;
}

void Projectile::updatePosition()
{
	if (checkWallCollision(this, xShift, 0.0f))
	{
		rotationValue = -rotationValue;
		xShift = -xShift;
		bounces++;
	}
	else if (checkWallCollision(this, 0.0f, yShift))
	{
		rotationValue = 540.0f - rotationValue;
		yShift = -yShift;
		bounces++;
	}
	xShiftValue += xShift;
	yShiftValue += yShift;
}

bool Projectile::isInScene()
{
	return inScene;
}

void Projectile::changeStatus()
{
	inScene = inScene ? false : true;
}

int Projectile::getNumberOfBounces()
{
	return bounces;
}
