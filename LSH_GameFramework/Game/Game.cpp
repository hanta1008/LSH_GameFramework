#include "Game.h"
#include "iOpenGL.h"

void loadGame()
{

}
void freeGame()
{

}
void drawGame(float dt)
{
	useShaderProgram();
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}
void keyGame()
{

}