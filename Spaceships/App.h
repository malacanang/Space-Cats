#ifndef App_hpp
#define App_hpp

#include "GlutApp.h"
#include "Rectangle.h"
#include "Circle.h"
#include "Triangle.h"
#include <deque>
#include "GlutApp.h"
#include "RgbImage.h"
#include "TexRect.hpp"
#include "../visualc15/Enemies.h"
#include "../visualc15/Al.h"
#include <vector>
#include <fstream>
#include <iostream>
#include <string>

class App: public GlutApp {
    // Maintain app state here
    
	ucm::Rectangle* r;
   
    bool right;
    bool move;
	bool left;
	bool up;
	bool down;

    float theta;
    float inc;

	//missle colors
	float r1;
	float r2;
	float r3;
    
    float missleX;
    float missleY;
	float missleX1;
	float missleY1;
	float missleX2;
	float missleY2;
	float enemyY, enemyZ, enemyA, enemyB, secretE;

    bool shot;
    
    int counter;
    
    bool gameover;
    bool loop;
    
public:

	//GLuint loadTexture(const char* filename);
	//the background texture
	GLuint wall;
	TexRect* background;
	//main character texture
	Al* mainc = new Al(0.0, - 0.7, 0.1, 0.1);
	int mode; 
	float mx, my;
	int score;
	int var;
	int highscore;
	char strscore[10];
    // Constructor, to initialize state
    App(const char* label, int x, int y, int w, int h);
    
    // These are the events we want to handle
    void draw();
    void keyPress(unsigned char key);
	
    void idle();
	void print(float x, float y, float z, char *string);
	GLuint loadTexture(const char *filename);
	void mouseDown(float x, float y);
	void getScores();
	void saveScore();
	void resetGame(int m);
	
    ~App();
};

#endif
