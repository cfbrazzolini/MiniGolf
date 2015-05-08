#include <iostream>

#include "camera.h"


#include "Angel.h"
#include <GL/glew.h> // for OpenGL extensions
#include <GL/glut.h> // for Glut utility kit


#define radToDeg(x) x*180/M_PI  
#define degToRad(x) x*M_PI/180


typedef vec4 point4;
typedef vec4 color4;


mat4 projection, modelview;  // Global Projection Matrices

GLfloat  zoom = 1.0;         // Translation factor
GLfloat  fovy = 60.0;		 // Field-of-view in Y direction angle (in degrees)
GLfloat  aspect = 1.0;       // Viewport aspect ratio
GLfloat  zNear = 0.5, zFar = 1000.0;

Camera camera = Camera::getInstance();

void init_gl()
{
	glEnable(GL_DEPTH_TEST);
}

void init(){

}

void myReshape(int w, int h)
{
	glViewport(0, 0, w, h);
	aspect = GLfloat(w) / h;
}

void display(){
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  /*clear the window */

	projection = Perspective(fovy, aspect, zNear, zFar) /** Translate( 0.0, 0.0, -zoom)*/;

	modelview = LookAt(camera.eye,camera.at, camera.up);


	// swap the buffers
	glutSwapBuffers();
}

void mouse(int btn,int state,int x,int y){
	glutPostRedisplay();
}

void key(unsigned char k,int x,int y){
	switch (k){
		case 27:
			exit(0);
			break;
	}
}

void idle(){

}

void specialFunc(int k, int x, int y){
	switch (k)
	{
	case 27: //Escape key
		exit(0);
		break;
	}
}


int main(int argc,char** argv){

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 800);
	glutCreateWindow("MiniGolf");
	init();
	glutReshapeFunc(myReshape);
	glutDisplayFunc(display);
	glutIdleFunc(idle);       // set in key press
	glutMouseFunc(mouse);
	glutKeyboardFunc(key);
	glutSpecialFunc(specialFunc);
	glutMainLoop();

	return 0;

}