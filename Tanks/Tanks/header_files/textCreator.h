#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
using namespace std;
using namespace glm;

typedef struct {
	unsigned int TextureID; // ID handle of the glyph texture
	ivec2   Size;			// Size of glyph
	ivec2   Bearing;		// Offset from baseline to left/top of glyph
	unsigned int Advance;   // Horizontal offset to advance to next glyph
} Character;

void initFreetype();

void renderText(int programID, mat4 textProjectionMatrix, string text, unsigned int textVAO, unsigned int textVBO, float x, float y, float scale, glm::vec3 color);