#include <stdlib.h>
#include <time.h>

#include "glut.h"

#include "SIM_pub.h"
#include "UI_drawing_glut_pub.h"
#include "UI_handlers_pub.h"

#define WWIDTH 500
#define WHEIGHT 500

int main(int argc, char **argv)
{
	srand(time(NULL));

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(WWIDTH,WHEIGHT);
	
	glutCreateWindow("Gravity Simulation");
	
	gluOrtho2D(0,WWIDTH,0,WHEIGHT);
	glutSpecialFunc(UI_handler_special_press);
	glutKeyboardFunc(UI_handler_key_press);
	glutIdleFunc(SIM_step);
	//glutReshapeFunc(change_size);
	glutMouseFunc(UI_handler_mouse_click);
	glutDisplayFunc(UI_drawing_glut_draw);

	glutMainLoop();
	return (0);
}
