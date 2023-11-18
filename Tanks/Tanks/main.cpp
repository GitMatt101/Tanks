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

vector<Entity*> scene;
Player player;

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
	player.initVAO();
	player.getCannon()->initVAO();
	player.getCockpit()->initVAO();
	scene.push_back(&player);
	scene.push_back(player.getCannon());
	scene.push_back(player.getCockpit());

	Projection = ortho(0.0f, float(width), 0.0f, float(height));
	MatProj = glGetUniformLocation(programId, "Projection");
	MatModel = glGetUniformLocation(programId, "Model");

	glViewport(0, 0, width, height);
}

void update(int value)
{
	player.updateVAO();
	for (int i = 0; i < scene.size(); i++)
		scene[i]->updateVAO();
	glutTimerFunc(50, update, 0);
	glutPostRedisplay();
}

void drawScene(void)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	for (int i = 0; i < scene.size(); i++) {
		*scene[i]->getModel() = mat4(1.0);
		*scene[i]->getModel() = translate(*scene[i]->getModel(), vec3((float)width / 2 + scene[i]->getXShiftValue(), (float)height / 2 + scene[i]->getYShiftValue(), 0.0f));
		*scene[i]->getModel() = scale(*scene[i]->getModel(), vec3(scene[i]->getScaleValue(), scene[i]->getScaleValue(), 1.0f));
		*scene[i]->getModel() = rotate(*scene[i]->getModel(), radians(scene[i]->getRotationValue()), vec3(0.0f, 0.0f, 1.0f));

		glUniformMatrix4fv(MatProj, 1, GL_FALSE, value_ptr(Projection));
		glUniformMatrix4fv(MatModel, 1, GL_FALSE, value_ptr(*scene[i]->getModel()));
		glBindVertexArray(*scene[i]->getVAO());
		glDrawArrays(GL_TRIANGLE_FAN, 0, scene[i]->getNumberOfVertices());
		glBindVertexArray(0);
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