#include "Rectangle.h"
#include "../visualc15/Al.h"
using namespace ucm;

void Rectangle::draw(){
    glColor3f(r, g, b);
    
    glBegin(GL_POLYGON);
    
    glVertex2f(x, y);
    glVertex2f(x+w, y);
    glVertex2f(x+w, y-h);
    glVertex2f(x, y-h);
    
    glEnd();
}

void Rectangle::fire(){
	missle = true;
	missle1 = true;
	missle2 = true;
}


