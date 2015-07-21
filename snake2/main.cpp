#include <iostream>
#include <GL/glut.h>
#include <math.h>
//#include <GL/freeglut.h>
#include <GL/glu.h>
#include "texture.h"
using namespace::std;

double winHei = 400.0, winWid = 700.0;
double goLeft = 0, goUp = -0.75;
int speed = 0;
unsigned int textures[1];
bool waySee = true;



void keyboardS (int numKey, int x, int y){
        switch (numKey){
        case GLUT_KEY_UP:{
            if (goUp == -0.75){
                goUp += 0.05;
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
                goUp-=0.75;
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
    glColor4f(1.0, 1.0, 1.0, 1.0);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, mario_jump);
    glPushMatrix();
    glBegin(GL_POLYGON);
        if (waySee == true){
            glTexCoord2d(0, 0);}else{glTexCoord2d(1, 0);} glVertex2f(goLeft - speed + 0.0, 100 * cos(2.5 * goUp) + 0.0);
        if (waySee == true){
            glTexCoord2d(0, 1);}else{glTexCoord2d(1, 1);} glVertex2f(goLeft - speed + 0.0, 100 * cos(2.5 * goUp) + 64.0);
        if (waySee == true){
            glTexCoord2d(1, 1);}else{glTexCoord2d(0, 1);} glVertex2f(goLeft - speed + 64.0, 100 * cos(2.5 * goUp) + 64.0);
        if (waySee == true){
            glTexCoord2d(1, 0);}else{glTexCoord2d(0, 0);} glVertex2f(goLeft - speed + 64.0, 100 * cos(2.5 * goUp) + 0.0);

    glEnd ();
    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_POLYGON);
        glVertex2f(0.0, -30.0); //вот и пошли первые костыли, марио по высоте неправильно расположен
        glVertex2f(winWid, -30.0); //поэтому все обьекты сдвигаются на 30 пикселей ниже горизонта (косинусоида)
        glVertex2f(winWid, -32.0);
        glVertex2f(0.0, -32.0);
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
    if (goUp != -0.75 && goUp != 0){
        goUp += 0.05;
    }
    if (goUp >= 0){
        goUp = -0.75;
    }
    glutTimerFunc(30, Timer, 0);
}

void Intialize (){
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho (0.0, winWid, - winHei/2, winHei/2, -5.0, 5.0);
}

int main(int argc, char *argv[])
{
    //QApplication a(argc, argv);
    //MainWindow w;
    //w.show();
    //cout << "Hello world\n";

    //INITIALIZE
    glutInit (&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize (winWid, winHei);
    glutInitWindowPosition(200, 200);
    glutCreateWindow("Super mario");


    glutDisplayFunc(Draw);
    //glutKeyboardFunc(keyboard);
    glutSpecialFunc(keyboardS);
    glutTimerFunc(300, Timer, 0);
    Intialize();
    if(LoadTexture((char *)"mario_jump.bmp") != 1){printf("Не удалось загрузить изображение\n");}
    glutMainLoop();
    return 0;
}
