// colorwindow.h
// Cem Yuksel

#ifndef _COLORWINDOW_INCLUDED_
#define _COLORWINDOW_INCLUDED_

#include <stdlib.h>
#include <stdio.h>

#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

//int CreateColorWindow ( int parentwindow, int x, int y );
void RGBtoHSV ( float r, float g, float b, float &h, float &s, float &v );
void HSVtoRGB ( float h, float s, float v,  float &r, float &g, float &b );


#endif
