/*Projeto de CG

Gustavo Jorge - 21803634
Luis Gonçalves - 21702482
Tiago Pinto - 21703819*/

#include <iostream>
#include <cmath>
#ifdef __APPLE__
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "getbmp.h"
#include "getbmp.cpp"

#define PI 3.14159265

using namespace std;
static float Xangle = 0.0, Yangle = 0.0, Zangle = 0.0; // Angles to rotate hemisphere.
static double pi = 3.1415;
static float larguraMuro = 40.0;
static float alturaMuro = 300.0;
static float comprimentoOutside = 1200.0;
static float comprimentoInside = 600.0;
static int vista = 2;
static double xCameraAnimation=0.0;
static double yCameraAnimation=-2000;
static double zCameraAnimation=0.0;
static double xBall = 0.0;
static double yBall = yCameraAnimation + 300;
static double zBall = zCameraAnimation;
static bool animacao1 = false;
static bool animacao_camera = false;
static double args[9];
static int animationPeriod = 100;
static unsigned int texture[8]; // Array of texture indices.
//static float spotAngle = 10.0; // Spotlight cone half-angle.


float qaBlack[] = { 0.2, 0.2, 0.2, 1.0 };
float qaWhite[] = { 1.0, 1.0, 1.0, 1.0 };
float matSpec[] = { 1.0, 1.0, 1.0, 1.0 };
float matShine[] = { 50.0 };


