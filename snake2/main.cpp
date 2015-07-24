#include <iostream>
#include <GL/glut.h>
#include <math.h>
#include <GL/glu.h>
#include "texture.h"
#include "collision.h"
#include "coords.h"
using namespace::std;


bool waySee = true, jumpFlag = false;
int jumpCount = 100;

void keyboardS (int numKey, int x, int y){
        switch (numKey){
        case GLUT_KEY_UP:{
            if (jumpCount >= 100){
                jumpCount = 0;
            }
            }break;
        case GLUT_KEY_LEFT:{
                goLeft-=13;
                if (speed >= -300){
                    speed-=13;
                }
                waySee = false;
            }break;
        case GLUT_KEY_DOWN:{
                goUp -=50;
            }break;
        case GLUT_KEY_RIGHT:{
                goLeft+=13;
                if (speed <=300){
                    speed+=13;
                }
                waySee = true;
            }break;
        }
    }

void Draw (){
    glClear(GL_COLOR_BUFFER_BIT);
    glColor4f(1.0, 1.0, 1.0, 0.5);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, mario_jump);
    glPushMatrix();
    glBegin(GL_POLYGON);

    if (mario2pipeLeft() == true){
        goLeft-=distancemario2pipe;
    }
    if (mario2pipeRight() == true){
        goLeft+=distancemario2pipe;
    }

        if (waySee == true){
            glTexCoord2d(0, 0);}else{glTexCoord2d(1, 0);} glVertex2f(goLeft - speed + 0.0,goUp + 0.0);
        if (waySee == true){
            glTexCoord2d(0, 1);}else{glTexCoord2d(1, 1);} glVertex2f(goLeft - speed + 0.0,goUp + 64.0);
        if (waySee == true){
            glTexCoord2d(1, 1);}else{glTexCoord2d(0, 1);} glVertex2f(goLeft - speed + 64.0,goUp + 64.0);
        if (waySee == true){
            glTexCoord2d(1, 0);}else{glTexCoord2d(0, 0);} glVertex2f(goLeft - speed + 64.0,goUp + 0.0);
    glEnd ();

    glBindTexture(GL_TEXTURE_2D, mario_floor);
    int temp = 0;
    for (int i = 0; i < winWid/64; i++){
        glBegin(GL_POLYGON);
            glTexCoord2d(0, 0); glVertex2f(temp, -94);
            glTexCoord2d(0, 1); glVertex2f(temp, -30);
            glTexCoord2d(1, 1); glVertex2f(temp + 64, -30);
            glTexCoord2d(1, 0); glVertex2f(temp + 64, -94);
        glEnd ();
        temp += 64;
    }

    glBindTexture(GL_TEXTURE_2D, pipe);
    glBegin (GL_POLYGON);
    glTexCoord2d(0, 0); glVertex2d(arrPipe[0].getX(), arrPipe[0].getY());
        glTexCoord2d(0, 1); glVertex2d(arrPipe[0].getX(), arrPipe[0].getY() + 64);
        glTexCoord2d(1, 1); glVertex2d(arrPipe[0].getX() + 64, arrPipe[0].getY() + 64);
        glTexCoord2d(1, 0); glVertex2d(arrPipe[0].getX() + 64, arrPipe[0].getY());
    glEnd ();

    glBindTexture(GL_TEXTURE_2D, wood);

    glBegin (GL_POLYGON);
        glTexCoord2d(0, 0); glVertex2d(arrWood[0].getX(), arrWood[0].getY());
        glTexCoord2d(0, 1); glVertex2d(arrWood[0].getX(), arrWood[0].getY() + 64);
        glTexCoord2d(1, 1); glVertex2d(arrWood[0].getX() + 64, arrWood[0].getY() + 64);
        glTexCoord2d(1, 0); glVertex2d(arrWood[0].getX() + 64, arrWood[0].getY());
    glEnd ();

    glPopMatrix();
    glutSwapBuffers();//конец кадра и выброс в буфер
}

void Timer (int){
    Draw ();
    if (speed > 0){
        speed/=1.1;
    }
    if (speed < 0){
        speed/=1.1;
    }
    if (jumpCount < 100 && jumpCount >= 0){
        goUp += 5;
        jumpCount += 5;
    }
    if (jumpCount >= 100 && gravitation () == true){
        goUp -= 5;
    }
    glutTimerFunc(30, Timer, 0);
}

void Intialize (){
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho (0.0, winWid, - winHei/2, winHei/2, -5.0, 5.0);
}

int main(int argc, char *argv[]){

    //INITIALIZE
    glutInit (&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize (winWid, winHei);
    glutInitWindowPosition(200, 200);
    glutCreateWindow("Super mario");
    set_coord();


    glutDisplayFunc(Draw);
    //glutKeyboardFunc(keyboard);
    glutSpecialFunc(keyboardS);
    glutTimerFunc(300, Timer, 0);
    Intialize();
    if(LoadTexture((char *)"mario_jump.bmp", mario_jump) != 1){printf("Не удалось загрузить изображение\n");}
    if(LoadTexture4D((char *)"floor.bmp", mario_floor) != 1){printf("Не удалось загрузить изображение\n");}
    if(LoadTexture4D((char *)"pipe.bmp", pipe) != 1){printf("Не удалось загрузить изображение\n");}
    if(LoadTexture4D((char *)"woodBox.bmp", wood) != 1){printf("Не удалось загрузить изображение\n");}
    glutMainLoop();
    return 0;
}
