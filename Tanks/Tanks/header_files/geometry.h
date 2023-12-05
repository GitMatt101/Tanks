#pragma once
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
using namespace glm;
using namespace std;

typedef struct {
	GLuint VAO;
	GLuint VBO_V;
	GLuint VBO_C;
	GLuint EBOindexes;
	int nTriangles;
	vector<vec3> vertices;
	vector<vec4> colors;
	vector<vec3> cpCoordinates;	// Coordinate dei punti di controllo
	vector<vec4> cpColors;		// Colori dei punti di controllo
	int nVertices;				// Numero massimo di punti in cui viene disegnata la curve
	int nCP;					// Numero massimo di punti di controllo (punti di interpolazione)
	mat4 model;					// Matrice di modellazione: traslazione * rotazione * scala
	float shiftValue;			// Valore di traslazione
	float scaleValue;			// Valore di scalatura
	float rotationValue;		// Valore di rotazione
} Shape;

vector<vec3> createCircle(float rx, float ry, int precision);

void create_moon(float cx, float cy, float rx, float ry, Shape* shape, vec4 color1, vec4 color2);

vector<vec3> createHeart(float rx, float ry, int precision);

void create_butterfly(float cx, float cy, float rx, float ry, Shape* shape, vec4 color1, vec4 color2);

vector<vec3> createRectangle(float width, float height);