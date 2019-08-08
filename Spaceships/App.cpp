#define _USE_MATH_DEFINES
#include "App.h"
#include <math.h>
#include <deque>
#include "visualc15\Al.h"
#include "visualc15\Enemies.h"
#include "visualc15\Rstash.h"
#include <Windows.h>
#include <MMSystem.h>
#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <ctime>
#include <cstdlib>

using namespace std;

deque<Enemies*> enemycats;
deque<Enemies*> secretEnemy;
deque<bool>checkHit;
deque<bool>checkHitboss;
deque<int>bossLife;
deque<ucm::Rectangle*> msl;
deque<ucm::Rectangle*>msl1;
deque<ucm::Rectangle*>msl2;
vector<ucm::Rectangle*> menu;
vector<string> v;

App::App(const char* label, int x, int y, int w, int h) : GlutApp(label, x, y, w, h) {
	// Initialize state variables

	//PlaySound(TEXT("kirby.wav"), NULL, SND_LOOP | SND_ASYNC);
	wall = loadTexture("..\\space.bmp");
	background = new TexRect(-1, 1, 2, 2);

	menu.push_back(new ucm::Rectangle(-0.25, 0.3, 0.5, 0.25));
	menu.push_back(new ucm::Rectangle(-0.25, 0.0, 0.5, 0.25));
	menu.push_back(new ucm::Rectangle(-0.25, -0.3, 0.5, 0.25));

	mx = -1.0;
	my = -1.0;
	score = 0;
	var = -1;
	// This is our ship
	mainc->al = mainc->loadTexture("..\\al.bmp");

	//enemy hit bool for all enemies
	for (int i = 0; i < 3; i++) {
		bossLife.push_back(9);
	}
	for (int i = 0; i < 3; i++) {
		checkHitboss.push_back(false);
	}
	for (int i = 0; i < 26; ++i) {
		checkHit.push_back(false);
	}
	// This is the enemy
	enemyY = 1.0;

	enemycats.push_back(new Enemies(-0.8f, 0.7, 0.1f, 0.1f));
	enemycats.push_back(new Enemies(-0.5f, 0.7, 0.1f, 0.1f));
	enemycats.push_back(new Enemies(-0.2f, 0.7, 0.1f, 0.1f));
	enemycats.push_back(new Enemies(0.1f, 0.7, 0.1f, 0.1f));
	enemycats.push_back(new Enemies(0.4f, 0.7, 0.1f, 0.1f));
	enemycats.push_back(new Enemies(0.7f, 0.7, 0.1f, 0.1f));

	for (int i = 0; i <6; i++)
	{
		enemycats[i]->cat = enemycats[i]->loadTexture("..\\greycat.bmp");
	}

	enemyZ = 1.0; //This is the second set of enemies, the row (7) 

	enemycats.push_back(new Enemies(-0.95f, 0.9, 0.1f, 0.1f));
	enemycats.push_back(new Enemies(-0.65f, 0.9, 0.1f, 0.1f));
	enemycats.push_back(new Enemies(-0.35f, 0.9, 0.1f, 0.1f));
	enemycats.push_back(new Enemies(-0.05f, 0.9, 0.1f, 0.1f));
	enemycats.push_back(new Enemies(0.25f, 0.9, 0.1f, 0.1f));
	enemycats.push_back(new Enemies(0.55f, 0.9, 0.1f, 0.1f));
	enemycats.push_back(new Enemies(0.85f, 0.9, 0.1f, 0.1f));
	for (int i = 6; i < enemycats.size(); i++)
	{
		enemycats[i]->cat = enemycats[i]->loadTexture("..\\greycat.bmp");
	}


	enemyA = 1.0; //This is the 3rd row of (6)

	enemycats.push_back(new Enemies(-0.8f, 1.1, 0.075f, 0.075f));
	enemycats.push_back(new Enemies(-0.5f, 1.1, 0.075f, 0.075f));
	enemycats.push_back(new Enemies(-0.2f, 1.1, 0.075f, 0.075f));
	enemycats.push_back(new Enemies(0.1f, 1.1, 0.075f, 0.075f));
	enemycats.push_back(new Enemies(0.4f, 1.1, 0.075f, 0.075f));
	enemycats.push_back(new Enemies(0.7f, 1.1, 0.075f, 0.075f));

	for (int i = 13; i < enemycats.size(); i++)
	{
		enemycats[i]->cat = enemycats[i]->loadTexture("..\\blackcat.bmp");
	}


	enemyB = 1.0; //This is the fourth set of enemies, the row (7) 

	enemycats.push_back(new Enemies(-0.95f, 1.3, 0.05f, 0.05f));
	enemycats.push_back(new Enemies(-0.65f, 1.3, 0.05f, 0.05f));
	enemycats.push_back(new Enemies(-0.35f, 1.3, 0.05f, 0.05f));
	enemycats.push_back(new Enemies(-0.05f, 1.3, 0.05f, 0.05f));
	enemycats.push_back(new Enemies(0.25f, 1.3, 0.05f, 0.05f));
	enemycats.push_back(new Enemies(0.55f, 1.3, 0.05f, 0.05f));
	enemycats.push_back(new Enemies(0.85f, 1.3, 0.05f, 0.05f));
	for (int i = 19; i < enemycats.size(); i++)
	{
		enemycats[i]->cat = enemycats[i]->loadTexture("..\\orangecat.bmp");
	}

	secretE = 1.0; // the boss

	secretEnemy.push_back(new Enemies(-0.95f, 3.0f, 0.3f, 0.3f));
	secretEnemy.push_back(new Enemies(-0.25f, 3.0f, 0.3f, 0.3f));
	secretEnemy.push_back(new Enemies(+0.45f, 3.0f, 0.3f, 0.3f));
	for (int i = 0; i < secretEnemy.size(); i++)
	{
		secretEnemy[i]->cat = secretEnemy[i]->loadTexture("..\\greycat.bmp");
	}

	
	// At the start, our ship should move to the right
	move = true;
	right = true;
	left = true;

	up = true;
	down = true;
	// Variables for enemy movement (circling the ship)
	theta = 0.0f;
	inc = 0.05f;

	// Specifies that at the start, the enemy has not been shot
	shot = false;

	// Position of the missle
	missleX = 0;
	missleY = 0.5;
	missleX1 = 0;
	missleY1 = 0.5;
	missleX2 = 0;
	missleY2 = 0.5;

	// Count how many missles we have fired
	counter = 0;

	// A variable that stores whether we have won or not
	gameover = false;

	// A variable that specifies whether we should execute idle function
	loop = true;


	mode = -1;
}



