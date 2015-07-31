#include <iostream>
#include <GL/glut.h>
#include <math.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include "texture.h"
#include "collision.h"
#include "coords.h"
#include "text.h"

using namespace::std;


bool waySee = true, jumpFlag = false;
int jumpCount = 250, coinCount = 0;

void keyboardS (int numKey, int x, int y){
        switch (numKey){
        case GLUT_KEY_UP:{
            if (jumpCount >= 250 && gravitation() == false){
                jumpCount = 0;
            }
            }break;
        case GLUT_KEY_LEFT:{
            if (goLeft >= 50){
                goLeft-=10;
                if (speed >= -300){
                    speed-=2;
                }
            }
                waySee = false;
            }break;
        case GLUT_KEY_RIGHT:{

                if (speed <=300){
                    speed+=2;
                }
                if (goLeft >= 500){
                    mapPush();
                }else{
                    goLeft+=10;
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

    int temp = 0;
    for (int i = 0; i < winWid/64; i++){
        glBindTexture(GL_TEXTURE_2D, mario_floor);
        glBegin(GL_POLYGON);
            glTexCoord2d(0, 0); glVertex2f(temp, -94);
            glTexCoord2d(0, 1); glVertex2f(temp, -30);
            glTexCoord2d(1, 1); glVertex2f(temp + 64, -30);
            glTexCoord2d(1, 0); glVertex2f(temp + 64, -94);
        glEnd ();
        temp += 64;
    }

    for (int i = 0; i < arrPipeASize; i++){
        glBindTexture(GL_TEXTURE_2D, pipeA);
        glBegin (GL_POLYGON);
            glTexCoord2d(0, 0); glVertex2d(arrPipeA[i].getX(), arrPipeA[i].getY());
            glTexCoord2d(0, 1); glVertex2d(arrPipeA[i].getX(), arrPipeA[i].getY() + 64);
            glTexCoord2d(1, 1); glVertex2d(arrPipeA[i].getX() + 64, arrPipeA[i].getY() + 64);
            glTexCoord2d(1, 0); glVertex2d(arrPipeA[i].getX() + 64, arrPipeA[i].getY());
        glEnd ();
    }

    for (int i = 0; i < arrPipeSize; i++){
        glBindTexture(GL_TEXTURE_2D, pipe);
        glBegin (GL_POLYGON);
            glTexCoord2d(0, 0); glVertex2d(arrPipe[i].getX(), arrPipe[i].getY());
            glTexCoord2d(0, 1); glVertex2d(arrPipe[i].getX(), arrPipe[i].getY() + 64);
            glTexCoord2d(1, 1); glVertex2d(arrPipe[i].getX() + 64, arrPipe[i].getY() + 64);
            glTexCoord2d(1, 0); glVertex2d(arrPipe[i].getX() + 64, arrPipe[i].getY());
        glEnd ();
    }

    for (int i = 0;i < arrWoodSize; i++){
        glBindTexture(GL_TEXTURE_2D, wood);
        glBegin (GL_POLYGON);
            glTexCoord2d(0, 0); glVertex2d(arrWood[i].getX(), arrWood[i].getY());
            glTexCoord2d(0, 1); glVertex2d(arrWood[i].getX(), arrWood[i].getY() + 64);
            glTexCoord2d(1, 1); glVertex2d(arrWood[i].getX() + 64, arrWood[i].getY() + 64);
            glTexCoord2d(1, 0); glVertex2d(arrWood[i].getX() + 64, arrWood[i].getY());
        glEnd ();
    }

    for (int i = 0;i < arrWoodCoinSize; i++){//куб
        glBindTexture(GL_TEXTURE_2D, wood);
        glBegin (GL_POLYGON);
            glTexCoord2d(0, 0); glVertex2d(arrWoodCoin[i].getX(), arrWoodCoin[i].getY());
            glTexCoord2d(0, 1); glVertex2d(arrWoodCoin[i].getX(), arrWoodCoin[i].getY() + 64);
            glTexCoord2d(1, 1); glVertex2d(arrWoodCoin[i].getX() + 64, arrWoodCoin[i].getY() + 64);
            glTexCoord2d(1, 0); glVertex2d(arrWoodCoin[i].getX() + 64, arrWoodCoin[i].getY());
        glEnd ();
    }

    for (int i = 0; i < arrWoodCoinSize; i++){//монета к кубу
        if (arrWoodCoin[i].getUsed() == 1){
            if (coinCount >= 0 && coinCount < 30){
                glBindTexture(GL_TEXTURE_2D, coin1);
            }
            if (coinCount >= 30 && coinCount < 34){
                glBindTexture(GL_TEXTURE_2D, coin2);
            }
            if (coinCount >= 34 && coinCount < 37){
                glBindTexture(GL_TEXTURE_2D, coin3);
            }
            if (coinCount >= 37 && coinCount < 50){
                glBindTexture(GL_TEXTURE_2D, coin4);
            }
            glBegin (GL_POLYGON);
                glTexCoord2d(0, 0); glVertex2d(arrWoodCoin[i].getX(), arrWoodCoin[i].getY() + 64);
                glTexCoord2d(0, 1); glVertex2d(arrWoodCoin[i].getX(), arrWoodCoin[i].getY() + 128);
                glTexCoord2d(1, 1); glVertex2d(arrWoodCoin[i].getX() + 64, arrWoodCoin[i].getY() + 128);
                glTexCoord2d(1, 0); glVertex2d(arrWoodCoin[i].getX() + 64, arrWoodCoin[i].getY() + 64);
            glEnd ();
        }
    }

    for (int i = 0;i < arrQuestionCoinSize; i++){//знак вопроса
        glBindTexture(GL_TEXTURE_2D, question);
        glBegin (GL_POLYGON);
            glTexCoord2d(0, 0); glVertex2d(arrQuestionCoin[i].getX(), arrQuestionCoin[i].getY());
            glTexCoord2d(0, 1); glVertex2d(arrQuestionCoin[i].getX(), arrQuestionCoin[i].getY() + 64);
            glTexCoord2d(1, 1); glVertex2d(arrQuestionCoin[i].getX() + 64, arrQuestionCoin[i].getY() + 64);
            glTexCoord2d(1, 0); glVertex2d(arrQuestionCoin[i].getX() + 64, arrQuestionCoin[i].getY());
        glEnd ();
    }

    for (int i = 0; i < arrQuestionCoinSize; i++){//монета к знаку вопроса
        if (arrQuestionCoin[i].getUsed() == 1){
            if (coinCount >= 0 && coinCount < 30){
                glBindTexture(GL_TEXTURE_2D, coin1);
            }
            if (coinCount >= 30 && coinCount < 34){
                glBindTexture(GL_TEXTURE_2D, coin2);
            }
            if (coinCount >= 34 && coinCount < 37){
                glBindTexture(GL_TEXTURE_2D, coin3);
            }
            if (coinCount >= 37 && coinCount < 50){
                glBindTexture(GL_TEXTURE_2D, coin4);
            }
            glBegin (GL_POLYGON);
                glTexCoord2d(0, 0); glVertex2d(arrQuestionCoin[i].getX(), arrQuestionCoin[i].getY() + 64);
                glTexCoord2d(0, 1); glVertex2d(arrQuestionCoin[i].getX(), arrQuestionCoin[i].getY() + 128);
                glTexCoord2d(1, 1); glVertex2d(arrQuestionCoin[i].getX() + 64, arrQuestionCoin[i].getY() + 128);
                glTexCoord2d(1, 0); glVertex2d(arrQuestionCoin[i].getX() + 64, arrQuestionCoin[i].getY() + 64);
            glEnd ();
        }
    }

    for (int i = 0;i < arrMushroomSize; i++){//знак вопроса к грибу
        glBindTexture(GL_TEXTURE_2D, question);
        glBegin (GL_POLYGON);
            glTexCoord2d(0, 0); glVertex2d(arrMushroom[i].getX(), arrMushroom[i].getY());
            glTexCoord2d(0, 1); glVertex2d(arrMushroom[i].getX(), arrMushroom[i].getY() + 64);
            glTexCoord2d(1, 1); glVertex2d(arrMushroom[i].getX() + 64, arrMushroom[i].getY() + 64);
            glTexCoord2d(1, 0); glVertex2d(arrMushroom[i].getX() + 64, arrMushroom[i].getY());
        glEnd ();
    }

    for (int i = 0; i < arrMushroomSize; i++){//гриб
        if (arrMushroom[i].getUsed() == 1){
            glBindTexture(GL_TEXTURE_2D, mushroom);
            glBegin (GL_POLYGON);
                glTexCoord2d(0, 0); glVertex2d(arrMushroom[i].getX(), arrMushroom[i].getY() + 64);
                glTexCoord2d(0, 1); glVertex2d(arrMushroom[i].getX(), arrMushroom[i].getY() + 128);
                glTexCoord2d(1, 1); glVertex2d(arrMushroom[i].getX() + 64, arrMushroom[i].getY() + 128);
                glTexCoord2d(1, 0); glVertex2d(arrMushroom[i].getX() + 64, arrMushroom[i].getY() + 64);
            glEnd ();
        }
    }

    for (int i = 0;i < arrEnemySize; i++){//враги
        if (arrEnemy[i].getUsed() == 0){
            glBindTexture(GL_TEXTURE_2D, mushroom);
            glBegin (GL_POLYGON);
                glTexCoord2d(0, 0); glVertex2d(arrEnemy[i].getX(), arrEnemy[i].getY());
                glTexCoord2d(0, 1); glVertex2d(arrEnemy[i].getX(), arrEnemy[i].getY() + 64);
                glTexCoord2d(1, 1); glVertex2d(arrEnemy[i].getX() + 64, arrEnemy[i].getY() + 64);
                glTexCoord2d(1, 0); glVertex2d(arrEnemy[i].getX() + 64, arrEnemy[i].getY());
            glEnd ();
        }
    }

    for (int i = 0;i < arrBlockSize; i++){//враги
            glBindTexture(GL_TEXTURE_2D, mushroom);
            glBegin (GL_POLYGON);
                glTexCoord2d(0, 0); glVertex2d(arrBlock[i].getX(), arrBlock[i].getY());
                glTexCoord2d(0, 1); glVertex2d(arrBlock[i].getX(), arrBlock[i].getY() + 64);
                glTexCoord2d(1, 1); glVertex2d(arrBlock[i].getX() + 64, arrBlock[i].getY() + 64);
                glTexCoord2d(1, 0); glVertex2d(arrBlock[i].getX() + 64, arrBlock[i].getY());
            glEnd ();
    }

    Textout("HEALTH: ", 50, winHei - 150, 1.0, 1.0, 0.5); //счетчики
    Textout(itoa (healthCount), 150, winHei - 150, 1.0, 1.0, 0.5);
    Textout("COINS: ", winWid - 200, winHei - 150, 1.0, 1.0, 0.5);
    Textout(itoa (coinCounter), winWid - 100, winHei - 150, 1.0, 1.0, 0.5);

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
    if (jumpCount < 250 && jumpCount >= 0){
        goUp += 10;
        jumpCount += 10;
    }
    if (jumpCount >= 250 && gravitation () == true){
        goUp -= 10;
    }
    if (pick () == true){
        jumpCount = 250; // прекращаем прыжок

        //goUp += distancemario2pipe;  //не работает, подпрыгивание прямо под бокс
    }
    takeCoin();
    if (coinCount >= 39){
        coinCount = 0;
    }
    coinCount+=2;
    for (int i = 0; i < arrEnemySize; i++){
        arrEnemy[i].changeWay();
    }
    kill();
    glutTimerFunc(30, Timer, 0);
}

void Intialize (){
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho (0.0, winWid, -100.0, winHei - 100, -5.0, 5.0);
}

int main(int argc, char *argv[]){

    //INITIALIZE
    glutInit (&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize (winWid, winHei);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("Super mario");
    set_coord();

    glutDisplayFunc(Draw);
    //glutKeyboardFunc(keyboard);
    glutSpecialFunc(keyboardS);
    glutTimerFunc(300, Timer, 0);
    Intialize();
    if(LoadTexture((char *)"mario_jump24.bmp", mario_jump) != 1){printf("Не удалось загрузить изображение\n");}
    if(LoadTexture((char *)"floor24.bmp", mario_floor) != 1){printf("Не удалось загрузить изображение\n");}
    if(LoadTexture((char *)"pipe24.bmp", pipe) != 1){printf("Не удалось загрузить изображение\n");}
    if(LoadTexture((char *)"pipeA24.bmp", pipeA) != 1){printf("Не удалось загрузить изображение\n");}
    if(LoadTexture((char *)"woodBox24.bmp", wood) != 1){printf("Не удалось загрузить изображение\n");}
    if(LoadTexture((char *)"coin24_1.bmp", coin1) != 1){printf("Не удалось загрузить изображение\n");}
    if(LoadTexture((char *)"coin24_2.bmp", coin2) != 1){printf("Не удалось загрузить изображение\n");}
    if(LoadTexture((char *)"coin24_3.bmp", coin3) != 1){printf("Не удалось загрузить изображение\n");}
    if(LoadTexture((char *)"coin24_4.bmp", coin4) != 1){printf("Не удалось загрузить изображение\n");}
    if(LoadTexture((char *)"question24.bmp", question) != 1){printf("Не удалось загрузить изображение\n");}
    if(LoadTexture((char *)"mushroom24.bmp", mushroom) != 1){printf("Не удалось загрузить изображение\n");}

    glutMainLoop();
    return 0;
}