void loadExternalTextures()
{
    // Local storage for bmp image data.
    BitMapFile *image[8];
    
    // Load the textures.
    image[0] = getbmp("castle.bmp");
	image[1] = getbmp("wood.bmp");
	image[2] = getbmp("land_dn.bmp");
	image[5] = getbmp("land_ft.bmp");
	image[4] = getbmp("land_bk.bmp");
	image[3] = getbmp("land_rt.bmp");
	image[6] = getbmp("land_lf.bmp");
	image[7] = getbmp("land_up.bmp");
    
    // Ligar a chao.bmp para o texture index[0]
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image[0]->sizeX, image[0]->sizeY, 0, 
	            GL_RGBA, GL_UNSIGNED_BYTE, image[0]->data);
	

	glBindTexture(GL_TEXTURE_2D, texture[1]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image[1]->sizeX, image[1]->sizeY, 0, 
	            GL_RGBA, GL_UNSIGNED_BYTE, image[1]->data);

	glBindTexture(GL_TEXTURE_2D, texture[2]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image[2]->sizeX, image[2]->sizeY, 0, 
	            GL_RGBA, GL_UNSIGNED_BYTE, image[2]->data);


	// Bind sky image to texture index[3]
   glBindTexture(GL_TEXTURE_2D, texture[3]);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image[3]->sizeX, image[3]->sizeY, 0, 
	            GL_RGBA, GL_UNSIGNED_BYTE, image[3]->data);
    
	glBindTexture(GL_TEXTURE_2D, texture[4]);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image[4]->sizeX, image[4]->sizeY, 0, 
	            GL_RGBA, GL_UNSIGNED_BYTE, image[4]->data);


	glBindTexture(GL_TEXTURE_2D, texture[5]);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image[5]->sizeX, image[5]->sizeY, 0, 
	            GL_RGBA, GL_UNSIGNED_BYTE, image[5]->data);

	glBindTexture(GL_TEXTURE_2D, texture[6]);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image[6]->sizeX, image[6]->sizeY, 0, 
	            GL_RGBA, GL_UNSIGNED_BYTE, image[6]->data);


	glBindTexture(GL_TEXTURE_2D, texture[7]);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image[7]->sizeX, image[7]->sizeY, 0, 
	            GL_RGBA, GL_UNSIGNED_BYTE, image[7]->data);

}
//desenhar varios circulos em cima uns dos outros para fazer uma torre (generica no centro)
void drawTower(float altura, double raio) {
	float x = 0.0;
	float y = 0.0;
	float angle = 0.0;
	float angle_stepsize = 0.1;

	glPushMatrix();
	//Tubo
	glBindTexture(GL_TEXTURE_2D, texture[0]); //whiteMarble
	glEnable(GL_LIGHT0);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, qaWhite);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, qaWhite);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, qaBlack);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, matShine);
	glBegin(GL_QUAD_STRIP);
	angle = 0.0;
	while (angle < 2 * PI) {
		x = raio * cos(angle);
		y = raio * sin(angle);
		glNormal3f(x, y, 0.0);
		glTexCoord2f((x * 0.5) + 0.5, 1.0); glVertex3f(x, y, altura);
		glTexCoord2f((x * 0.5) + 0.5, 0.0); glVertex3f(x, y, 0.0);
		angle = angle + angle_stepsize;
	}
	glTexCoord2f(0.0, 1.0); glVertex3f(raio, 0.0, altura);
	glTexCoord2f(0.0, 0.0); glVertex3f(raio, 0.0, 0.0);
	glEnd();

	//Circulo
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, qaWhite);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, qaWhite);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, qaBlack);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, matShine);
	glBegin(GL_POLYGON);
	angle = 0.0;
	while (angle < 2 * PI) {
		x = raio * cos(angle);
		y = raio * sin(angle);
		glNormal3f(0.0, 0.0, 1.0);
		glTexCoord2f((x * 0.5) + 0.5, (y * 0.5) + 0.5); glVertex3f(x, y, altura);
		angle = angle + angle_stepsize;
	}
	glTexCoord2f(1.0, 1.0); glVertex3f(raio, 0.0, altura);
	glEnd();
	glPopMatrix();

	glDisable(GL_LIGHT0);
}
void branco() {
	glColor3f(1.0, 1.0, 1.0);
}
void verde() {
	glColor3f(0.0, 1.0, 0.0);
}
void azul() {
	glColor3f(0.0,0.0,1.0);
}
//desenha um retangulo no centro (vai ser a base do paralelepípedo)
void drawBaseRectangle(float referencialComprimento, float referencialLargura, int idTexture) {
	glBindTexture(GL_TEXTURE_2D, texture[idTexture]);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, qaWhite);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, qaWhite);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, qaBlack);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, matShine);
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 0.0);glVertex3f(-referencialComprimento, -referencialLargura, 0.0);
	glTexCoord2f(1.0, 0.0);glVertex3f(referencialComprimento, -referencialLargura, 0.0);
	glTexCoord2f(1.0, 1.0);glVertex3f(referencialComprimento, referencialLargura, 0.0);
	glTexCoord2f(0.0, 1.0);glVertex3f(-referencialComprimento, referencialLargura, 0.0);
	glEnd();
}
//desenha um retangulo no centro(vai ser os lados do paralelepíped)
void drawLateralsRectangle(float referencialLargura, float referencialAltura, int idTexture) {
	glBindTexture(GL_TEXTURE_2D, texture[idTexture]);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, qaWhite);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, qaWhite);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, qaBlack);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, matShine);
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 0.0);glVertex3f(-referencialAltura, -referencialLargura, 0.0);
	glTexCoord2f(1.0, 0.0);glVertex3f(referencialAltura, -referencialLargura, 0.0);
	glTexCoord2f(1.0, 1.0);glVertex3f(referencialAltura, referencialLargura, 0.0);
	glTexCoord2f(0.0, 1.0);glVertex3f(-referencialAltura, referencialLargura, 0.0);
	glEnd();
}
//desenha um paralelepípedo generico no centro
void drawWall(float largura, float comprimento, float altura,int idTexture) {
	//Comprimento = 600
	//largura = 100
	//altura = 100
	float referencialLargura = largura / 2;
	float referencialComprimento = comprimento / 2;
	float referencialAltura = altura / 2;
	

	glPushMatrix();//retangulo da frente
	glEnable(GL_LIGHT0);
    glRotatef(90.0, 1.0, 0.0, 0.0);
    glTranslatef(0.0, -referencialAltura, 0.0);
    glTranslatef(0.0, 0.0, referencialLargura);
	glNormal3f(0.0,1.0,0.0);
    drawLateralsRectangle(referencialAltura, referencialComprimento,idTexture);
    glPopMatrix();

	glPushMatrix();
	glNormal3f(0.0,0.0,1.0);
	drawBaseRectangle(referencialComprimento, referencialLargura, idTexture);//retangulo da base
	glPopMatrix();
	
    glPushMatrix();//retangulo da direita
    glRotatef(90.0, 0.0, 1.0, 0.0);
    glTranslatef(0.0, 0.0, referencialComprimento);
    glTranslatef(referencialAltura, 0.0, 0.0);
	glNormal3f(-1.0,0.0,0.0);
    drawLateralsRectangle(referencialLargura, referencialAltura,idTexture);
    glPopMatrix();

    glPushMatrix();//retangulo da esquerda
    glRotatef(90.0, 0.0, 1.0, 0.0);
    glTranslatef(0.0, 0.0, -referencialComprimento);
    glTranslatef(referencialAltura, 0.0, 0.0);
	glNormal3f(-1.0,0.0,0.0);
    drawLateralsRectangle(referencialLargura, referencialAltura,idTexture);
    glPopMatrix();

    glPushMatrix();//retangulo de tras
    glRotatef(90.0, 1.0, 0.0, 0.0);
    glTranslatef(0.0, -referencialAltura, 0.0);
    glTranslatef(0.0, 0.0, -referencialLargura);
	glNormal3f(0.0,-1.0,0.0);
    drawLateralsRectangle(referencialAltura, referencialComprimento,idTexture);
    glPopMatrix();
	
    glPushMatrix();//"tampa"
    glTranslatef(0.0, 0.0, -altura);
	glNormal3f(0.0,0.0,-1.0);
    drawBaseRectangle(referencialComprimento, referencialLargura,idTexture);
	glDisable(GL_LIGHT0);
    glPopMatrix();
	
}
//desenha os cubos em cima das torres (dando para as torres grandes e pequenas)
void drawTopOfSquareTowers(float yTower, float xTower, float zTower) {
	branco();
	glPushMatrix();
	glRotatef(90.0,0.0,0.0,1.0);
	glTranslatef(0.0, 0.0, zTower);
	glTranslatef(0.0, 40.0, 0.0);
	glTranslatef(-40.0, 0.0, 0.0);
	glTranslatef(xTower, yTower, 0.0);
	drawWall(20.0, 20.0, 20.0,0);
	glPopMatrix();

	glPushMatrix();
	glRotatef(90.0,0.0,0.0,1.0);
	glTranslatef(0.0, 0.0, zTower);
	glTranslatef(0.0, -40.0, 0.0);
	glTranslatef(-40.0, 0.0, 0.0);
	glTranslatef(xTower, yTower, 0.0);
	drawWall(20.0, 20.0, 20.0,0);
	glPopMatrix();

	glPushMatrix();
	glRotatef(90.0,0.0,0.0,1.0);
	glTranslatef(0.0, 0.0, zTower);
	glTranslatef(0.0, 40.0, 0.0);
	glTranslatef(40.0, 0.0, 0.0);
	glTranslatef(xTower, yTower, 0.0);
	drawWall(20.0, 20.0, 20.0,0);
	glPopMatrix();

	glPushMatrix();
	glRotatef(90.0,0.0,0.0,1.0);
	glTranslatef(0.0, 0.0, zTower);
	glTranslatef(0.0, -40.0, 0.0);
	glTranslatef(40.0, 0.0, 0.0);
	glTranslatef(xTower, yTower, 0.0);
	drawWall(20.0, 20.0, 20.0,0);
	glPopMatrix();	
}
//desenha as torres de fora (com transformações)
void drawTowersOutside() {
	azul();
	//desenha 4 cubos em cima da torre
	drawTopOfSquareTowers(comprimentoOutside/2, comprimentoOutside/2, alturaMuro + larguraMuro/2);//cilindro superior direito
	drawTopOfSquareTowers(comprimentoOutside/2, -comprimentoOutside/2,  alturaMuro + larguraMuro/2);//cilindro inferior direito
	drawTopOfSquareTowers(-comprimentoOutside/2, -comprimentoOutside/2,  alturaMuro + larguraMuro/2);//cilindro inferior esquerdo
	drawTopOfSquareTowers(-comprimentoOutside/2,comprimentoOutside/2, alturaMuro + larguraMuro/2);//cilindro superior esquerdo
	//inferior direita
	glPushMatrix();
	glTranslatef(0.0, 0.0, -alturaMuro);
	glTranslatef(comprimentoOutside/2, 0.0, 0.0);
	glTranslatef(0.0, -comprimentoOutside/2, 0.0);
	drawTower(alturaMuro * 2, 80.0);
	drawTower(alturaMuro * 2, 40.0);
	glPopMatrix();

	//superior direita
	glPushMatrix();
	glTranslatef(0.0, 0.0, -alturaMuro);
	glTranslatef(comprimentoOutside/2, comprimentoOutside/2, 0.0);
	drawTower(alturaMuro*2, 80.0);
	drawTower(alturaMuro*2, 40.0);
	glPopMatrix();

	//superior esquerda
	glPushMatrix();
	glTranslatef(0.0, 0.0, -alturaMuro);
	glTranslatef(-comprimentoOutside/2, comprimentoOutside/2, 0.0);
	drawTower(alturaMuro*2, 80.0);
	drawTower(alturaMuro*2, 40.0);
	glPopMatrix();

	//inferior esquerda
	glPushMatrix();
	glTranslatef(0.0, 0.0, -alturaMuro);
	glTranslatef(-comprimentoOutside/2, -comprimentoOutside/2, 0.0);
	drawTower(alturaMuro*2, 80.0);
	drawTower(alturaMuro*2, 40.0);
	glPopMatrix();
}
//desenha as torres de dentro
void drawTowersInside(float alturaMuralha) {
	azul();

	//desenha 4 cubos em cima da torre
	drawTopOfSquareTowers(comprimentoInside/2, comprimentoInside/2, larguraMuro/2);//cilindro superior direito
	drawTopOfSquareTowers(comprimentoInside/2, -comprimentoInside/2, larguraMuro/2);//cilindro inferior direito
	drawTopOfSquareTowers(-comprimentoInside/2, -comprimentoInside/2, larguraMuro/2);//cilindro inferior esquerdo
	drawTopOfSquareTowers(-comprimentoInside/2,comprimentoInside/2,larguraMuro/2);//cilindro superior esquerdo
	//inferior direita
	glPushMatrix();
	glTranslatef(0.0, 0.0, -alturaMuralha);
	glTranslatef(comprimentoInside/2, -comprimentoInside/2, 0.0);
	drawTower(alturaMuralha, 80.0);
	drawTower(alturaMuralha, 40.0);
	glPopMatrix();

	//inferior esquerda
	glPushMatrix();
	glTranslatef(0.0, 0.0, -alturaMuralha);
	glTranslatef(-comprimentoInside/2, -comprimentoInside/2, 0.0);
	drawTower(alturaMuralha, 80.0);
	drawTower(alturaMuralha, 40.0);
	glPopMatrix();

	//superior direita
	glPushMatrix();
	glTranslatef(0.0, 0.0, -alturaMuralha);
	glTranslatef(comprimentoInside/2, comprimentoInside/2, 0.0);
	drawTower(alturaMuralha, 80.0);
	drawTower(alturaMuralha, 40.0);
	glPopMatrix();

	//superior esquerda
	glPushMatrix();
	glTranslatef(0.0, 0.0, -alturaMuralha);
	glTranslatef(-comprimentoInside/2, comprimentoInside/2, 0.0);
	drawTower(alturaMuralha, 80.0);
	drawTower(alturaMuralha, 40.0);
	glPopMatrix();
}
//desenha a muralha de fora
void drawOutsideWall() {
	branco();

	//colocar os cubos em cima dos muros da muralha
	for(float x = -comprimentoOutside/2; x <= comprimentoOutside/2; x += 100.0) {
		for(float y = -comprimentoOutside/2; y <= comprimentoOutside/2; y+=100.0) {
			if(x == -comprimentoOutside/2 || y == -comprimentoOutside/2 || x == comprimentoOutside/2 ||  y==comprimentoOutside/2 ) {
				glPushMatrix();
				glRotatef(90.0,0.0,0.0,1.0);
				glTranslatef(x, y, larguraMuro);
				drawWall(larguraMuro, larguraMuro, larguraMuro,0);
				glPopMatrix();
			}			
		}		
	}

	glPushMatrix();//muro de baixp
	glTranslatef(0.0, -comprimentoOutside/2, 0.0);
	glRotatef(180.0,0.0,0.0,1.0);
	drawWall(larguraMuro, comprimentoOutside + larguraMuro, alturaMuro,0);
	glPopMatrix();

	glPushMatrix();//muro de cima
	glTranslatef(0.0, comprimentoOutside/2, 0.0);
	drawWall(larguraMuro, comprimentoOutside + larguraMuro, alturaMuro,0);
	glPopMatrix();

	glPushMatrix();//muro do lado esquerdo
	glRotatef(90.0, 0.0, 0.0, 1.0);
	glTranslatef(0.0, comprimentoOutside/2, 0.0);
	drawWall(larguraMuro, comprimentoOutside + larguraMuro, alturaMuro,0);
	glPopMatrix();

	glPushMatrix();//muro do lado direito
	glRotatef(90.0, 0.0, 0.0, 1.0);
	glTranslatef(0.0, -comprimentoOutside/2, 0.0);
	drawWall(larguraMuro, comprimentoOutside + larguraMuro, alturaMuro,0);
	glPopMatrix();

	//e chamada a função que desenha as torres de fora
    drawTowersOutside();
    
}
//desenha a muralha de dentro
void drawInsideWall() {
	branco();
	float ladosQuadradosCentro = 100.0;

	glPushMatrix();//muro de baixp
	glTranslatef(0.0, -comprimentoInside/2, 0.0);
	glRotatef(180.0,0.0,0.0,1.0);
	drawWall(larguraMuro, comprimentoInside + larguraMuro, alturaMuro,0);
	glPopMatrix();

	glPushMatrix();//muro de cima
	glTranslatef(0.0, comprimentoInside/2, 0.0);
	drawWall(40.0, comprimentoInside + larguraMuro, alturaMuro,0);
	glPopMatrix();

	glPushMatrix();//muro do lado esquerdo
	glRotatef(90.0, 0.0, 0.0, 1.0);
	glTranslatef(0.0, comprimentoInside/2, 0.0);
	drawWall(40.0, comprimentoInside + larguraMuro, alturaMuro,0);
	glPopMatrix();

	glPushMatrix();//muro do lado direito
	glRotatef(90.0, 0.0, 0.0, 1.0);
	glTranslatef(0.0, -comprimentoInside/2, 0.0);
	drawWall(40.0, comprimentoInside + larguraMuro, alturaMuro,0);
	glPopMatrix();

	glPushMatrix();//quadrado de cima
	glTranslatef(0.0, comprimentoInside/2, 0.0);
	drawWall(ladosQuadradosCentro, ladosQuadradosCentro, alturaMuro,0);
	glPopMatrix();

	glPushMatrix();//quadrado baix0
	glTranslatef(0.0, -comprimentoInside/2, 0.0);
	drawWall(ladosQuadradosCentro, ladosQuadradosCentro, alturaMuro,0);
	glPopMatrix();

	glPushMatrix();//quadrado direito
	glTranslatef(comprimentoInside/2, 0.0, 0.0);
	drawWall(ladosQuadradosCentro, ladosQuadradosCentro, alturaMuro,0);
	glPopMatrix();

	glPushMatrix();//quadrado esquerdo
	glTranslatef(-comprimentoInside/2, 0.0, 0.0);
	drawWall(ladosQuadradosCentro, ladosQuadradosCentro, alturaMuro,0);
	glPopMatrix();

	drawTopOfSquareTowers(comprimentoInside/2, 0.0, larguraMuro/2);//Top Tower
	drawTopOfSquareTowers(-comprimentoInside/2, 0.0, larguraMuro/2);//Bottom Tower
	drawTopOfSquareTowers(0.0, comprimentoInside/2, larguraMuro/2);//Right Tower
	drawTopOfSquareTowers(0.0, -comprimentoInside/2, larguraMuro/2);//Left Tower	
	
	//e chamada a fucao que desenha as torres de dentro
    drawTowersInside(alturaMuro);
}
void drawBall(double x, double y, double z) {
   glPushMatrix();

   glTranslatef(x, y, 120.0);
   glPushMatrix();
   glutWireSphere(25, 10, 8);
   glPopMatrix();
   glPopMatrix();

   
}
void skyBox() {
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, texture[2]);//chao     
   	glBegin(GL_QUADS);
	   glNormal3f(0.0,-1.0,.0);
      glTexCoord2f(0.0, 0.0); glVertex3f(30000.0, -30000,300.0);
      glTexCoord2f(5.0, 0.0); glVertex3f(-30000.0, -30000.0, 300.0);
      glTexCoord2f(5.0, 5.0); glVertex3f(-30000.0, 30000.0, 300.0);
      glTexCoord2f(0.0, 5.0); glVertex3f(30000.0, 30000.0, 300.0);
   glEnd();
   glPopMatrix();
   
	glPushMatrix();
   glBindTexture(GL_TEXTURE_2D, texture[3]);//parte da frente      
   glBegin(GL_QUADS);
	glNormal3f(0.0,-1.0,0.0);
      glTexCoord2f(0.0, 0.0); glVertex3f(20000.0, 20000.0, 300.0);
      glTexCoord2f(1.0, 0.0); glVertex3f(-20000.0, 20000.0, 300.0);
      glTexCoord2f(1.0, 1.0); glVertex3f(-20000.0, 20000.0, -29000.0);
      glTexCoord2f(0.0, 1.0); glVertex3f(20000.0, 20000.0, -29000.0);
   glEnd();
   glPopMatrix();

