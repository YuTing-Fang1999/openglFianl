#pragma once
#include<Windows.h>
#include<GL/glew.h>
#include<GL/freeglut.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#define _USE_MATH_DEFINES

#define PLAYER_RATE 0.5 //���a�C�������ʶZ��
#define FINAL_LEN -50 //���I����

enum Status { START, GAME, DEAD, END };

class Player{
public:
	GLfloat pos[3];	//Position
	Status status = START; //�C���ثe�����A

	Player(){
		memset(this->pos, 0, 3);
	}
	~Player(){}

	//���Y
	void lookAt() {
		gluLookAt(
			pos[0], pos[1] + 5, pos[2] + 5,
			pos[0], pos[1], pos[2] - 17,
			0, 1, 0);
	}

	//�e�Xplayer
	void drawPlayer(){
		glPushMatrix();
		{
			glTranslatef(pos[0], pos[1], pos[2]);
			glScalef(1,2,1);
			glutSolidCube(1);
		}
		glPopMatrix();
	}

	//player��L�\��
	void kb(unsigned char key, int x, int y) {
		if (key == 'w') {
			pos[2] -= PLAYER_RATE;
		}
		else if (key == 's') {
			pos[2] += PLAYER_RATE;
		}
		else if (key == 'a') {
			pos[0] -= PLAYER_RATE;
		}
		else if (key == 'd') {
			pos[0] += PLAYER_RATE;
		}
	}

	//�۰ʫe�i
	void Progress() {
		//pos[2] -= 0.1;
	}

	//����
	void playerStop() {
		this->pos[2] = FINAL_LEN;
	}
};

class ProgressBar {
public:
	static void draw(Player *p) {
		float x = 0, y = 0; //�i�ױ��_�I
		float width = 8, height = 0.2;
		
		//�p�G��F���I
		if (p->pos[2] == FINAL_LEN) p->status = END;
		
		glDisable(GL_LIGHTING);
		{
			glPushMatrix();
			{
				//�ű�
				glTranslatef(p->pos[0]-4, p->pos[1]+7.8, p->pos[2]);
				glColor3f(0, 1, 1);
				glBegin(GL_QUADS);
				glVertex2f(x, y);
				glVertex2f(x + (p->pos[2])/FINAL_LEN * width, y);
				glVertex2f(x + (p->pos[2]) / FINAL_LEN * width, y + height);
				glVertex2f(x, y + height);
				glEnd();

				//�ձ�
				glColor3f(1, 1, 1);
				glBegin(GL_QUADS);
				glVertex2f(x, y);
				glVertex2f(x + width, y);
				glVertex2f(x + width, y + height);
				glVertex2f(x, y + height);
				glEnd();
			}
			glPopMatrix();
			
		}
		glEnable(GL_LIGHTING);

		
	}
};
class Building{
public:
	GLfloat scl[3];
	GLfloat pos[3]={0,0,0};
	GLfloat mat_amb[4]={0.2,0.2,0.2,1};
	GLfloat mat_dif[4]={0.8,0.7,0.7,1};
	GLfloat mat_dif_w[4]={1,1,1,1};
	GLfloat mat_nul[4]={0,0,0,0};

	Building(GLfloat x,GLfloat y,GLfloat z){
		scl[0]=x;scl[1]=y;scl[2]=z;
	}
	~Building(){}

	void setPos(GLfloat x,GLfloat y,GLfloat z){
		pos[0]=x;pos[1]=y;pos[2]=z;
	}

	void drawBuilding(){
		glPushMatrix();
		{
			//glTranslatef(0,0,-70);
			glTranslatef(pos[0],pos[1],pos[2]);
			glScalef(scl[0],scl[1],scl[2]);
			//glMaterialfv(GL_FRONT,GL_AMBIENT,mat_amb);
			
			glutSolidCube(1);
			//glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_dif_w);
		}
		glPopMatrix();
	}
};

class CollisionBall {
public:
	GLfloat myPos[3];

	CollisionBall(GLfloat x, GLfloat y, GLfloat z) {
		myPos[0] = x;
		myPos[1] = y;
		myPos[2] = z;
	}
	~CollisionBall() {}

	GLfloat dist(GLfloat pos[3]) {
		return sqrt(
			pow(pos[0] - myPos[0], 2) +
			pow(pos[1] - myPos[1], 2) +
			pow(pos[2] - myPos[2], 2)
		);
	}
	bool isColision(GLfloat r, GLfloat pos[3]) {
		return dist(pos) < r;
	}
};
class TestObject{
public:
	//draw a test object in scene
	TestObject(){}
	~TestObject(){}

	static void drawCube(GLfloat x,GLfloat y,GLfloat z,Player *p){
		GLfloat mat_dif_yellow[4] = { 0.8,0.7,0,1 };
		GLfloat mat_dif_white[4] = { 1,1,1,1 };
		GLfloat mat_dif_red[4] = { 1,0,0,1 };
		
		CollisionBall clision(x, y, z);
		glPushMatrix();
		{
			glMaterialfv(GL_FRONT,GL_DIFFUSE, mat_dif_yellow);
			if (clision.isColision(1.4, p->pos)) {
				glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_dif_red);
			}
			glTranslatef(x, y, z);
			glutSolidCube(1);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_dif_white);
		}
		glPopMatrix();
	}
};