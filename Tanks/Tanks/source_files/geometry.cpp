#include "../header_files/geometry.h"

#define PI 3.14159265358979323846

vector<vec3> createCircle(float rx, float ry, int precision)
{
	float step = 2 * PI / precision;
	vector<vec3> vertices;
	for (int i = 0; i <= precision + 2; i++) {
		float theta_i = (float)i * step;
		vertices.push_back(vec3(rx * cos(theta_i), ry * sin(theta_i), 0.0f));
	}
	return vertices;
}

void create_moon(float cx, float cy, float rx, float ry, Shape* shape, vec4 color1, vec4 color2)
{
	float step = 2 * PI / shape->nTriangles;
	shape->vertices.push_back(vec3(cx, cy, 0.0f));
	shape->colors.push_back(color1);
	for (int i = 0; i <= shape->nTriangles + 2; i++) {
		float theta_i = (float)i * step;
		float x = cx - rx * (0.5f - cos(2 * theta_i) - cos(theta_i));
		float y = cy - ry * 3 * sin(theta_i);
		shape->vertices.push_back(vec3(x, y, 0.0f));
		shape->colors.push_back(color2);
	}
	shape->nVertices = shape->vertices.size();
}

vector<vec3> createHeart(float rx, float ry, int precision)
{
	float step = 2 * PI / precision;
	vector<vec3> vertices;
	for (int i = 0; i <= precision + 2; i++) {
		float theta_i = (float)i * step;
		float x = rx * 16 * pow(sin(theta_i), 3);
		float y = ry * (13 * cos(theta_i) - 5 * cos(2 * theta_i) - 2 * cos(3 * theta_i) - cos(4 * theta_i));
		vertices.push_back(vec3(x, y, 0.0f));
	}
	return vertices;
}

void create_butterfly(float cx, float cy, float rx, float ry, Shape* shape, vec4 color1, vec4 color2)
{
	float step = 2 * PI / shape->nTriangles;
	shape->vertices.push_back(vec3(cx, cy, 0.0f));
	shape->colors.push_back(color1);
	for (int i = 0; i <= shape->nTriangles + 2; i++) {
		float theta_i = (float)i * step;
		float x = cx + rx * (sin(theta_i) * exp(cos(theta_i) - 2 * cos(4 * theta_i) + pow(sin(theta_i / 12), 3)));
		float y = cy + ry * (cos(theta_i) * exp(cos(theta_i) - 2 * cos(4 * theta_i) - pow(sin(theta_i / 12), 3)));
		shape->vertices.push_back(vec3(x, y, 0.0f));
		shape->colors.push_back(color2);
	}
	shape->nVertices = shape->vertices.size();
}

vector<vec3> createRectangle(float width, float height)
{
	vector<vec3> vertices;
	vertices.push_back(vec3(width / 2, -height / 2, 0.0f));
	vertices.push_back(vec3(width / 2, height / 2, 0.0f));
	vertices.push_back(vec3(-width / 2, height / 2, 0.0f));
	vertices.push_back(vec3(-width / 2, -height / 2, 0.0f));
	vertices.push_back(vec3(width / 2, -height / 2, 0.0f));
	return vertices;
}