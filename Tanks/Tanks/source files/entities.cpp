#include "../header files/entities.h"
#include "../header files/VAO_manager.h"

#define DEFAULT_SIZE 50.0f

Entity::Entity()
{
	alive = true;
	xShiftValue = 0.0f;
	yShiftValue = 0.0f;
	scaleValue = DEFAULT_SIZE;
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
	for (int i = 0; i < polygonVertices.size(); i++) {
		vertices.push_back(vec3(polygonVertices[i].x, polygonVertices[i].y, 0.0f));
		colors.push_back(color1);
		if (polygonVertices[i].x < xMin)
			xMin = polygonVertices[i].x;
		else if (polygonVertices[i].x > xMax)
			xMax = polygonVertices[i].x;
		if (polygonVertices[i].y < yMin)
			yMin = polygonVertices[i].y;
		else if (polygonVertices[i].y > yMax)
			yMax = polygonVertices[i].y;
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

float Entity::getScaleValue()
{
	return scaleValue;
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

void Entity::setScaleValue(float value)
{
	scaleValue = value;
}

void Entity::setRotationValue(float value)
{
	rotationValue = value;
}

Hitbox Entity::getHitbox()
{
	return hitbox;
}



Player::Player() 
{
	Entity();
	vec4 color1 = vec4(0.0f, 0.3f, 0.0f, 1.0f);
	vec4 color2 = vec4(0.7f, 0.2f, 0.2f, 1.0f);
	vec3 center = vec3(0.0f, 0.0f, 0.0f);
	createPolygonalShape(createRectangle(1.2f, 1.8f), center, color1, color2);
	direction = RIGHT;
	cannon.createPolygonalShape(createRectangle(0.2f, 1.6f), vec3(0.0f, 0.0f, 0.0f), vec4(0.0f, 0.3f, 0.0f, 1.0f), vec4(0.0f, 0.3f, 0.0f, 1.0f));
	cannon.setYShiftValue((cannon.getHitbox().cornerTop.y - cannon.getHitbox().cornerBot.y) / 2 * cannon.getScaleValue());
}

Entity* Player::getCannon()
{
	return &cannon;
}

Direction Player::getDirection()
{
	return direction;
}