glPushMatrix();
   glBindTexture(GL_TEXTURE_2D, texture[4]);//parte da esquerda  
   glBegin(GL_QUADS);
	glNormal3f(-1.0,0.0,0.0);
      glTexCoord2f(0.0, 0.0); glVertex3f(20000.0, -20000.0, 300.0);
      glTexCoord2f(1.0, 0.0); glVertex3f(20000.0, 20000.0, 300.0);
      glTexCoord2f(1.0, 1.0); glVertex3f(20000.0, 20000.0, -29000.0);
      glTexCoord2f(0.0, 1.0); glVertex3f(20000.0, -20000.0, -29000.0);
   glEnd();
   glPopMatrix();

glPushMatrix();
   glBindTexture(GL_TEXTURE_2D, texture[5]);//parte da direita       
   glBegin(GL_QUADS);
		glNormal3f(1.0,0.0,0.0);
      glTexCoord2f(0.0, 0.0); glVertex3f(-20000.0, 20000.0, 300.0);
      glTexCoord2f(1.0, 0.0); glVertex3f(-20000.0, -20000.0, 300.0);
      glTexCoord2f(1.0, 1.0); glVertex3f(-20000.0, -20000.0, -29000.0);
      glTexCoord2f(0.0, 1.0); glVertex3f(-20000.0, 20000.0, -29000.0);
   glEnd();
   glPopMatrix();

glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, texture[6]);//parte de tras    
   glBegin(GL_QUADS);
	glNormal3f(0.0,1.0,0.0);
      glTexCoord2f(0.0, 0.0); glVertex3f(-20000.0, -20000.0, 300.0);
      glTexCoord2f(1.0, 0.0); glVertex3f(20000.0, -20000.0, 300.0);
      glTexCoord2f(1.0, 1.0); glVertex3f(20000.0, -20000.0, -29000.0);
      glTexCoord2f(0.0, 1.0); glVertex3f(-20000.0, -20000.0, -29000.0);
   glEnd();
   glPopMatrix();

	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, texture[7]);//parte de cima       
   	glBegin(GL_QUADS);
	   glNormal3f(0.0,-1.0,.0);
      glTexCoord2f(0.0, 0.0); glVertex3f(30000.0, -30000,-29000.0);
      glTexCoord2f(1.0, 0.0); glVertex3f(-30000.0, -30000.0, -29000.0);
      glTexCoord2f(1.0, 1.0); glVertex3f(-30000.0, 30000.0, -29000.0);
      glTexCoord2f(0.0, 1.0); glVertex3f(30000.0, 30000.0, -29000.0);
   glEnd();
   glPopMatrix();
   
}
// Drawing (display) routine.
// This stays in a loop after calling glutMainLoop()
// PT: Função que faz a renderização para a janela
// Fica em loop após ser chamada a função glutMainLoop()
void drawScene(void)
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	// Clear screen to background color.
    // PT: Limpa a cor de fundo
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
	
	float lightPos[] = { -1500.0, 0.0, -1500.0, 1.0 };

	
	if(animacao1){
		gluLookAt(xBall,yBall,zBall,xBall,20000.0,0.0,0.0,0.0,-1.0);
	
	} else {
		gluLookAt(args[0], args[1], args[2], args[3], args[4], args[5], args[6], args[7], args[8]);
	}
	

	//rotacao de todo o desenho em torno do z
	glRotatef(Zangle, 0.0, 0.0, 1.0);
	//rotacao de todo o desenho em torno do y
   	glRotatef(Yangle, 0.0, 1.0, 0.0);
	   //rotacao de todo o desenho em torno do x
   	glRotatef(Xangle, 1.0, 0.0, 0.0);

	glEnable(GL_LIGHTING);

	glEnable(GL_LIGHT0);
	skyBox();
   
	//e chamada as funções que desenham todo o castelo (rotação para ficar a vista de topo by default)
	glPushMatrix();
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	glRotatef(180.0, 0.0, 1.0, 0.0);
	drawInsideWall();
	drawOutsideWall();
	glPopMatrix();
	glDisable(GL_LIGHT0);
	if(animacao1) {
		drawBall(xBall, yBall + 300, zBall);
	}
	glDisable(GL_LIGHTING);


	glFlush();
    
}