void App::draw() {

	// Clear the screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Set background color to black
	glClearColor(0.0, 0.0, 0.0, 1.0);

	// Set up the transformations stack
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	 if (mode == -1)
	{
		glColor3d(1.0, 0.0, 0.0);


		print(-0.25, 0.75, 0.0, "Space Katz");

		print(-0.25, 0.15, 0.0, "New Game");
		print(-0.25, 0.0, 0.0, "High Scores"); 
		deque<Enemies *> cats;
		cats.push_back(new Enemies(-0.8f, 0.7, 0.1f, 0.1f));
		cats.push_back(new Enemies(-0.5f, 0.7, 0.1f, 0.1f));
		cats.push_back(new Enemies(-0.2f, 0.7, 0.1f, 0.1f));
		cats.push_back(new Enemies(0.1f, 0.7, 0.1f, 0.1f));
		cats.push_back(new Enemies(0.4f, 0.7, 0.1f, 0.1f));
		cats.push_back(new Enemies(0.7f, 0.7, 0.1f, 0.1f));

		for (int i = 6; i < cats.size(); i++)
		{
			cats[i]->cat = cats[i]->loadTexture("..\\greycat.bmp");
		}

		for (int i = 0; i < cats.size(); i++)
		{
			glBindTexture(GL_TEXTURE_2D, enemycats[i]->cat);
			cats[i]->test->TexRect::draw();
		}

		print(-0.25, -0.15, 0.0, "Exit");
		print(-0.25, -0.5, 0.0, "Instructions");

		if (mx < .25 && mx > -.25 && my < 0.3 && my > 0.1)
		{
			mode = 1;
		}
		else if (mx < .25 && mx > -.25 && my < 0.1 && my > -0.1)
			mode = 2;
		else if (mx < .25 && mx > -.25 && my < -0.1 && my > -0.25)
			exit(0);
		else if (mx < .25 && mx > -.25 && my < -0.35 && my > -0.5)
			mode = 4;
		mx = -1.0;
		my = -1.0;
	}
	else if (mode == 1)
	{
		// If a missle has been fired and it's not game over, draw that missle
		if (mainc->missle & !gameover) {
			for (int i = 0; i < msl.size(); i++)
				msl[i]->draw();
		}
		if (mainc->missle1 & !gameover) {
			for (int i = 0; i < msl1.size(); i++)
				msl1[i]->draw();
		}
		if (mainc->missle2 & !gameover) {
			for (int i = 0; i < msl2.size(); i++)
				msl2[i]->draw();
		}


		glColor3d(1.0, 1.0, 1.0);

		glBindTexture(GL_TEXTURE_2D, mainc->al);
		mainc->test->TexRect::draw();



		//draw the enemies

		//boss enemy
		for (int i = 0; i < secretEnemy.size(); i++) {
			if (!checkHitboss[i]) {
				glBindTexture(GL_TEXTURE_2D, secretEnemy[i]->cat);
				secretEnemy[i]->test->TexRect::draw();
			}
		}

		for (int i = 0; i < enemycats.size(); i++)
		{
			if (!checkHit[i]) {
				glBindTexture(GL_TEXTURE_2D, enemycats[i]->cat);
				enemycats[i]->test->TexRect::draw();
			}

		}

		//textual features
		print(-0.9, 0.8, 0.0, "ESC = quit");
		print(-0.9, 0.7, 0.0, "Z = menu");
		print(-0.9, 0.6, 0.0, "R = restart");
		if (!move)
			print(-0.2, 0.0, 0.0, "PAUSE");
		
		print(0.5, -0.8, 0.0, "Score:");

		itoa(score, strscore, 10);
		print(0.8, -0.8, 0.0, strscore);



		glBindTexture(GL_TEXTURE_2D, wall);
		background->draw();


		

		glDisable(GL_TEXTURE_2D);
	}
	
	else if (mode == 2)
	{
		print(-0.25, 0.75, 0.0, "HIGHSCORES");
		getScores();
		float y = 0.5;
		for (int i = 0; i <5; i++)
		{
			int val = atoi(v[i].c_str());


			print(-0.25, y, 0.0, itoa(i + 1, strscore, 10));
			print(-0.20, y, 0.0, ". ");
			itoa(val, strscore, 10);
			print(-0.15,y, 0.0, strscore);
			y = y - 0.3;
		}
	}
	else if (mode == 3)
	{
		if (var == -1)
		{
			PlaySound(TEXT("explosion.wav"), NULL, SND_SYNC | SND_NODEFAULT);
			var++;

			saveScore();
		}
		print(-0.25, 0, 0, "GAME OVER");
		
		itoa(score, strscore, 10);
		
		

		if (score >= highscore)
		{
			print(-.25, -0.5, 0.0, "new high score!");
			print(0, -0.25, 0.0, strscore);
			print(-.25, -0.25, 0.0, "score:");
		}
		else 
		{
			print(0, -0.25, 0.0, strscore);
			print(-.25, -0.25, 0.0, "score:");
		}

	}
	else if (mode == 4)
	{
		print(-0.25, 0.75, 0.0, "Instructions");
	
		print(-0.25, 0.3, 0.0, "Left = A");
		print(-0.25, 0.2, 0.0, "Right = D");
		print(-0.25, 0.1, 0.0, "Up = W");
		print(-0.25, 0.0, 0.0, "Down = S");
		print(-0.25, -0.1, 0.0, "Fire = F");
		print(-0.25, -0.2, 0.0, "Special Fire = G");

		print(-0.25, -0.4, 0.0, "Return to menu = Z");
		print(-0.25, -0.5, 0.0, "Restart Game = R");

	}
	// We have been drawing everything to the back buffer
	// Swap the buffers to see the result of what we drew
	glFlush();
	glutSwapBuffers();

}

