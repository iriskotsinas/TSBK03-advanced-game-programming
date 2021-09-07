// Revised 2019 with a bit better variable names.

// This worked 2015: 
// Linux: gcc lab0.c ../common/*.c ../common/Linux/MicroGlut.c -lGL -o lab0 -I../common -I../common/Linux
// Mac: gcc lab0.c ../common/*.c ../common/Mac/MicroGlut.m -o lab0 -framework OpenGL -framework Cocoa -I../common/Mac -I../common

#ifdef __APPLE__
	#include <OpenGL/gl3.h>
	#include "MicroGlut.h"
	//uses framework Cocoa
#else
	#include <GL/gl.h>
	#include "MicroGlut.h"
#endif
#include "GL_utilities.h"
#include "VectorUtils3.h"
#include "LittleOBJLoader.h"
#include "LoadTGA.h"

//constants
const int initWidth=512, initHeight=512;
unsigned int angle = 45;

// Model-to-world matrix
// Modify this matrix.
// See below for how it is applied to your model.
//mat4 modelToWorld = {{ 1.0, 0.0, 0.0, 0.0,
//                              0.0, 1.0, 0.0, 0.0,
//                              0.0, 0.0, 1.0, 0.0,
//                              0.0, 0.0, 0.0, 1.0}};
mat4 bunnyModel = {{ 1.0, 0.0, 0.0, -0.5,
                    0.0, 1.0, 0.0, 0.0,
                    0.0, 0.0, 1.0, -3,
                    0.0, 0.0, 0.0, 1.0}};
vec3 bunnyColor = {1,0.6,0.2};

mat4 teddyModel = {{ 1.0, 0.0, 0.0, 0.5,
                    0.0, 1.0, 0.0, 0.0,
                    0.0, 0.0, 1.0, -4,
                    0.0, 0.0, 0.0, 1.0}};
vec3 teddyColor = {0.6,0.2,1};
// World-to-view matrix. Usually set by lookAt() or similar.
mat4 worldToView;
// Projection matrix, set by a call to perspective().
mat4 projectionMatrix;

vec3 lightPos = {1,1,1};
vec3 lightColor = {1,1,1};

// Globals
// * Model(s)
Model *bunny;
Model *teddy;
// * Reference(s) to shader program(s)
GLuint program;
// * Texture(s)
GLuint texture;

void init(void)
{
	dumpInfo();

	// GL inits
	glClearColor(0.2,0.2,0.5,0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	printError("GL inits"); // This is merely a vague indication of where something might be wrong

	projectionMatrix = perspective(90, 1.0, 0.1, 1000);
	worldToView = lookAt(0, 0, 1.5, 0, 0, 0, 0, 1, 0);

	// Load and compile shader
	program = loadShaders("lab0.vert", "lab0.frag");
	printError("init shader");
	
	// Upload geometry to the GPU:
	bunny = LoadModelPlus("objects/stanford-bunny.obj");
    teddy = LoadModelPlus("objects/teddy.obj");
	printError("load models");

	// Load textures
	LoadTGATextureSimple("textures/maskros512.tga",&texture);
	printError("load textures");
}


void display(void)
{
	printError("pre display");

	// clear the screen
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    
    GLfloat t = (GLfloat)glutGet(GLUT_ELAPSED_TIME);
    bunnyModel.m[0] = cos(angle+t*0.01);
    bunnyModel.m[2] = sin(angle+t*0.01);
    bunnyModel.m[8] = -sin(angle+t*0.01);
    bunnyModel.m[10] = cos(angle+t*0.01);

	//activate the program, and set its variables
	glUseProgram(program);
	glUniformMatrix4fv(glGetUniformLocation(program, "projectionMatrix"), 1, GL_TRUE, projectionMatrix.m);
//	mat4 modelToWorldToView = Mult(worldToView, bunnyModel); // Combine to one matrix
	glUniformMatrix4fv(glGetUniformLocation(program, "modelToWorldToView"), 1, GL_TRUE, bunnyModel.m);
    glUniform3f(glGetUniformLocation(program, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
    glUniform3f(glGetUniformLocation(program, "lightColor"), lightColor.x, lightColor.y, lightColor.z);
    glUniform3f(glGetUniformLocation(program, "object_color"), bunnyColor.x, bunnyColor.y, bunnyColor.z);
    
	//draw the model
	DrawModel(bunny, program, "in_Position", "in_Normal", NULL);
    
//    glUniform1i(glGetUniformLocation(program, "example_texture"), 0);
//    glActiveTexture(GL_TEXTURE0); //which texture-unit is active
//    glBindTexture(GL_TEXTURE_2D, texture); //load the texture to active texture-unit
    
    //Texture
    glUniform1i(glGetUniformLocation(program,"example_texture"),0);//the last argument has to be the same as the texture-unit that is to be used
    glActiveTexture(GL_TEXTURE0);//which texture-unit is active
    glBindTexture(GL_TEXTURE_2D, texture);//load the texture to active texture-unit
    
    glUniformMatrix4fv(glGetUniformLocation(program, "modelToWorldToView"), 1, GL_TRUE, teddyModel.m);
    glUniform3f(glGetUniformLocation(program, "object_color"), teddyColor.x, teddyColor.y, teddyColor.z);
    
    DrawModel(teddy, program, "in_Position", "in_Normal", "in_TexCoord");
	
	printError("display");
	
	glutSwapBuffers();
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA|GLUT_DEPTH|GLUT_DOUBLE);
	glutInitContextVersion(3, 2);
	glutCreateWindow ("Lab 0 - OpenGL 3.2+ Introduction");
	glutDisplayFunc(display); 
	glutRepeatingTimer(20);
	init ();
	glutMainLoop();
	exit(0);
}

