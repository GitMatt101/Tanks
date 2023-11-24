#include "../header files/entities.h"
#include "../header files/VAO_manager.h"
#include <math.h>
#include "../header files/interactions.h"

#define DEFAULT_SIZE 50.0f

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

vector<vec3>* Entity::getControlPointsCoordinates()
{
	return &cpCoordinates;
}

vector<vec4>* Entity::getControlPointsColors()
{
	return &cpColors;
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
	xShiftValue = x;
	yShiftValue = y;
	xShift = 5.0f * cos(radians(90.0f + angle));
	yShift = m * xShift;
	createPolygonalShape(createCircle(vec3(0.0f, 0.0f, 0.0f), 1.0f, 1.0f, 100), vec3(0.0f, 0.0f, 0.0f), vec4(0.4f, 0.4f, 0.4f, 1.0f), vec4(0.4f, 0.4f, 0.4f, 1.0f));
	xScaleValue = 5.0f;
	yScaleValue = 5.0f;
	inScene = false;
}

void Projectile::updatePosition()
{
	if (checkWallCollision(this, xShift, 0.0f))
		xShift = -xShift;
	else if (checkWallCollision(this, 0.0f, yShift))
		yShift = -yShift;
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
