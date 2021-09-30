// Demo of heavily simplified sprite engine
// by Ingemar Ragnemalm 2009
// used as base for lab 4 in TSBK03.
// OpenGL 3 conversion 2013.

#ifdef __APPLE__
	#include <OpenGL/gl3.h>
	#include "MicroGlut.h"
	// uses framework Cocoa
#else
	#include <GL/gl.h>
	#include "MicroGlut.h"
#endif

#include <stdlib.h>
#include "LoadTGA.h"
#include "SpriteLight.h"
#include "GL_utilities.h"
#include "VectorUtils3.h"

// Lägg till egna globaler här efter behov.
float kMaxDistance = 110.0f;
float kCohesionWeight = 0.0015f;
float kAvoidanceWeight = 0.7f;
float kAlignmentWeight = 0.08f;
float kRandom = 2.0f;
float kfoodWeight = 0.9f;
float kMaxSpeed = 2.0f;

float CalculateDistance(SpritePtr p1, SpritePtr p2) {
    float distance = Norm(VectorSub(p1->position, p2->position));
    return distance;
}

vec3 CalculateAvoidance(vec3 p) {
    // vector in other direction
    vec3 sub = ScalarMult(p, -1);
    vec3 avoidance = SetVector(sub.x, sub.y, 0.0f);
    float distance = Norm(avoidance);
    return ScalarMult(avoidance, (1 - distance/kMaxDistance));
}

void SpriteBehavior() // Din kod!
{
// Lägg till din labbkod här. Det går bra att ändra var som helst i
// koden i övrigt, men mycket kan samlas här. Du kan utgå från den
// globala listroten, gSpriteRoot, för att kontrollera alla sprites
// hastigheter och positioner, eller arbeta från egna globaler.
    SpritePtr p1 = gSpriteRoot;
    SpritePtr p2;
    
    while (p1 != NULL) {
        float count = 0;
        
        // Cohesion
        p1->averagePosition = SetVector(0, 0, 0);
        
        // Separation
        p1->avoidanceVector = SetVector(0, 0, 0);

        // Alignment
        p1->speedDiff = SetVector(0, 0, 0);
        
        p2 = gSpriteRoot;

        while (p2 != NULL) {
            if (p1 != p2 && CalculateDistance(p1, p2) < kMaxDistance) {
                // Alignment
                p1->speedDiff = VectorAdd(p1->speedDiff, VectorSub(p2->speed, p1->speed));
                // Cohesion
                p1->averagePosition = VectorAdd(p1->averagePosition, p2->position);
                // Separation
                p1->avoidanceVector = VectorAdd(p1->avoidanceVector, CalculateAvoidance(VectorSub(p2->position, p1->position)));
                count += 1;
            }
            p2 = p2->next;
        }
        if (count > 0) {
            // Divisions
            p1->speedDiff = ScalarMult(p1->speedDiff, 1.0 / count);
            p1->averagePosition = ScalarMult(p1->averagePosition, 1.0 / count);
            p1->avoidanceVector = ScalarMult(p1->avoidanceVector, 1.0 / count);
        }
        p1 = p1->next;
    }
    
    // Second loop for adding the resulting contributions
    SpritePtr p = gSpriteRoot;
    while (p != NULL) {
        vec3 cohesionAmount = ScalarMult(p->averagePosition, kCohesionWeight);
        vec3 alignmentAmount = ScalarMult(p->speedDiff, kAlignmentWeight);
        vec3 avoidanceAmount = ScalarMult(p->avoidanceVector, kAvoidanceWeight);
        
        p->speed = VectorAdd(p->speed, cohesionAmount);
        p->speed = VectorAdd(p->speed, alignmentAmount);
        p->speed = VectorAdd(p->speed, avoidanceAmount);
//        i->speed = ScalarMult(i->speed, speed_increase/Norm(i->speed)); // Normalize här får de att fastna i kanter
        p->position = VectorAdd(p->position, p->speed);
        p = p->next;
    }
}

// Drawing routine
void Display()
{
	SpritePtr sp;
	
	glClearColor(0, 0, 0.2, 1);
	glClear(GL_COLOR_BUFFER_BIT+GL_DEPTH_BUFFER_BIT);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	DrawBackground();
	
	SpriteBehavior(); // Din kod!
	
// Loop though all sprites. (Several loops in real engine.)
	sp = gSpriteRoot;
	do
	{
		HandleSprite(sp); // Callback in a real engine
		DrawSprite(sp);
		sp = sp->next;
	} while (sp != NULL);
	
	glutSwapBuffers();
}

void Reshape(int h, int v)
{
	glViewport(0, 0, h, v);
	gWidth = h;
	gHeight = v;
}

void Timer(int value)
{
	glutTimerFunc(20, Timer, 0);
	glutPostRedisplay();
}

// Example of user controllable parameter
float someValue = 0.0;

void Key(unsigned char key,
         __attribute__((unused)) int x,
         __attribute__((unused)) int y)
{
  switch (key)
  {
    case '+':
    	someValue += 0.1;
    	printf("someValue = %f\n", someValue);
    	break;
    case '-':
    	someValue -= 0.1;
    	printf("someValue = %f\n", someValue);
    	break;
    case 0x1b:
      exit(0);
  }
}

void Init()
{
	TextureData *sheepFace, *blackFace, *dogFace, *foodFace;
	
	LoadTGATextureSimple("bilder/leaves.tga", &backgroundTexID); // Bakgrund
	
	sheepFace = GetFace("bilder/sheep.tga"); // Ett får
	blackFace = GetFace("bilder/blackie.tga"); // Ett svart får
	dogFace = GetFace("bilder/dog.tga"); // En hund
	foodFace = GetFace("bilder/mat.tga"); // Mat
	
	NewSprite(sheepFace, 100, 200, 1, 1);
	NewSprite(sheepFace, 200, 100, 1.5, -1);
	NewSprite(sheepFace, 250, 200, -1, 1.5);
    NewSprite(dogFace, 200, 250, -1, 1.5);
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(800, 600);
	glutInitContextVersion(3, 2);
	glutCreateWindow("SpriteLight demo / Flocking");
	
	glutDisplayFunc(Display);
	glutTimerFunc(20, Timer, 0); // Should match the screen synch
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Key);
	
	InitSpriteLight();
	Init();
	
	glutMainLoop();
	return 0;
}