void App::keyPress(unsigned char key) {

	if (key == ' ') {
		// Uncomment below to enable user to stop moving
		move = !move;
	}
	
	if (move && mode ==1) {
		
		if (key == 'f') {
			// Fire a missle from the current position
			missleX = mainc->test->getX() + 0.04f;
			missleY = mainc->test->getY() + 0.05f;
			r1 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
			r2 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
			r3 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
			msl.push_back(new ucm::Rectangle(missleX, missleY + 0.05f, 0.01f, 0.05f, r1, r2, r3));
			mainc->fire();

			// Increment missle counter
			counter++;
		}
		else if (key == 'g') {
			missleX = mainc->test->getX() + 0.04f;
			missleY = mainc->test->getY() + 0.05f;
			missleX2 = mainc->test->getX() + 0.03f;
			missleY2 = mainc->test->getY() + 0.05f;
			missleX1 = mainc->test->getX() + 0.03f;
			missleY1 = mainc->test->getY() + 0.05f;
			r1 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
			r2 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
			r3 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
			msl.push_back(new ucm::Rectangle(missleX, missleY + 0.03f, 0.02f, 0.02f, r2, r3, r1));
			msl1.push_back(new ucm::Rectangle(missleX1, missleY1 + 0.05f, 0.02f, 0.02f, r3, r1, r2));
			msl2.push_back(new ucm::Rectangle(missleX2, missleY2 + 0.05f, 0.02f, 0.02f, r1, r2, r3));
			mainc->fire();

			// Increment missle counter
			counter++;
		}
		else if (key == 'a')
		{
			if (left)
				mainc->test->setX(mainc->test->getX() - 0.03);
			else
				mainc->test->setX(mainc->test->getX());

		}
		else if (key == 'd')
		{

			if (right)
				mainc->test->setX(mainc->test->getX() + 0.03);
			else
				mainc->test->setX(mainc->test->getX());

		}
		else if (key == 'w')
		{
			if (up)
				mainc->test->setY(mainc->test->getY() + 0.03);
			else
				mainc->test->setY(mainc->test->getY());

		}
		else if (key == 's')
		{
			if (down)
				mainc->test->setY(mainc->test->getY() - 0.03);
			else
				mainc->test->setY(mainc->test->getY());
		}
		else if (key == 'z')
		{


			resetGame(-1);
		}
		else if (key == 'r')
			resetGame(1);
	}
	
	 if (key == 'z')
	{
		
		mode = -1;
		redraw();
	}
	
	if (key == 27)
	{
		// Exit the app when Esc key is pressed

		exit(0);
	}
}
void App::mouseDown(float x, float y) {
	// Update app state
	mx = x;
	my = y;

	redraw();

}

