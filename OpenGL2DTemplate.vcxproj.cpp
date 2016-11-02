#include <windows.h>
#include <math.h>
#include <string>
#include <glut.h>

#define PI 3.14159265
#define val  (180.0 / PI);

double screenX = glutGet(GLUT_SCREEN_WIDTH);
double screenY = glutGet(GLUT_SCREEN_HEIGHT);
double playerX = screenX + 10;
double playerY = screenY + 10;
double playerAngle = 0;
double xDis = 0;
double yDis = 0;
double chaserX1 = 0;
double chaserY1 = 0;
double chaser1Angle = 0;
double chaserX2 = 0;
double chaserY2 = screenY;
double chaser2Angle = 0;
double targetX1 = screenX / 2 -50;
double targetY1 = screenY / 2 -50;
double traget1Angle = 0;
double targetX2 = screenX / 2 + 50;
double targetY2 = screenY / 2 +50;
double traget2Angle = 0;
double speedChaser1 = 0.6;
double speedChaser2 = 1.1;
double speedTarget1 = 1.4;
double speedTarget2 = 0.7;
long  score = 0;
std::string  scoreText = "Score: 0";
int mode = 0;
int pmode = 0;
std::string  timerText = "Time: 0m 0s";
int timer = 0;
bool specialPower = false;
int factor = 1;
int type = 0;
int timerStart = 0;

void startAgain(){
	playerX = screenX + 10;
	playerY = screenY + 10;
	playerAngle = 0;
	xDis = 0;
	yDis = 0;
	chaserX1 = 0;
	chaserY1 = 0;
	chaser1Angle = 0;
	chaserX2 = 0;
	chaserY2 = screenY;
	chaser2Angle = 0;
	targetX1 = screenX / 2 - 50;
	targetY1 = screenY / 2 - 50;
	traget1Angle = 0;
	targetX2 = screenX / 2 + 50;
	targetY2 = screenY / 2 + 50;
	traget2Angle = 0;
	speedChaser1 = 0.6;
	speedChaser2 = 1.1;
	speedTarget1 = 1.4;
	speedTarget2 = 0.7;
	score = 0;
	scoreText = "Score : 0";
	mode = 0;
	pmode = 0;
	timerText = "Time: 0m 0s";
	timer = 0;
	specialPower = false;
	factor = 1;
}

void scoredisplay(float x, float y, void *font, const char *string){
	const char *c;
	glRasterPos2f(x, y);
	for (c = string; *c != '\0'; c++) {
		glutBitmapCharacter(font, *c);
	}
}

void passM(int x, int y)
{
	double xDiff = playerX - x;
	double yDiff = playerY - y;
	playerAngle = atan(yDiff / xDiff) * val;
	if (xDiff >= 0)
		playerAngle -= 180;
	playerX = x;
	playerY = y;

	glutPostRedisplay();
}

void spe(int k, int x, int y)
{
	if (mode ==0 && k == GLUT_KEY_F1)
		mode = 2;
	else if (mode == 0 && k == GLUT_KEY_F2)
		mode = 3;	
	glutPostRedisplay();//redisplay to update the screen with the changed

}

void key(unsigned char k, int x, int y)//keyboard up function is called whenever the keyboard key is released
{
	if (k == (char)27)//if the letter q is pressed, then the object will go back to it's original color.
	{
		if (mode == 0 || mode == 1 || mode == 4)
			exit(0);
		else{
			pmode = mode;
			mode = 1;
		}
	}
	else if (k == 13 && (mode == 1 || mode == 4))
		startAgain();
	else if (k == ' ' && mode == 1)
		mode = pmode;
	else if (k == '1' && specialPower && type == 0){
		type = 1;
		factor = 2;
		timerStart = timer;
	}
	else if (k == '2' && specialPower && type == 0){
		type = 2;
		timerStart = timer;
	}
	glutPostRedisplay();//redisplay to update the screen with the changed
}

void time(int value)//timer animation function, allows the user to pass an integer valu to the timer function.
{
	if (mode == 2 && timer >= 300)
		mode = 4;
	if ((mode == 2 || mode == 3) && timer == 30)
		specialPower = true;
	if (type != 0 && timer - timerStart >= 30){
		type = 0;
		specialPower = false;
		factor = 1;
	}
	if (mode == 2 || mode == 3)
		timer++;
	glutTimerFunc(1000, time, 0);					//recall the time function after 1000 ms and pass a zero value as an input to the time func.
}

