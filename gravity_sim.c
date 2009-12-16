#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <GL/glu.h>
#include <math.h>
#include <time.h>

#define WWIDTH 500
#define WHEIGHT 500
#define MAX_BODIES 50
#define G 6.67428e-11
#define MIN_MASS 2.23e11
#define MAX_MASS 2.23e12
#define MIN_R 2
#define MAX_R 10
#define DT 0.5

typedef struct {
	float mass;
	float xpos;
	float ypos;
	float vx;
	float vy;
	float radius;
	float color_r;
	float color_g;
	float color_b;
} Body;

void add_body(int x, int y);
float ranf(float low, float high);

int num_bodies;
Body bodies[MAX_BODIES];

void draw_ball(int i) {
	glPushMatrix();
		glTranslatef(bodies[i].xpos,bodies[i].ypos,0);
		glColor3f(bodies[i].color_r, bodies[i].color_g, bodies[i].color_b);
		glBegin(GL_QUADS);
			glVertex2d(-bodies[i].radius,bodies[i].radius);
			glVertex2d(bodies[i].radius,bodies[i].radius);
			glVertex2d(bodies[i].radius,-bodies[i].radius);
			glVertex2d(-bodies[i].radius,-bodies[i].radius);
		glEnd();
	glPopMatrix();
}

void draw_state(void) {
	glClear(GL_COLOR_BUFFER_BIT);
    //glLoadIdentity();  
    //gluLookAt (0.0, 0.0, 50.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	//sample drawing
	//glBegin(GL_TRIANGLES);						// Drawing Using Triangles
	//	glVertex3f( 0.0f, 1.0f, 0.0f);				// Top
	//	glVertex3f(-1.0f,-1.0f, 0.0f);				// Bottom Left
	//	glVertex3f( 1.0f,-1.0f, 0.0f);				// Bottom Right
	//glEnd();
	
	int i;
	for(i = 0; i < num_bodies; i++) {
		draw_ball(i);
	}
	
	glutSwapBuffers();
}

void get_vel_acc(int node, int dir, float pos0, float vel0, float *vel, float *acc) {
	float sumfy = 0;
	
	int i;
	float dist, temp, f, fx, fy;
	for(i=0;i<num_bodies;i++) {
		if( i != node ) {
			//if(!dir) dist = bodies[i].xpos - bodies[node].xpos;
			//else dist = bodies[i].ypos - bodies[node].ypos;
			
			dist = sqrt((bodies[i].ypos - bodies[node].ypos) * (bodies[i].ypos - bodies[node].ypos) +
								(bodies[i].xpos - bodies[node].xpos)*(bodies[i].xpos - bodies[node].xpos));
			f = G * bodies[i].mass * bodies[node].mass * (1/(dist * dist));
			fx = (bodies[i].xpos - bodies[node].xpos) * f / sqrt((bodies[i].xpos - bodies[node].xpos)*(bodies[i].xpos - bodies[node].xpos) +
																																		(bodies[i].ypos - bodies[node].ypos)*(bodies[i].ypos - bodies[node].ypos));
			fy = (bodies[i].ypos - bodies[node].ypos) * f / sqrt((bodies[i].xpos - bodies[node].xpos)*(bodies[i].xpos - bodies[node].xpos) +
																																		(bodies[i].ypos - bodies[node].ypos)*(bodies[i].ypos - bodies[node].ypos));																										
			
			if(!dir) sumfy += fx;
			else sumfy += fy;
		}
	}
	
	*vel = vel0;
	*acc = sumfy / bodies[node].mass;
}

void sim_step(void) {
	int i;
	
	float v1x[num_bodies],v2x[num_bodies],v1y[num_bodies],v2y[num_bodies];
	float a1x[num_bodies],a2x[num_bodies],a1y[num_bodies],a2y[num_bodies];
	
	for(i=0; i < num_bodies; i++) {
		//x direction
		get_vel_acc (i, 0, bodies[i].xpos, bodies[i].vx, &v1x[i], &a1x[i]);
		// y direction
		get_vel_acc (i, 1, bodies[i].ypos, bodies[i].vy, &v1y[i], &a1y[i]);
	}
	for(i=0; i < num_bodies; i++) {
		//x direction
		get_vel_acc (i, 0, bodies[i].xpos + (DT * v1x[i]), bodies[i].vx + (DT * a1x[i]), &v2x[i], &a2x[i]);
		// y direction
		get_vel_acc (i, 0, bodies[i].ypos + (DT * v1y[i]), bodies[i].vy + (DT * a1y[i]), &v2y[i], &a2y[i]);
	}
	for(i=0; i < num_bodies; i++) {
		//printf("applying %f and %f as accels\n",a1x[i],a2x[i]);
		bodies[i].vx = bodies[i].vx + ( DT * ((a1x[i] + a2x[i]) / 2));
		bodies[i].vy = bodies[i].vy + ( DT * ((a1y[i] + a2y[i]) / 2));
		
		//printf("using vel %f,%f\n",v1x[i],v2x[i]);
		bodies[i].xpos = bodies[i].xpos + ( DT * ((v1x[i] + v2x[i]) / 2));
		bodies[i].ypos = bodies[i].ypos + ( DT * ((v1y[i] + v2y[i]) / 2));
	}
	
	glutPostRedisplay();
}

void special_press(int key, int x, int y) {
	printf("special key %d pressed\n",key);
}

void key_press(unsigned char key, int x, int y) {
	if (key == 27) 
		exit(0);
	else if (key == 'c') {
		printf("Count: %d\n",num_bodies);
	} else if (key == 'p') {
		int i;
		for(i=0; i < num_bodies; i++) {
			printf("(%f,%f) ",bodies[i].xpos,bodies[i].ypos);
		}
		putchar('\n');
	}
}

void mouse_click(int button, int state, int x, int y) {
	if(state == GLUT_UP) {
		add_body(x,WHEIGHT - y);
	}
}

void add_body(int x, int y) {
	if(num_bodies == MAX_BODIES) {
		printf("max number of bodies reached!\n");
	}
	else {
		bodies[num_bodies].mass = ranf(MIN_MASS,MAX_MASS);
		bodies[num_bodies].radius = ranf(MIN_R,MAX_R);
		bodies[num_bodies].color_r = ranf(0,1);
		bodies[num_bodies].color_g = ranf(0,1);
		bodies[num_bodies].color_b = ranf(0,1);
		bodies[num_bodies].xpos = x;
		bodies[num_bodies].ypos = y;
		bodies[num_bodies].vx = 0;
		bodies[num_bodies].vy = 0;
		num_bodies++;
	}
}

float ranf(float low, float high) {
	float temp = (rand() / ((float)RAND_MAX + 1.0)) * (high - low) + low;
	return temp;
}

int main(int argc, char **argv)
{
	srand(time(NULL));

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(WWIDTH,WHEIGHT);
	
	glutCreateWindow("Gravity Simulation");
	
	gluOrtho2D(0,WWIDTH,0,WHEIGHT);
	glutSpecialFunc(special_press);
	glutKeyboardFunc(key_press);
	glutIdleFunc(sim_step);
	//glutReshapeFunc(change_size);
	glutMouseFunc(mouse_click);
	glutDisplayFunc(draw_state);

	glutMainLoop();
	return (0);
}
