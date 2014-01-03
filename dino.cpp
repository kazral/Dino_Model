/**
* CMPS 160L (Fall 2011)
* Lab 2: Animated Animal
*
* Method to draw hemisphere taken from Sumanta Guha, at:
* http://www.ecse.rpi.edu/~wrf/wiki/ComputerGraphicsFall2011/guha/ExperimenterSource/Chapter3/Hemisphere/hemisphere.cpp
*/

#include <stdlib.h>
#include <GL/glut.h>
#include <cmath>
#include "dino.h"
#include "dinoutil.h"

#define PI 3.14159265

static float R = 1.8; // Radius of hemisphere.
static int p = 15; // Number of longitudinal slices.
static int q = 15; // Number of latitudinal slices.
static float Xangle = 0.0, Yangle = 0.0, Zangle = 0.0;

// Global variables
float angle = 0;
float neck_angle = 0;
float arms_angle = 0;
float hands_angle = 0;
float legs_angle = 0;
float feet_angle = 0;
bool is_spinning = false;
bool neck_spinning = false;
bool arms_spinning = false;
bool hands_spinning = false;
bool legs_spinning = false;
bool feet_spinning = false;

// Do spin
void spin() {
	if (is_spinning) {
		is_spinning = false;
		angle = 0.0;
	} else {
		is_spinning = true;
	}
}

void spin_neck() {
	if (neck_spinning) {
		neck_spinning = false;
		neck_angle = 0.0;
	} else {
		neck_spinning = true;
	}
}

void spin_arms() {
	if (arms_spinning) {
		arms_spinning = false;
		arms_angle = 0.0;
	} else {
		arms_spinning = true;
	}
}

void spin_hands() {
	if (hands_spinning) {
		hands_spinning = false;
		hands_angle = 0.0;
	} else {
		hands_spinning = true;
	}
}

void spin_legs() {
	if (legs_spinning) {
		legs_spinning = false;
		legs_angle = 0.0;
	} else {
		legs_spinning = true;
	}
}

void spin_feet() {
	if (feet_spinning) {
		feet_spinning = false;
		feet_angle = 0.0;
	} else {
		is_spinning = true;
	}
}



void cb_display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	camera();

	// Rotate along y-axis
	if (is_spinning) {
		glRotatef(angle, 0, 1, 0);
		angle++;
	}

	if (neck_spinning) {
		neck_angle++;
	}

	if (arms_spinning) {
		arms_angle++;
	}

	if (hands_spinning) {
		hands_angle++;
	}

	if (feet_spinning) {
		feet_angle++;
	}

	if (legs_spinning) {
		legs_angle++;
	}

	draw_axis(4.0);

	glPushMatrix();
	glTranslatef(0, -2, 0);
	draw_dino();
	glPopMatrix();

	glFlush();
	glutSwapBuffers(); // for smoother animation
}

void cb_idle() {
	glutPostRedisplay();
}

void cb_keyboard(unsigned char key, int x, int y) {
	// Add controls to animation, joint movement control, etc.
	// Some camera functions are provided for model viewing convinience.
	switch(key) {
		case '1':
			set_cam(DEFAULT);
			break;
		case '2':
			set_cam(FRONT);
			break;
		case '3':
			set_cam(SIDE);
			break;
		case '4':
			set_cam(TOP);
			break;
		case '5':
			set_cam(ANGLE);
			break;
		case 's':
			spin();
			break;
		case 'n':
			spin_neck();
			break;
		case 'f':
			spin_feet();
			break;
		case 'l':
			spin_legs();
			break;
		case 'a':
			spin_arms();
			break;
		case 'h':
			spin_hands();
			break;
		case 'q':
			exit(0);
			break;
	}
}

void cb_reshape(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-1.0, 1.0, -1.0, 1.0, 1.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
}



void draw_dino() {
	// top level function for drawing the entire dino
	glNormal3f(0, 0, 1);
	draw_body();

	// the two arms
	glPushMatrix();
	glTranslatef(-.8, .5, -1.2);
	glRotatef(arms_angle, 0, 0, 1);
	draw_arm();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-.8, .5, 1.2);
	glRotatef(arms_angle, 0, 0, 1);
	draw_arm();
	glPopMatrix();
	
	// the tail
	glPushMatrix();
	glRotatef(-15, 0, 0, 1);
	glTranslatef(1, 0, 0);
	glRotatef(90, 0, 1, 0);
	glScalef(1.5, 1.25, 1);
	draw_tail();
	glPopMatrix();

	// the neck and head
	glPushMatrix();
	glRotatef(neck_angle, 0, 1, 0);
	draw_neck();
	glPopMatrix();
}

void draw_body() {
	// draws the core body of the dino
	glColor3f(0, .75, .25);
	glutSolidSphere(1.5, 50, 50);

	// draw the legs
	glPushMatrix();
	glScalef(.6, .8, .6);
	glTranslatef(0, -.5, 2.5);
	glRotatef(legs_angle, 0, 0, 1);
	draw_leg();
	glPopMatrix();

	glPushMatrix();
	glScalef(.6, .8, .6);
	glTranslatef(0, -.5, -2.5);
	glRotatef(legs_angle, 0, 0, 1);
	draw_leg();
	glPopMatrix();
}