void App::idle() {
	// loop should always be true, unless it's game over
	if (loop && mode ==1) {

		// If the spaceship should move from side to side,
		// make it do so
		if (move) {
			float x = mainc->test->getX();
			float y = mainc->test->getY();

			if (x >= 0.85) {
				// Reached right edge, start moving left
				right = false;
				left = true;
			}

			else if (x <= -0.975) {
				// Reached left edge, start moving right
				left = false;
				right = true;
			}
			else
			{
				left = true;
				right = true;
			}

			if (y >= 0.975) {
				// Reached top edge, start moving left
				up = false;
				down = true;
			}

			else if (y <= -0.875) {
				// Reached bottom edge, start moving right
				down = false;
				up = true;
			}
			else
			{
				up = true;
				down = true;
			}



			// If there is a missle, make it go up
			if (mainc->missle && move) {
				missleY += 0.01f;
				for (int i = 0; i < msl.size(); i++)
					msl[i]->setY(msl[i]->getY() + 0.01f);

			}
			//new missle
			if (mainc->missle1 && move) {

				missleX1 -= 0.01f;
				missleY1 += 0.01f;

				for (int i = 0; i < msl1.size(); i++) {
					msl1[i]->setY(msl1[i]->getY() + 0.01f);
					msl1[i]->setX(msl1[i]->getX() - 0.004f);
				}
			}
			if (mainc->missle2 && move) {
				missleX2 += 0.01f;
				missleY2 += 0.01f;
				for (int i = 0; i < msl2.size(); i++) {
					msl2[i]->setY(msl2[i]->getY() + 0.01f);
					msl2[i]->setX(msl2[i]->getX() + 0.004f);
				}
			}
			//boss life
			for (int i = 0; i < secretEnemy.size(); ++i) {
				for (int k = 0; k < msl.size(); ++k) {
					if (secretEnemy[i]->test->contains(msl[k]->getX(), msl[k]->getY()) && bossLife[i] != 0) {
						bossLife[i] = bossLife[i] - 1;
						msl.erase(msl.begin() + k);
						score += 1000;
					}
					else if (secretEnemy[i]->test->contains(msl[k]->getX(), msl[k]->getY()) && bossLife[i] == 0) {
						checkHitboss[i] = true;
					}

					
				}
			}
			//hit detection
			for (int i = 0; i < enemycats.size(); ++i)
			{

				for (int k = 0; k < msl.size(); ++k)
				{

					if (enemycats[i]->test->contains(msl[k]->getX(), msl[k]->getY()) && !checkHit[i])
					{

						checkHit[i] = true;
						msl.erase(msl.begin() + k);
						if (i < 7)
							score += 50;
						else if (i < 13)
							score += 100;
						else if (i < 20)
							score += 200;
						else
							score += 500;
					}



				}
			}
			//hit detection for missle deque 1
			for (int i = 0; i < enemycats.size(); i++)
			{
				for (int k = 0; k < msl1.size(); k++)
				{
					if (enemycats[i]->test->contains(msl1[k]->getX(), msl1[k]->getY()) && !checkHit[i])
					{
						//enemycats.erase(enemycats.begin() + i);
						checkHit[i] = true;
						msl1.erase(msl1.begin() + k);
						if (i < 7)
							score += 50;
						else if (i < 13)
							score += 100;
						else if (i < 20)
							score += 200;
						else
							score += 500;
						//PlaySound(TEXT("invaderkilled.wav"), NULL, SND_SYNC | SND_NODEFAULT);
					}


				}
			}
			//hit detection for missle deque 2
			for (int i = 0; i < enemycats.size(); i++)
			{
				for (int k = 0; k < msl2.size(); k++)
				{
					if (enemycats[i]->test->contains(msl2[k]->getX(), msl2[k]->getY()) && !checkHit[i])
					{
						//enemycats.erase(enemycats.begin() + i);
						checkHit[i] = true;
						msl2.erase(msl2.begin() + k);
						if (i < 7)
							score += 50;
						else if (i < 13)
							score += 100;
						else if (i < 20)
							score += 200;
						else
							score += 500;
						//PlaySound(TEXT("invaderkilled.wav"), NULL, SND_SYNC | SND_NODEFAULT);
					}


				}
			}
			// Once missle leaves the screen, make it disappear
			if (missleY > 1) {
				mainc->missle = false;
				if (msl.size() > 0)
					msl.pop_back();
			}
			if (missleY1 > 1) {
				mainc->missle1 = false;
				if (msl1.size() > 0)
					msl1.pop_back();
			}
			if (missleY2 > 1) {
				mainc->missle2 = false;
				if (msl2.size() > 0)
					msl2.pop_back();
			}

			//enemy movement

			for (int i = secretEnemy.size() - 1; i >= 0; --i) {
				if (secretEnemy[i]->test->getY() > -1 && move && !checkHitboss[i]) {
					secretEnemy[i]->test->setY(secretEnemy[i]->test->getY() - 0.0009);
				}
				else if (secretEnemy[i]->test->getY() > -1 && move && checkHitboss[i]) {
					secretEnemy[i]->test->setY(secretEnemy[i]->test->getY());
				}
				else {
					mode = 3;
					break;
				}
			}

			for (int i = enemycats.size() - 1; i >= 0; i--)
			{
				if (enemycats[i]->test->getY() > -1 && move && !checkHit[i])
					enemycats[i]->test->setY(enemycats[i]->test->getY() - 0.0009);
				else if (enemycats[i]->test->getY() > -1 && move && checkHit[i]) {
					enemycats[i]->test->setY(enemycats[i]->test->getY());
				}

				else {
					mode = 3;
					break;
				}
			}

		}
		// Redraw the scene after all modifications have been made
		redraw();
	}
}

