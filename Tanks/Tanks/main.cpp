#include <iostream>
#include <fstream>
#include <string>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "header_files/lib.h"
#pragma warning(disable : 4996)

const int width = 1280;
const int height = 720;

static unsigned int programID, programID_text;

GLuint textVAO, textVBO;

mat4 Projection;
GLuint MatProj, MatModel;

vector<Entity*> playerComponents;
vector<Entity*> projectiles;
vector<Entity*> walls;
vector<Entity*> enemies;
vector<vector<Entity*>*> scene;
vector<Entity*> lives;

Player* player = new Player();

void INIT_SHADER(void)
{
	GLenum ErrorCheckValue = glGetError();
	char* vertexShader = (char*)"vertexShader_M.glsl";
	char* fragmentShader = (char*)"fragmentShader_M.glsl";
	programID = ShaderMaker::createProgram(vertexShader, fragmentShader);
	glUseProgram(programID);

	//Generazione del program shader per la gestione del testo
	vertexShader = (char*)"vertexShader_Text.glsl";
	fragmentShader = (char*)"fragmentShader_Text.glsl";

	programID_text = ShaderMaker::createProgram(vertexShader, fragmentShader);
}

void INIT_VAO(void)
{
	playerComponents = createPlayer(player);
	walls = createWalls(1.0f, 0.4f);
	enemies = createEnemies((char*)"enemy.txt");
	lives = createLives(3, 0.05f, 0.4f * walls[0]->getYScaleValue());

	scene.push_back(&playerComponents);
	scene.push_back(&walls);
	scene.push_back(&projectiles);
	scene.push_back(&enemies);
	scene.push_back(&lives);

	for (vector<Entity*>* container : scene)
		for (Entity* entity : *container)
			entity->initVAO();

	Projection = ortho(0.0f, float(width), 0.0f, float(height));
	MatProj = glGetUniformLocation(programID, "Projection");
	MatModel = glGetUniformLocation(programID, "Model");

	glViewport(0, 0, width, height);
}

void shiftLeft(int index)
{
	for (int i = index; i < projectiles.size() - 1; i++)
		projectiles[i] = projectiles[i + 1];
	projectiles.pop_back();
}

void gameOver(char* text)
{
	string str(text);
	renderText(programID_text, Projection, str, textVAO, textVBO, width / 2 - 30.0f * str.length() / 2, height / 2 - 10.0f, 1.0f, vec3(1.0f, 0.0f, 0.0f));
}

void update(int value)
{
	int i = 0;
	if (checkEnemyCollision(player))
	{
		Entity* heart = lives[lives.size() - 1];
		lives.pop_back();
		delete(heart);
		if (lives.size() == 0)
			player->die();
	}
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
				(projectile->getXShiftValue() > (float)width || projectile->getXShiftValue() < 0.0f
				|| projectile->getYShiftValue() > (float)height || projectile->getYShiftValue() < 0.0f)
				|| checkEnemyCollision(projectile))
			{
				shiftLeft(i);
				player->removeProjectile(i);
				delete(projectile);
				i--;
			}
		}
		i++;
	}

	for (vector<Entity*>* container : scene)
		for (Entity* entity : *container)
			entity->updateVAO();
	if (player->isAlive() && enemies.size() > 0)
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
			*entity->getModel() = translate(*entity->getModel(), vec3(entity->getXShiftValue(), entity->getYShiftValue(), 0.0f));
			*entity->getModel() = scale(*entity->getModel(), vec3(entity->getXScaleValue(), entity->getYScaleValue(), 1.0f));
			*entity->getModel() = rotate(*entity->getModel(), radians(entity->getRotationValue()), vec3(0.0f, 0.0f, 1.0f));
			glUniformMatrix4fv(MatProj, 1, GL_FALSE, value_ptr(Projection));
			glUniformMatrix4fv(MatModel, 1, GL_FALSE, value_ptr(*entity->getModel()));
			glBindVertexArray(*entity->getVAO());
			glDrawArrays(GL_TRIANGLE_FAN, 0, entity->getNumberOfVertices());
			glBindVertexArray(0);
		}
	}
	if (player->isAlive() && enemies.size() == 0)
		gameOver((char*)"YOU WIN");
	else if (!player->isAlive())
		gameOver((char*)"YOU LOSE");
	string str = "Enemies left: " + to_string(enemies.size());
	renderText(programID_text, Projection, str, textVAO, textVBO, width - 12.0f * str.length(), height - walls[0]->getHeight() * walls[0]->getYScaleValue() * 2 - 10.0f, 0.5f, vec3(1.0f, 0.0f, 0.0f));
	glutSwapBuffers();
	glUseProgram(programID);
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
	initTextVAO(&textVAO, &textVBO);
	initFreetype();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glutTimerFunc(17, update, 0);
	glutKeyboardFunc(keyboard);
	glutPassiveMotionFunc(mouseMovement);
	glutMainLoop();
}