void draw_leg() {
	glColor3f(0, .55, .25);
	glutSolidSphere(1, 50, 50);

	glPushMatrix();
	glScalef(1.3, .1, 1);
	glTranslatef(-.55, -8, 0);
	draw_foot();
	glPopMatrix();
}

void draw_foot() {
	glColor3f(0, 1, .05);
	glutSolidSphere(1, 25, 25);
}

void draw_arm() {
	glColor3f(0, .5, .1);
	glScalef(.5, 1.25, 1);
	glutSolidCube(.5);

	// draw the forearm
	glPushMatrix();
	glTranslatef(-.55, -.25, 0);
	glRotatef(hands_angle, 0, 1, 0);
	draw_forearm();
	glPopMatrix();
}

void draw_forearm() {
	glColor3f(0, .5, .1);
	glScalef(3.25, .4, 1);
	glutSolidCube(.5);
}

void draw_tail() {
	glColor3f(0, .55, .05);

	glutSolidCone(.5, 2, 25, 25);
}

void draw_neck() {
	glColor3f(0, .75, .25);
	glPushMatrix();
	glTranslatef(-.1, 1.25, 0);
	glScalef(1.3, 2, 1.2);
	glutSolidCube(1);
	glPopMatrix();

	// draw the head
	glPushMatrix();
	glTranslatef(-1.16, 2, 0);
	glScalef(1, 1.15, 1);
	draw_head();
	glPopMatrix();
}

void draw_head() {
	int i, j;
   
    glColor3f(0, .75, .25);

    // Array of latitudinal triangle strips, each parallel to the equator, stacked one
    // above the other from the equator to the north pole.



    for(j = 0; j < q; j++)
    {
       // One latitudinal triangle strip.
       glBegin(GL_TRIANGLE_STRIP);
          for(i = 0; i <= p; i++)
	 	 {
             glVertex3f( R * cos( (float)(j+1)/q * PI/2.0 ) * cos( 2.0 * (float)i/p * PI ),
                         R * sin( (float)(j+1)/q * PI/2.0 ),
		 			    R * cos( (float)(j+1)/q * PI/2.0 ) * sin( 2.0 * (float)i/p * PI ) );
             glVertex3f( R * cos( (float)j/q * PI/2.0 ) * cos( 2.0 * (float)i/p * PI ),
                         R * sin( (float)j/q * PI/2.0 ),
			 		    R * cos( (float)j/q * PI/2.0 ) * sin( 2.0 * (float)i/p * PI ) );
		  }
		  glEnd();
	}
	
	// draw the eyes
	glPushMatrix();
	glScalef(.65, 1, .55);
	glTranslatef(-2.699, .5, -1);
	draw_eye(true);
	glPopMatrix();

	glPushMatrix();
	glScalef(.65, 1, .55);
	glTranslatef(-2.699, .5, 1);
	draw_eye(false);
	glPopMatrix();

	// draw the teeth
	glPushMatrix();
	glScalef(1, 1.3, 1);
	glTranslatef(-.25, 0, -1.3);
	glRotatef(90, 1, 0, 0);
	draw_tooth();
	glPopMatrix();

	glPushMatrix();
	glScalef(1, 1.3, 1);
	glTranslatef(-.25, 0, 1.3);
	glRotatef(90, 1, 0, 0);
	draw_tooth();
	glPopMatrix();
}

void draw_tooth() {
	glColor3f(1, 1, 1);
	glutSolidCone(.25, .25, 20, 20);
}

void draw_eye(bool left) {
	glColor3f(1, 1, 1);
	glBegin(GL_POLYGON);
		glVertex3f(0.05, 0, -.7);
		glVertex3f(0, -.3 ,-.5);
		glVertex3f(0, -.4, 0);
		glVertex3f(0, -.3, .5);
		glVertex3f(0.05, 0, .7);
		glVertex3f(0.25, .3, .5);
		glVertex3f(0.25, .4, 0);
		glVertex3f(0.25, .3, -.5);
	glEnd();

	// draw pupils
	glPushMatrix();
	glScalef(1, 1.5, 1.5);
	if (left) {
		glTranslatef(0, 0, -.1);
	}
	else {
		glTranslatef(0, 0, .1);
	}
	draw_pupil();
	glPopMatrix();
}

void draw_pupil() {
	glColor3f(0, 0, 0);
	glBegin(GL_POLYGON);
		glVertex3f(0.1, .1, -.1);
		glVertex3f(0, -.1, -.1);
		glVertex3f(0, -.1, .1);
		glVertex3f(0.1, .1, .1);
	glEnd();
}
		

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Lab 2: Robotic Animals");
	glEnable(GL_DEPTH_TEST);

	glutDisplayFunc(cb_display);
	glutReshapeFunc(cb_reshape);
	glutIdleFunc(cb_idle);
	glutKeyboardFunc(cb_keyboard);
	glClearColor(0,0,0,0); // set background to black

	glutMainLoop();

	return 0;
}