GLuint App::loadTexture(const char *filename) {
	GLuint texture_id;
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
	glEnable(GL_DEPTH_TEST);

	RgbImage theTexMap(filename);

	// Pixel alignment: each row is word aligned (aligned to a 4 byte boundary)
	//    Therefore, no need to call glPixelStore( GL_UNPACK_ALIGNMENT, ... );


	glGenTextures(1, &texture_id);
	glBindTexture(GL_TEXTURE_2D, texture_id);





	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, theTexMap.GetNumCols(), theTexMap.GetNumRows(),
		GL_RGB, GL_UNSIGNED_BYTE, theTexMap.ImageData());

	return texture_id;

}

void App::print(float x, float y, float z, char *string)
{
	//set the position of the text in the window using the x and y coordinates
	glColor3d(1.0, 1.0, 1.0);
	glRasterPos2f(x, y);
	//get the length of the string to display
	int len = (int)strlen(string);

	//loop to display character by character
	for (int i = 0; i < len; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
	}
}

void App::saveScore()
{
	ofstream file;
	file.open("highscore.txt", std::ofstream::out | std::ofstream::app);
	
	file<< score<<std::endl; 
	
	file.close();


	ifstream rfile("highscore.txt");
	string line;
	std::vector<int> hscore;
	while (std::getline(rfile, line))
	{
		int k = atoi(line.c_str());
		hscore.push_back(k);
		
	}
	std::sort(hscore.begin(), hscore.end());
	int i = hscore.size() - 1;
	
	rfile.close();
	
	highscore = hscore[i];

	file.open("highscore.txt", ios::out | ios::trunc);
	for (i = hscore.size()-1; i>=0; i--)
		file << hscore[i] << endl;
	file.close();

	
}

