#include "iOpenGL.h"

const char* strVertShader = "							\
#version 330 core\n										\
layout(location = 0) in vec3 aPos;						\
														\
void main()												\
{														\
	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);	\
}														\
";

const char* strFragShader = "							\
#version 330 core\n										\
out vec4 FragColor;										\
														\
void main()												\
{														\
	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);			\
}														\
";

Vertex _vertex_[4] = {
	{ {-0.5, -0.5, 0.0, 1.0}, {1.0, 0.0, 0.0, 1.0}, {0.0, 1.0} },
	{ {-0.5,  0.5, 0.0, 1.0}, {0.0, 1.0, 0.0, 1.0}, {0.0, 0.0} },
	{ { 0.5,  0.5, 0.0, 1.0}, {0.0, 0.0, 1.0, 1.0}, {1.0, 0.0} },
	{ { 0.5, -0.5, 0.0, 1.0}, {1.0, 1.0, 1.0, 1.0}, {1.0, 1.0} },
};

float vertices[] = {
	  -0.5f, -0.5f, 0.0f, // left  
	   0.5f, -0.5f, 0.0f, // right 
	   0.0f,  0.5f, 0.0f  // top   
};


void initOpenGL()
{
	loadShader();
	loadVAO();

	glFrontFace(GL_CCW);// GL_GW
	glDisable(GL_CULL_FACE);

	glEnable(GL_BLEND);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glClearDepth(1.0f);
}

void freeOpenGL()
{

}

GLuint createShader(GLuint shader, const char* source)
{
	GLuint shaderID = glCreateShader(shader);
	glShaderSource(shaderID, 1, &source, NULL);
	glCompileShader(shaderID);

	int  success;
	char infoLog[512];
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
	if (!success )
	{
		glGetShaderInfoLog(shaderID, 512, NULL, infoLog);
		if(shader == GL_VERTEX_SHADER)
			printf("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n%s\n", infoLog);
		else if(shader == GL_FRAGMENT_SHADER)
			printf("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n%s\n", infoLog);
		return NULL;
	}

	return shaderID;
}
void freeShaderID(GLuint id)
{
	glDeleteShader(id);
}

GLuint createShaderProgram(GLuint vertexID, GLuint fragID)
{
	GLuint shaderProgramID;
	shaderProgramID = glCreateProgram();
	glAttachShader(shaderProgramID, vertexID);
	glAttachShader(shaderProgramID, fragID);
	glLinkProgram(shaderProgramID);
	glDetachShader(shaderProgramID, vertexID);
	glDetachShader(shaderProgramID, fragID);

	int  success;
	char infoLog[512];
	glGetProgramiv(shaderProgramID, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgramID, 512, NULL, infoLog);
		printf("ERROR::SHADER::PROGRAMID::COMPILATION_FAILED\n%s\n", infoLog);

		return NULL;
	}

	return shaderProgramID;
}
void useShaderProgram()
{
	glUseProgram(programID);
}
void freeShaderProgram()
{
	glDeleteProgram(programID);
}

GLuint vertexShader, fragShader, programID;
void loadShader()
{
	vertexShader = createShader(GL_VERTEX_SHADER, strVertShader);
	fragShader = createShader(GL_FRAGMENT_SHADER, strFragShader);
	programID = createShaderProgram(vertexShader, fragShader);

	if (!vertexShader || !fragShader || !programID)
	{
		printf("ERROR::LOADSHADER_FAILED\N");
		return;
	}
	useShaderProgram();
	freeShaderID(vertexShader);
	freeShaderID(fragShader);
}

GLuint VBO, VAO;
void loadVAO()
{
	//VBO
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_VERTEX_ARRAY, VBO);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex), _vertex_, GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//VAO
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
}
void freeVAO()
{
	//VBO
	glDeleteBuffers(1, &VBO);

	//VAO
	glDeleteVertexArrays(1, &VAO);
}

