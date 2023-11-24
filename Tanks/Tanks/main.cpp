#include <iostream>
#include <fstream>
#include <string>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "header files/lib.h"
#pragma warning(disable : 4996)

const int width = 1280;
const int height = 720;

static unsigned int programId;

mat4 Projection;
GLuint MatProj, MatModel;

vector<Entity*> playerComponents;
vector<Entity*> projectiles;
vector<Entity*> walls;
vector<vector<Entity*>*> scene;

Player* player = new Player();

void INIT_SHADER(void)
{
	GLenum ErrorCheckValue = glGetError();
	char* vertexShader = (char*)"vertexShader_M.glsl";
	char* fragmentShader = (char*)"fragmentShader_M.glsl";
	programId = ShaderMaker::createProgram(vertexShader, fragmentShader);
	glUseProgram(programId);
}

void INIT_VAO(void)
{
	player->initVAO();
	player->getCannon()->initVAO();
	player->getCockpit()->initVAO();
	playerComponents.push_back(player);
	playerComponents.push_back(player->getCannon());
	playerComponents.push_back(player->getCockpit());
	
	float dim1 = 1.0f;
	float dim2 = 0.4f;

	Entity* bottomWall = new Entity();
	bottomWall->createPolygonalShape(createRectangle(dim1, dim2), vec3(0.0f, 0.0f, 0.0f), vec4(0.6f, 0.6f, 0.6f, 1.0f), vec4(0.6f, 0.6f, 0.6f, 1.0f));
	bottomWall->setYShiftValue(-(float)height / 2 + bottomWall->getHeight() / 2 * bottomWall->getYScaleValue());
	bottomWall->setXScaleValue((float)width);
	walls.push_back(bottomWall);
	Entity* topWall = new Entity();
	topWall->createPolygonalShape(createRectangle(dim1, dim2), vec3(0.0f, 0.0f, 0.0f), vec4(0.6f, 0.6f, 0.6f, 1.0f), vec4(0.6f, 0.6f, 0.6f, 1.0f));
	topWall->setYShiftValue((float)height / 2 - topWall->getHeight() / 2 * topWall->getYScaleValue());
	topWall->setXScaleValue((float)width);
	walls.push_back(topWall);

	Entity* leftWall = new Entity();
	leftWall->createPolygonalShape(createRectangle(dim2, dim1), vec3(0.0f, 0.0f, 0.0f), vec4(0.6f, 0.6f, 0.6f, 1.0f), vec4(0.6f, 0.6f, 0.6f, 1.0f));
	leftWall->setXShiftValue(-(float)width / 2 + leftWall->getWidth() / 2 * leftWall->getXScaleValue());
	leftWall->setYScaleValue((float)height);
	walls.push_back(leftWall);
	Entity* rightWall = new Entity();
	rightWall->createPolygonalShape(createRectangle(dim2, dim1), vec3(0.0f, 0.0f, 0.0f), vec4(0.6f, 0.6f, 0.6f, 1.0f), vec4(0.6f, 0.6f, 0.6f, 1.0f));
	rightWall->setXShiftValue((float)width / 2 - rightWall->getWidth() / 2 * rightWall->getXScaleValue());
	rightWall->setYScaleValue((float)height);
	walls.push_back(rightWall);

	Entity* midLeftWall = new Entity();
	midLeftWall->createPolygonalShape(createRectangle(dim2, dim1), vec3(0.0f, 0.0f, 0.0f), vec4(0.6f, 0.6f, 0.6f, 1.0f), vec4(0.6f, 0.6f, 0.6f, 1.0f));
	midLeftWall->setXShiftValue(-(float)width / 4 + midLeftWall->getWidth() / 2 * midLeftWall->getXScaleValue());
	midLeftWall->setYScaleValue((float)height / 2);
	walls.push_back(midLeftWall);
	Entity* midRightWall = new Entity();
	midRightWall->createPolygonalShape(createRectangle(dim2, dim1), vec3(0.0f, 0.0f, 0.0f), vec4(0.6f, 0.6f, 0.6f, 1.0f), vec4(0.6f, 0.6f, 0.6f, 1.0f));
	midRightWall->setXShiftValue((float)width / 4 - midRightWall->getWidth() / 2 * midRightWall->getXScaleValue());
	midRightWall->setYScaleValue((float)height / 2);
	walls.push_back(midRightWall);

	for (Entity* wall : walls)
		wall->initVAO();

	scene.push_back(&playerComponents);
	scene.push_back(&projectiles);
	scene.push_back(&walls);
	Projection = ortho(0.0f, float(width), 0.0f, float(height));
	MatProj = glGetUniformLocation(programId, "Projection");
	MatModel = glGetUniformLocation(programId, "Model");

	glViewport(0, 0, width, height);
}

void shiftLeft(int index)
{
	for (int i = index; i < projectiles.size() - 1; i++)
		projectiles[i] = projectiles[i + 1];
	projectiles.pop_back();
}

void update(int value)
{
	int i = 0;
	for (Projectile* projectile : player->getProjectiles())
	{
		if (!projectile->isInScene())
		{
			projectile->changeStatus();
			projectile->initVAO();
			projectiles.push_back(projectile);
		}
		else
		{
			projectile->updatePosition();
			if (projectile->getNumberOfBounces() > 2 || 
				((float)width / 2 + projectile->getXShiftValue() > (float)width || (float)width / 2 + projectile->getXShiftValue() < 0.0f
				|| (float)height / 2 + projectile->getYShiftValue() > (float)height || (float)height / 2 + projectile->getYShiftValue() < 0.0f))
			{
				shiftLeft(i);
				player->removeProjectile(i);
				delete(projectile);
				i--;
			}
		}
		i++;
	}

	for (Entity* component : playerComponents)
		component->updateVAO();
	for (Entity* projectile : projectiles)
		projectile->updateVAO();
	for (Entity* wall : walls)
		wall->updateVAO();
	glutTimerFunc(17, update, 0);
	glutPostRedisplay();
}

void drawScene(void)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	for (vector<Entity*>* container : scene)
	{
		for (Entity* entity : *container)
		{
			*entity->getModel() = mat4(1.0);
			*entity->getModel() = translate(*entity->getModel(), vec3((float)width / 2 + entity->getXShiftValue(), (float)height / 2 + entity->getYShiftValue(), 0.0f));
			*entity->getModel() = scale(*entity->getModel(), vec3(entity->getXScaleValue(), entity->getYScaleValue(), 1.0f));
			*entity->getModel() = rotate(*entity->getModel(), radians(entity->getRotationValue()), vec3(0.0f, 0.0f, 1.0f));
			glUniformMatrix4fv(MatProj, 1, GL_FALSE, value_ptr(Projection));
			glUniformMatrix4fv(MatModel, 1, GL_FALSE, value_ptr(*entity->getModel()));
			glBindVertexArray(*entity->getVAO());
			glDrawArrays(GL_TRIANGLE_FAN, 0, entity->getNumberOfVertices());
			glBindVertexArray(0);
		}
	}
	glutSwapBuffers();
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitContextVersion(4, 0);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("Tanks");
	glutDisplayFunc(drawScene);
	glewExperimental = GL_TRUE;
	glewInit();
	INIT_SHADER();
	INIT_VAO();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glutTimerFunc(50, update, 0);
	glutKeyboardFunc(keyboard);
	glutPassiveMotionFunc(mouseMovement);
	glutMainLoop();
}