void App::getScores()
{
	ifstream rfile("highscore.txt");
	
	string line;
	
	
	while(rfile.good())
	{
		std::getline(rfile, line);
		v.push_back(line);
		
	}
	rfile.close();
}
void App::resetGame(int m)
{
	mode = m;
	score = 0;
	mainc->test->setX(0.0);
	mainc->test->setY(-0.7);
	enemycats.clear();
	msl.clear();
	msl1.clear();
	msl2.clear();
	checkHit.clear();

	for (int i = 0; i < 26; ++i) {
		checkHit.push_back(false);
	}
	enemycats.push_back(new Enemies(-0.8f, 0.7, 0.1f, 0.1f));
	enemycats.push_back(new Enemies(-0.5f, 0.7, 0.1f, 0.1f));
	enemycats.push_back(new Enemies(-0.2f, 0.7, 0.1f, 0.1f));
	enemycats.push_back(new Enemies(0.1f, 0.7, 0.1f, 0.1f));
	enemycats.push_back(new Enemies(0.4f, 0.7, 0.1f, 0.1f));
	enemycats.push_back(new Enemies(0.7f, 0.7, 0.1f, 0.1f));

	for (int i = 0; i < enemycats.size(); i++)
	{
		enemycats[i]->cat = enemycats[i]->loadTexture("..\\greycat.bmp");
	}

	

	enemycats.push_back(new Enemies(-0.95f, 0.9, 0.1f, 0.1f));
	enemycats.push_back(new Enemies(-0.65f, 0.9, 0.1f, 0.1f));
	enemycats.push_back(new Enemies(-0.35f, 0.9, 0.1f, 0.1f));
	enemycats.push_back(new Enemies(-0.05f, 0.9, 0.1f, 0.1f));
	enemycats.push_back(new Enemies(0.25f, 0.9, 0.1f, 0.1f));
	enemycats.push_back(new Enemies(0.55f, 0.9, 0.1f, 0.1f));
	enemycats.push_back(new Enemies(0.85f, 0.9, 0.1f, 0.1f));
	for (int i = 6; i < enemycats.size(); i++)
	{
		enemycats[i]->cat = enemycats[i]->loadTexture("..\\greycat.bmp");
	}


	enemyA = 1.0; //This is the 3rd row of (6)

	enemycats.push_back(new Enemies(-0.8f, 1.1, 0.075f, 0.075f));
	enemycats.push_back(new Enemies(-0.5f, 1.1, 0.075f, 0.075f));
	enemycats.push_back(new Enemies(-0.2f, 1.1, 0.075f, 0.075f));
	enemycats.push_back(new Enemies(0.1f, 1.1, 0.075f, 0.075f));
	enemycats.push_back(new Enemies(0.4f, 1.1, 0.075f, 0.075f));
	enemycats.push_back(new Enemies(0.7f, 1.1, 0.075f, 0.075f));

	for (int i = 13; i < enemycats.size(); i++)
	{
		enemycats[i]->cat = enemycats[i]->loadTexture("..\\blackcat.bmp");
	}



	enemycats.push_back(new Enemies(-0.95f, 1.3, 0.05f, 0.05f));
	enemycats.push_back(new Enemies(-0.65f, 1.3, 0.05f, 0.05f));
	enemycats.push_back(new Enemies(-0.35f, 1.3, 0.05f, 0.05f));
	enemycats.push_back(new Enemies(-0.05f, 1.3, 0.05f, 0.05f));
	enemycats.push_back(new Enemies(0.25f, 1.3, 0.05f, 0.05f));
	enemycats.push_back(new Enemies(0.55f, 1.3, 0.05f, 0.05f));
	enemycats.push_back(new Enemies(0.85f, 1.3, 0.05f, 0.05f));
	for (int i = 19; i < enemycats.size(); i++)
	{
		enemycats[i]->cat = enemycats[i]->loadTexture("..\\orangecat.bmp");
	}

	redraw(); 
}

App::~App() {
	delete r;

}