void Display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	switch (mode){
		case 0:
			glColor3f(1.0f, 0.0f, 0.0f);
			scoredisplay(screenX / 2 - 0.035*screenX, screenY / 2 - 0.04*screenY, (void *)GLUT_BITMAP_TIMES_ROMAN_24, "Welcome to Chase Game");
			scoredisplay(screenX / 2 - 0.03*screenX, screenY / 2, (void *)GLUT_BITMAP_TIMES_ROMAN_24, "Press F1 for 5min Mode");
			scoredisplay(screenX / 2 - 0.04*screenX, screenY / 2 + 0.04*screenY, (void *)GLUT_BITMAP_TIMES_ROMAN_24, "Press F2 for One Shot Mode");
			scoredisplay(screenX - 350, screenY - 40, (void *)GLUT_BITMAP_TIMES_ROMAN_24, "Press Esc to Exit");
			break;
		case 1 :
			glColor3f(1.0f, 0.0f, 0.0f);
			scoredisplay(screenX / 2 - 0.039*screenX, screenY / 2 - 0.06*screenY, (void *)GLUT_BITMAP_TIMES_ROMAN_24, "Game Paused");
			scoredisplay(screenX / 2 - 0.058*screenX, screenY / 2 - 0.02*screenY, (void *)GLUT_BITMAP_TIMES_ROMAN_24, "Press Space to Get Back");
			scoredisplay(screenX / 2 - 0.06*screenX, screenY / 2 + 0.02*screenY, (void *)GLUT_BITMAP_TIMES_ROMAN_24, "Press Enter to Start Again");
			scoredisplay(screenX / 2 - 0.04*screenX, screenY / 2 + 0.06*screenY, (void *)GLUT_BITMAP_TIMES_ROMAN_24, "Press Esc to Exit");
			break; 
		 case 4:
				glColor3f(1.0f, 0.0f, 0.0f);
				scoredisplay(screenX / 2 - 0.035*screenX, screenY / 2 - 0.04*screenY, (void *)GLUT_BITMAP_TIMES_ROMAN_24, "GAME OVER");
				scoredisplay(screenX / 2 - 0.06*screenX, screenY / 2, (void *)GLUT_BITMAP_TIMES_ROMAN_24, "Press Enter to Start Again");
				scoreText = "Your Final Score is " + std::to_string(score);
				scoredisplay(screenX / 2 - 0.046*screenX, screenY / 2 + 0.04*screenY, (void *)GLUT_BITMAP_TIMES_ROMAN_24, scoreText.c_str());
				break;
		case 2 :
		case 3 :
		//Player
		glPushMatrix();
		glTranslated(playerX, playerY, 0);
		glRotated(playerAngle, 0, 0, 1);
		glBegin(GL_POLYGON);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(50.0f, 0.0f, 0.0f);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(75.0f, 25.0f, 0.0f);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(50.0f, 50.0f, 0.0f);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 50.0f, 0.0f);
		glEnd();
		glPopMatrix();

		//Chasser1
		glPushMatrix();
		glTranslated(chaserX1, chaserY1, 0);
		glRotated(chaser1Angle, 0, 0, 1);
		glBegin(GL_POLYGON);
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(50.0f, 0.0f, 0.0f);
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(75.0f, 25.0f, 0.0f);
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(50.0f, 50.0f, 0.0f);
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 50.0f, 0.0f);
		glEnd();
		glPopMatrix();

		//Chasser2
		glPushMatrix();
		glTranslated(chaserX2, chaserY2, 0);
		glRotated(chaser2Angle, 0, 0, 1);
		glBegin(GL_POLYGON);
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(50.0f, 0.0f, 0.0f);
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(75.0f, 25.0f, 0.0f);
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(50.0f, 50.0f, 0.0f);
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 50.0f, 0.0f);
		glEnd();
		glPopMatrix();

		//Target1
		glPushMatrix();
		glTranslated(targetX1, targetY1, 0);
		glRotated(traget1Angle, 0, 0, 1);
		glBegin(GL_POLYGON);
		glColor3f(0.5f, 1.0f, 0.2f);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glColor3f(0.5f, 1.0f, 0.2f);
		glVertex3f(50.0f, 0.0f, 0.0f);
		glColor3f(0.5f, 1.0f, 0.2f);
		glVertex3f(75.0f, 25.0f, 0.0f);
		glColor3f(0.5f, 1.0f, 0.2f);
		glVertex3f(50.0f, 50.0f, 0.0f);
		glColor3f(0.5f, 1.0f, 0.2f);
		glVertex3f(0.0f, 50.0f, 0.0f);
		glEnd();
		glPopMatrix();

		//Target2
		glPushMatrix();
		glTranslated(targetX2, targetY2, 0);
		glRotated(traget2Angle, 0, 0, 1);
		glBegin(GL_POLYGON);
		glColor3f(0.5f, 1.0f, 0.2f);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glColor3f(0.5f, 1.0f, 0.2f);
		glVertex3f(50.0f, 0.0f, 0.0f);
		glColor3f(0.5f, 1.0f, 0.2f);
		glVertex3f(75.0f, 25.0f, 0.0f);
		glColor3f(0.5f, 1.0f, 0.2f);
		glVertex3f(50.0f, 50.0f, 0.0f);
		glColor3f(0.5f, 1.0f, 0.2f);
		glVertex3f(0.0f, 50.0f, 0.0f);
		glEnd();
		glPopMatrix();

		scoreText = "Score: " + std::to_string(score);
		scoredisplay(10, 30, (void *)GLUT_BITMAP_9_BY_15, scoreText.c_str());

		timerText = "Time: " + std::to_string(timer / 60) + "m " + std::to_string(timer % 60) + "s";
		scoredisplay(10, 50, (void *)GLUT_BITMAP_9_BY_15, timerText.c_str());
		if (specialPower){
			if (type == 0){
			glColor3f(0.0f, 1.0f, 0.0f);
			scoredisplay(screenX - 350, screenY - 100, (void *)GLUT_BITMAP_TIMES_ROMAN_24, "Now Available");
			}
			else if (type == 1){
				glColor3f(0.0f, 0.0f, 1.0f);
				scoredisplay(screenX - 350, screenY - 100, (void *)GLUT_BITMAP_TIMES_ROMAN_24, "Double Points Activated");
			}
			else{
				glColor3f(0.0f, 0.0f, 1.0f);
				scoredisplay(screenX - 350, screenY - 100, (void *)GLUT_BITMAP_TIMES_ROMAN_24, "Freeze Chasers Activated");
			}
		}
		else{
			glColor3f(1.0f, 0.0f, 0.0f);
			scoredisplay(screenX - 350, screenY - 100, (void *)GLUT_BITMAP_TIMES_ROMAN_24, "Not Available");
		}
		scoredisplay(screenX - 350, screenY - 190, (void *)GLUT_BITMAP_TIMES_ROMAN_24, "Special Powers");
		scoredisplay(screenX - 350, screenY - 160, (void *)GLUT_BITMAP_TIMES_ROMAN_24, "Press 1 to Double Points");
		scoredisplay(screenX - 350, screenY - 130, (void *)GLUT_BITMAP_TIMES_ROMAN_24, "Press 2 to Freeze Chasers");
		glColor3f(1.0f, 0.0f, 0.0f);
		scoredisplay(screenX - 350, screenY - 40, (void *)GLUT_BITMAP_TIMES_ROMAN_24, "Press Esc to Pause");

		break;
		
		}
		glFlush();
}

