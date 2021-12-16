#include<Windows.h>
#include<GL/glew.h>
#include<GL/freeglut.h>
#include<stdio.h>
#include<string.h>
#include"classDef.h"

extern Player p1;
Building b1(5, 10, 5);

void init(){
	glClearColor(0.0,0.0,0.0,1.0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
}

void idle(){
	//player 自動移動
	p1.Progress();
	printf("pos.z = %f\n",p1.pos[2]);

	//如果遊戲結束，停止移動
	if(p1.status == END){
		p1.playerStop();
		printf("stop\n");
	}
	glutPostRedisplay();
}

void keyboard(unsigned char key,int x,int y){
	if(key==27){
		exit(0);
	}
	if (key == 32) {//space
		//用空白鍵開始遊戲
		p1.status = GAME;
	}
	if (p1.status == GAME) {
		p1.kb(key,x,y);
	}
	
	glutPostRedisplay();
}

void reshape(int w,int h){
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90,(GLfloat)w/(GLfloat)h,1,50);
	glMatrixMode(GL_MODELVIEW);
}

//====================================draw====================================
void drawGround(int w, int h) {
	glPushMatrix();
	{
		glDisable(GL_LIGHTING);
		{
			glColor3ub(80, 127, 80);
			glTranslatef(0, 0, -100);
			glRotatef(90, 1, 0, 0);
			glScalef(w, h, 0);
			glRectf(-1, 1, 1, -1);
		}
		glEnable(GL_LIGHTING);
	}
	glPopMatrix();
}

void drawObstacles() {
	//static method ,don't need instance
	TestObject::drawCube(-2, 1, -5,&p1);
	TestObject::drawCube(3, 1, -10,&p1);
	//TestObject::drawCube(4, 1, -20);
	//TestObject::drawCube(-4, 1, -50);
	//TestObject::drawCube(4, 1, -70);
	//TestObject::drawCube(-2.5, 1, -90);
	//TestObject::drawCube(4, 1, -100);
	//TestObject::drawCube(4, 1, -130);
	//TestObject::drawCube(4, 1, -200);
}

void drawBuildings() {
	b1.setPos(10, 1, -70);
	b1.drawBuilding();
}

void drawPlayer() {
	p1.drawPlayer();
}

void drawProgressBar() {
	ProgressBar::draw(&p1);
}