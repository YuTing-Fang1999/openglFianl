#include<Windows.h>
#include<GL/glew.h>
#include<GL/freeglut.h>
#include<stdio.h>
#include<string.h>
#include<math.h>
#define _USE_MATH_DEFINES

#include"basicFunc.h"
#include"classDef.h"

extern Player p1=Player();

//�C���}�l�e��
void drawStart() {
	//�i�H��K�ĭq�~�檺�e���A�ϥΪť���i�}�l�C��
	drawPlayer();
}

//�C���B��e��
void drawGame() {
	
	//�a�O(�e,��)
	drawGround(6, 600);

	//�ؿv
	drawBuildings();

	//��ê��
	drawObstacles();

	//player
	drawPlayer();

	//�W�誺�i�ױ�
	drawProgressBar();
}

//�C�������e��
void drawEnd() {
	//�i�H��K�Ħ���~�檺�e��
	drawProgressBar();
}

void display(){
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	
	p1.lookAt();
	//====================================

	switch (p1.status)
	{
	case START:
		drawStart();
		break;

	case GAME:
		drawGame();
		break;

	case END:
		drawEnd();
		break;

	default:
		break;
	}
	
	//====================================

	glutSwapBuffers();
}

int main(int argc,char **argv){
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH |GLUT_MULTISAMPLE);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(700,700);
	glutCreateWindow("TITLE");

	init();

	GLenum err = glewInit();
	if( err != GLEW_OK){
		printf("GLEW_ERROR\n");
	}

	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutReshapeFunc(reshape);
	glutIdleFunc(idle);
	glutMainLoop();
	return 0;
}