void Anim()
{
	if (mode == 2 || mode == 3 || (playerX == screenX+10 && playerY == screenY +10))
	{
		//Chaser1
		double xDiff = playerX - chaserX1;
		double yDiff = playerY - chaserY1;
		double distance = sqrt(xDiff*xDiff + yDiff*yDiff);
		if (distance != 0){
			xDis = (speedChaser1 * xDiff) / distance;
			yDis = (speedChaser1 * yDiff) / distance;
		}
		
		if (type != 2){
			chaserX1 += xDis;
			chaserY1 += yDis;
		}

		xDiff = chaserX1 - playerX;
		yDiff = chaserY1 - playerY;

		chaser1Angle = atan(yDiff / xDiff) * val;
		if (xDiff > 0)
			chaser1Angle -= 180;

		//Chaser2
		xDiff = playerX - chaserX2;
		yDiff = playerY - chaserY2;
		distance = sqrt(xDiff*xDiff + yDiff*yDiff);

		if (distance != 0){
			xDis = (speedChaser2 * xDiff) / distance;
			yDis = (speedChaser2 * yDiff) / distance;
		}

		if (type != 2){
			chaserX2 += xDis;
			chaserY2 += yDis;
		}
		xDiff = chaserX2 - playerX;
		yDiff = chaserY2 - playerY;
		chaser2Angle = atan(yDiff / xDiff) * val;
		if (xDiff > 0)
			chaser2Angle -= 180;

		//Target1
		xDiff = playerX - targetX1;
		yDiff = playerY - targetY1;
		distance = sqrt(xDiff*xDiff + yDiff*yDiff);

		if (distance != 0){
			xDis = (speedTarget1 * xDiff) / distance;
			yDis = (speedTarget1 * yDiff) / distance;
		}
		if (distance <= screenX / 2)
			targetX1 -= xDis;

		if (distance <= screenY / 2)
			targetY1 -= yDis;

		if (targetX1 >= screenX || targetX1 <= 0 || targetY1 >= screenY || targetY1 <= 0){
			targetX1 = screenX / 2;
			targetY1 = screenY / 2;
		}

		xDiff = targetX1 - playerX;
		yDiff = targetY1 - playerY;
		traget1Angle = atan(yDiff / xDiff) * val;
		if (xDiff < 0)
			traget1Angle -= 180;

		//Target2
		xDiff = playerX - targetX2;
		yDiff = playerY - targetY2;
		distance = sqrt(xDiff*xDiff + yDiff*yDiff);

		if (distance != 0){
			xDis = (speedTarget2 * xDiff) / distance;
			yDis = (speedTarget2 * yDiff) / distance;
		}
		if (distance <= screenX / 2)
			targetX2 -= xDis;

		if (distance <= screenY / 2)
			targetY2 -= yDis;

		if (targetX2 >= screenX || targetX2 <= 0 || targetY2 >= screenY || targetY2 <= 0){
			targetX2 = screenX / 2;
			targetY2 = screenY / 2;
		}

		xDiff = targetX2 - playerX;
		yDiff = targetY2 - playerY;
		traget2Angle = atan(yDiff / xDiff) * val;
		if (xDiff < 0)
			traget2Angle -= 180;

		//Check for collision
		if ((playerX - 50) <= targetX1 && (playerX + 50) >= targetX1 && (playerY - 25) <= targetY1 && (playerY + 25) >= targetY1){
			score = score + (factor);
			targetX1 = screenX / 2;
			targetY1 = screenY / 2;
			PlaySoundA((LPCSTR) "button-1.WAV", NULL, SND_FILENAME | SND_ASYNC);
		}

		if ((playerX - 50) <= targetX2 && (playerX + 50) >= targetX2 && (playerY - 25) <= targetY2 && (playerY + 25) >= targetY2){
			score = score + (factor);
			targetX2 = screenX / 2;
			targetY2 = screenY / 2;
			PlaySoundA((LPCSTR) "button-1.WAV", NULL, SND_FILENAME | SND_ASYNC);
		}

		if ((playerX - 50) <= chaserX1 && (playerX + 50) >= chaserX1 && (playerY - 25) <= chaserY1 && (playerY + 25) >= chaserY1){
			if (mode == 3)
				mode = 4;
			else{
				score = score - (factor);
				chaserX1 = 0;
				chaserY1 = 0;
				PlaySoundA((LPCSTR) "button-3.WAV", NULL, SND_FILENAME | SND_ASYNC);
			}
		}

		if ((playerX - 50) <= chaserX2 && (playerX + 50) >= chaserX2 && (playerY - 25) <= chaserY2 && (playerY + 25) >= chaserY2){
			if (mode == 3)
				mode = 4; 
			else{
				score = score - (factor);
				chaserX2 = 0;
				chaserY2 = screenY;
				PlaySoundA((LPCSTR) "button-3.WAV", NULL, SND_FILENAME | SND_ASYNC);
			}
		}


	}
	
	

	for (int i = 0; i < 1000000; i++);
	glutPostRedisplay();
}

void main(int argc, char** argr)
{

	glutInit(&argc, argr);
	glutInitWindowSize(screenX, screenY);
	glutCreateWindow("Control");
	glutFullScreen();
	glutDisplayFunc(Display);
	glutIdleFunc(Anim);
	glutSetCursor(GLUT_CURSOR_NONE);
	glutPassiveMotionFunc(passM);
				//call the passive motion function
	//glutMouseFunc(actM);
				//call the mouse function
	glutKeyboardFunc(key);
				//call the keyboard function
	//glutKeyboardUpFunc(keyUp);
				//call the keyboard up function
	glutSpecialFunc(spe);
				//call the keyboard special keys function
	//glutSpecialUpFunc(speUp);
				//call the keyboard special keys up function
	glutTimerFunc(0,time,0);
				//call the timer function
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	gluOrtho2D(0.0, screenX, screenY, 0.0);
	glutMainLoop();//don't call any method after this line as it will not be reached.
}