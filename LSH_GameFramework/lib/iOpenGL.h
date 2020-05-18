#pragma once

#include <gl/glew.h>
#include <gl/wglew.h>
#pragma comment(lib, "opengl32")

#include <stdlib.h>
#include <stdio.h>

extern GLuint vertexShader;
extern GLuint fragShader;
extern GLuint programID;

extern GLuint VAO;

typedef struct _Vertex {
	float position[4];
	float color[4];
	float texcoord[2];
} Vertex;

void initOpenGL();
void freeOpenGL();

void loadShader();
void loadVAO();
void useShaderProgram();

void reshapeOpenGL();