void camera(int id) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	switch(id) {
		case 1:
			//gluLookAt(0.0,-1100,-1.0,0.0,0.0,0.0,0.0,1.0,0.0);
			glOrtho(-800.0, 800.0, -800.0, 800.0, 1.0, 2600.0);
			break;
		case 2:
			//gluLookAt(0.0,0.0,-1000.0,0.0,0.0,0.0,0.0,1.0,0.0);
			gluPerspective(100,1 ,1, 30000.0);
			//gluLookAt(-1100.0,0.0,-100.0,0.0,0.0,0.0,1.0,0.0,0.0);
			break;
		case 3:
			break;
		default:
			gluPerspective(100,1 ,1, 30000.0);
			args[0] = 0.0;
			args[1] = 0.0;
			args[2] = -1200.0;
			args[3] = 0.0;
			args[4] = 0.0;
			args[5] = 0.0;
			args[6] = 0.0;
			args[7] = 1.0;
			args[8] = 0.0;			
			break;

	}
	

	
}
// Initialization routine. Use to initialize code logic, e.g. initializing variables.
// PT: Função para inicializar recursos ou lógica de código adicional.
void setup(void)
{
	glClearColor(0.0, 0.0, 0.0, 1.0);

	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);

	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);

	float lightAmb[] = { 0.0, 0.0, 0.0, 1.0 };
	float lightDiffAndSpec[] = { 1.0, 1.0, 1.0, 1.0 };
	float qaSpecularLight[] = { 1.0, 1.0, 1.0, 1.0 };

	//float lightAmb1[] = { 1.0, 0.0, 0.0, 1.0 };
	//float lightDifAndSpec1[] = { 1.0, 1.0, 1.0, 1.0 };
	float globAmb[] = { 0.4, 0.4, 0.4, 1.0 };

	glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffAndSpec);
	glLightfv(GL_LIGHT0, GL_SPECULAR, qaSpecularLight);

	//glLightfv(GL_LIGHT1, GL_AMBIENT, lightAmb1);
	//glLightfv(GL_LIGHT1, GL_DIFFUSE, lightDifAndSpec1);
	//glLightfv(GL_LIGHT1, GL_SPECULAR, lightDifAndSpec1);

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globAmb);

	glEnable(GL_NORMALIZE);	

	// Flat shading to obtain the checkered pattern of the floor.
	glShadeModel(GL_FLAT);
	
	 // Cull back faces.
   

	camera(0);

	// Create texture index array.
    glGenTextures(8, texture);
    
    // Load external textures.
    loadExternalTextures();
    
    // Turn on OpenGL texturing.
   	glEnable(GL_TEXTURE_2D); 
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

}
// OpenGL window reshape routine.
// PT: Função que lida com o ajuste à janela de Opengl
void resize(int w, int h)
{
	 // Set viewport size to be the entire OpenGL window.
    // PT: define a vista (viewport). Neste caso ocupa a janela toda de opengl em função do tamanho w e h.
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
}
// Keyboard input processing routine.
// PT: função que recebe o input do teclado
void keyInput(unsigned char key, int x, int y)
{
	switch (key)
	{
	// Press escape to exit.
    // PT: escape faz a saída do programa.
	case 27:
		exit(0);
		break;
	case 'x':
         Xangle += 5.0;
		 if (Xangle > 360.0) Xangle -= 360.0;
         glutPostRedisplay();
         break;
	case 'y':
         Yangle += 5.0;
		 if (Yangle > 360.0) Yangle -= 360.0;
         glutPostRedisplay();
         break;
	case 'z':
         Zangle += 5.0;
		 if (Zangle > 360.0) Zangle -= 360.0;
         glutPostRedisplay();
         break;
	
	case 'q':
		animacao1 = false;
		xBall = 0.0;
		yBall = -2000 + 300;
		zBall = 0.0;
		xCameraAnimation=0.0;
		yCameraAnimation=-2000;
		zCameraAnimation=0.0;
		args[0] = 0.0;
		args[1] = -2500.0;
		args[2] = -500.0;
		args[3] = 0.0;
		args[4] = 0.0;
		args[5] = 0.0;
		args[6] = 0.0;
		args[7] = 1.0;
		args[8] = 0.0;
		glutPostRedisplay();
		break;
	case 'w':
		if(animacao1) {
			yBall+= 10.0;
		}
		glutPostRedisplay();
		break;
	case 'a':
		if(animacao1) {
			xBall += 10;
		}
		glutPostRedisplay();
		break;
	case 's':
		if(animacao1) {
			yBall-= 10;
		}
		glutPostRedisplay();
		break;
	case 'd':
		if(animacao1) {
			xBall -= 10;
		}
		glutPostRedisplay();
		break;
	case ' ' :
		if(animacao_camera) {
			animacao_camera = false;
		} else {
			animacao_camera = true;
		}
		break;
	default:
		break;
	}
}
// Callback routine for non-ASCII key entry.
void specialKeyInput(int key, int x, int y)
{
   
}
void top_menu(int id)
{
   if (id==1) exit(0);
}
void perspectiva(int id) {
	camera(2);
   if(id==2) {
		//gluLookAt(0.0,-1100,-1.0,0.0,0.0,0.0,0.0,1.0,0.0);
		args[0] = 0.0;
		args[1] = -1300.0;
		args[2] = 0.0;
		args[3] = 0.0;
		args[4] = 0.0;
		args[5] = 0.0;
		args[6] = 0.0;
		args[7] = 0.0;
		args[8] = -1.0;
   }
   if(id==3) {
      	//gluLookAt(0.0,0.0,-1000.0,0.0,0.0,0.0,0.0,1.0,0.0);
	  	args[0] = 0.0;
		args[1] = 0.0;
		args[2] = -1200.0;
		args[3] = 0.0;
		args[4] = 0.0;
		args[5] = 0.0;
		args[6] = 0.0;
		args[7] = 1.0;
		args[8] = 0.0;
   }
   if(id==4) {
    	//gluLookAt(-1100.0,0.0,-100.0,0.0,0.0,0.0,1.0,0.0,0.0);
		args[0] = 1300.0;
		args[1] = 0.0;
		args[2] = 0.0;
		args[3] = 0.0;
		args[4] = 0.0;
		args[5] = 0.0;
		args[6] = 0.0;
		args[7] = 0.0;
		args[8] = -1.0;
   }
   if(id == 5) {
	   camera(0);
   }
   glutPostRedisplay();
}
void ortogonal(int id) {
	camera(1);
   if(id==2) {
	   args[0] = 0.0;
		args[1] = -1300.0;
		args[2] = 0.0;
		args[3] = 0.0;
		args[4] = 0.0;
		args[5] = 0.0;
		args[6] = 0.0;
		args[7] = 0.0;
		args[8] = -1.0;
   }
   if(id == 3) {
       args[0] = 0.0;
		args[1] = 0.0;
		args[2] = -1200.0;
		args[3] = 0.0;
		args[4] = 0.0;
		args[5] = 0.0;
		args[6] = 0.0;
		args[7] = 1.0;
		args[8] = 0.0;
   }
   if(id == 4) {
      args[0] = -1300.0;
		args[1] = 0.0;
		args[2] = 0.0;
		args[3] = 0.0;
		args[4] = 0.0;
		args[5] = 0.0;
		args[6] = 0.0;
		args[7] = 0.0;
		args[8] = -1.0;
   }

   glutPostRedisplay();
}
void animacoes(int id) {
	if(id == 2) {
		camera(2);
		animacao1 = true;
		cout << "Pressione w se quiser andar para a frente e q para sair da animacao \n";
		glutPostRedisplay();
	}
}
void makeMenu(void) {
    int sub_menu2;
    sub_menu2 = glutCreateMenu(perspectiva);
    glutAddMenuEntry("Frente",2);
    glutAddMenuEntry("Topo",3);
    glutAddMenuEntry("Lateral", 4);
	glutAddMenuEntry("Cima/Frente", 5);

    int sub_menu3;
    sub_menu3 = glutCreateMenu(ortogonal);
    glutAddMenuEntry("Frente",2);
    glutAddMenuEntry("Topo",3);
    glutAddMenuEntry("Lateral", 4);


    int sub_menu;
    sub_menu = glutCreateMenu(top_menu);
    glutAddSubMenu("Perspectiva", sub_menu2);
    glutAddSubMenu("Ortogonal",sub_menu3);

	int sub_menu_animacoes;
	sub_menu_animacoes = glutCreateMenu(animacoes);
	glutAddMenuEntry("ball animation", 2);

    glutCreateMenu(top_menu);
    glutAddSubMenu("Projecao", sub_menu);
	glutAddSubMenu("Animacoes", sub_menu_animacoes);
    glutAddMenuEntry("Quit",1);

    glutAttachMenu(GLUT_RIGHT_BUTTON);

}
void animate(int value)
{
   if (animacao_camera) 
   {
	   if(yCameraAnimation < -1700) {
		   yCameraAnimation += 30;
	   } else if(xCameraAnimation <800 && yCameraAnimation < 0) {
		   xCameraAnimation += 30;
	   } else if(yCameraAnimation < 800 && xCameraAnimation >0) {
		   yCameraAnimation += 30;
	   }else if(xCameraAnimation>-800) {
		   xCameraAnimation-=30;
		}else{
			yCameraAnimation -= 30;
	   }

		args[0] = xCameraAnimation;
		args[1] = yCameraAnimation;
		args[2] = -500;
		args[3] = 0.0;
		args[4] = 0.0;
		args[5] = 0.0;
		args[6] = 0.0;
		args[7] = 0.0;
		args[8] = -1.0;
   }
   glutTimerFunc(animationPeriod, animate, 1);
   glutPostRedisplay();
}
void initGL(int argc, char **argv)
{
	// PT: inicializa a GLUT parte do opengl
	glutInit(&argc, argv);
	// PT: inicializa modos de Opengl. Neste caso usaremos um buffer de desenho e o modo de cores RGB
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	// PT: Tamanho da janela opengl
	glutInitWindowSize(500, 500);
	// PT: Define o ponto inicial onde a janela ser� colocada, partindo do canto superior esquerdo
	glutInitWindowPosition(100, 100);
	// PT: Cria a janela Opengl com o titulo que � passado por argumento
	glutCreateWindow("castle.cpp");

	// PT: fun��o para inicializar alguma l�gica adicional do programa antes de come�ar a renderiza��o. (facultativo)
	setup();
	// PT: Regista a fun��o que far� a renderiza��o e apresenta��o para a janela. Neste caso a fun��o: drawScene
	glutDisplayFunc(drawScene);
	// PT: Regista a fun��o que far� o redimensionamento da janela. Neste caso a fun��o: resize
	glutReshapeFunc(resize);
	// PT: Regista a fun��o que vai receber o input do teclado. Neste caso a fun��o: keyInput
	glutKeyboardFunc(keyInput);
	glutSpecialFunc(specialKeyInput);

	 makeMenu();

	glutTimerFunc(5, animate, 1);

}
int main(int argc, char **argv)
{
	// Init opengl functions and do the initial setup
    // PT: Inicia as funções de opengl e faz um setup inicial
	initGL(argc, argv);

	cout << "Carregue na tecla 'x' para rodar em torno do eixo dos XX' \n";

	cout << "Carregue na tecla 'y' para rodar em torno do eixo dos YY' \n";

	cout << "Carregue na tecla 'Z' para rodar em torno do eixo dos ZZ' \n";

	cout << "Carregue na tecla space para on/off a animação da camera \n";

	// Begin processing. Will call glutDisplayFunc(<function_to_be_called>) everytime
    // a frame has to be rendered: window was moved, minimized/maximized, resized. They are based on changes on the opengl window.
    // We can force it by calling:
    // glutPostRedisplay();
    // PT: Inicia o processo de renderização da janela através da framework do Opengl. Irá chamar a função que é registada através da função glutDisplayFunc(<function_to_be_called>) (ver função initGL) de cada vez que uma frame da janela terá de ser renderizada: quando a janela é movida, minimizada/maximizada, redimensionada. Estas serão baseadas em mudanças na janela Opengl.
    // Podemos forçar a renderização usando a função:
    // glutPostRedisplay();


	glutMainLoop();

	return 0;
}