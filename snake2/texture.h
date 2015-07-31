#ifndef TEXTURE_H
#define TEXTURE_H

#endif // TEXTURE_H

#pragma once
#include <iostream>
//#include <GL/freeglut.h>
#include <malloc.h>
#include <GL/glut.h>
using std::cout;

GLuint  mario_jump; // обьявление текстур тутттттттттттт
GLuint mario_floor;
GLuint pipe;
GLuint pipeA;
GLuint wood;
GLuint coin1;
GLuint coin2;
GLuint coin3;
GLuint coin4;
GLuint question;
GLuint mushroom;

struct textura_struct{
int W;
int H;
unsigned char *Image;
}get_textura;

int LoadTexture(char *FileName, GLuint &mar){
  FILE *F;
  /* Открываем файл */
  if ((F = fopen(FileName, "rb")) == NULL)
    return 0;
  //cout << "pointer successfull\n";
  /*Перемещаемся в bmp-файле на нужную позицию, и считываем ширину и длинну */
  fseek(F, 18, SEEK_SET);
  fread(&(get_textura.W), 2, 1, F);
  fseek(F, 2, SEEK_CUR);
  fread(&(get_textura.H), 2, 1, F);

  printf("%d x %d\n", get_textura.W, get_textura.H);

  /* Выделяем память под изображение. Если память не выделилась, закрываем файл и выходим с ошибкой */
  if ((get_textura.Image = (unsigned char *) malloc(sizeof(unsigned char)*3*get_textura.W * get_textura.H)) == NULL)
  {
    fclose(F);
    return 0;
  }
  /* Считываем изображение в память по 3 бита, то бишь RGB для каждого пикселя */
  fseek(F, 30, SEEK_CUR);
  fread(get_textura.Image, 3, get_textura.W * get_textura.H, F);

  glGenTextures(1, &mar);
  glBindTexture(GL_TEXTURE_2D, mar);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  gluBuild2DMipmaps(GL_TEXTURE_2D, 3, get_textura.W, get_textura.H, GL_BGR, GL_UNSIGNED_BYTE, get_textura.Image);
  free(get_textura.Image);
  fclose(F);

  return 1;
}


int LoadTexture4D(char *FileName, GLuint &mar){
  FILE *F;
  /* Открываем файл */
  if ((F = fopen(FileName, "rb")) == NULL)
    return 0;
  //cout << "pointer successfull\n";
  /*Перемещаемся в bmp-файле на нужную позицию, и считываем ширину и длинну */
  fseek(F, 18, SEEK_SET);
  fread(&(get_textura.W), 2, 1, F);
  fseek(F, 2, SEEK_CUR);
  fread(&(get_textura.H), 2, 1, F);

  printf("%d x %d\n", get_textura.W, get_textura.H);

  /* Выделяем память под изображение. Если память не выделилась, закрываем файл и выходим с ошибкой */
  if ((get_textura.Image = (unsigned char *) malloc(sizeof(unsigned char)*3*get_textura.W * get_textura.H)) == NULL)
  {
    fclose(F);
    return 0;
  }
  /* Считываем изображение в память по 3 бита, то бишь RGB для каждого пикселя */
  fseek(F, 30, SEEK_CUR);
  fread(get_textura.Image, 3, get_textura.W * get_textura.H, F);

  glGenTextures(1, &mar);
  glBindTexture(GL_TEXTURE_2D, mar);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  gluBuild2DMipmaps(GL_TEXTURE_2D, 4, get_textura.W, get_textura.H, GL_RGBA, GL_UNSIGNED_BYTE, get_textura.Image);
  free(get_textura.Image);
  fclose(F);

  return 1;
}
