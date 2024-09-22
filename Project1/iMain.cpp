#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include "iGraphics.h"

using namespace std;
#define screenWidth 1280
#define screenHeight 720
#define blockWidth 30
#define blockGap (screenHeight / 4)
#define sqSizeH 50
#define sqSizeW 50
#define bigJump 40 // 35
#define smallJump 25
#define runspeed  30 // 20
#define gravity 4 // 8
#define dx 20
#define floorOpenGap 200
#define diamondsize 20
#define buttonSize 20
#define pitSize 180
#define maxPlayer 6

#define leverSize 25
#define gapPos g1.pitX + 50 + floorOpenGap
#define platformSpeed 2

bool player1 = false;
bool player2 = false;
bool dead = false;
int numPlayer = 0;
double buttonWidth = 250; // width of the buttons
double buttonHeight = 115; // height of the buttons
double spacing = 90; // space between buttons
double playButtonY = screenHeight - 300;// starting position of the buttons due to logo
double startX = (screenWidth - buttonWidth) / 2;// starting position of the buttons
double instructionsButtonY = playButtonY - spacing;// jeno equal spacing thake
double leaderboardsButtonY = instructionsButtonY - spacing;
double credsButtonY = leaderboardsButtonY - spacing;
double quitButtonY = credsButtonY - spacing;
double creds = 0, menu = 1, escY = (screenHeight - 75), escX = 25, leaderboard = 0, play = 0, instruction = 0, loading = 0;
double velocityE = 2.5;
bool movingUp = true, movingDown = false;
bool elevatormovement1 = false, elevatormovement2 = false;
int doorV = 2;
bool movingUpD = false, movingDownD = false;


int bottomLine1 = blockWidth, bottomLine2 = blockWidth;
int points = 0;
int floorLevel1 = 0, floorLevel2 = 0;
int dy = 10;
bool moveJump1 = false;
bool moveJump1_2 = false; // Added for smaller jump for sq_1
int velocityY1 = 0;
bool yMoving1 = false;
int maxHeight = 150;
int travelledHeight = 0;
bool goingUp = false;
bool goingDown = false;
bool moveRight1 = false;
bool moveLeft1 = false;
bool name = false;
int c = 0;
bool moveJump2 = false;
bool moveJump2_2 = false;
int velocityY2 = 0;
bool yMoving2 = false;
bool moveRight2 = false;
bool moveLeft2 = false;
bool inAir1 = false, inAir2 = false;
bool atElevator = false;
bool EntryMusicOn = true;
bool playingMusic = false;
bool gainedDiamond = false;
int LodingTime = 0;
bool platformRight = true;
bool platformLeft = false;
bool onPlatform1 = false, onPlatform2 = false;


int rrindex1;
int lrindex1;
int shindex1;
int rrindex2;
int lrindex2;
int shindex2;
int wdoory;
int wdoorx;
int fdoory;
int fdoorx;
int doory;
int doorx;
void diamonds();
void button();
void define_Elements();
void Xboundary1(int *, int);
void Xboundary3(int &, int, bool);
int floorDetermination(int, int);
int jumpSpeedDetermination(int, int, int);
void runright1();
void runleft1();
void shead1();

void runright2();
void runleft2();
void shead2();

void Level1();
void Level3();
void elevator();
void door();
void lever();
void Platfrom1();
bool PlatformCheck(int, int);
bool music = true;

struct Platform{
	int x;
}platfrom1;

struct Door {
	int x, y;
}door1;

struct levers{
	int leverX, leverY;
	bool leverPress = false, over = false;
}l1;

struct player {
	char name[100];
	int point = 0;;
} p[maxPlayer];

struct square {
	int x = 0, y = 0;
	bool life = true;
};
square sq_1, sq_2;

struct elevator {
	int elevatorX, elevatorY, eGravity = 4;
	elevator(){
		eGravity = 4;
	}
}e1;

struct pit{
	int pitX, pitY;
}f1, w1, g1, g2;

struct diamond{
	int diamondX, diamondY;
	bool diamondContact = false;
}d1[4];

struct button{
	int buttonX, buttonY;
	bool buttonPress = false;
}b1, b2;

bool gameover = false;
char playButtonImage[30] = "images\\play1.bmp";
char instructionsButtonImage[30] = "images\\ins1.bmp";
char leaderboardsButtonImage[30] = "images\\Leaderboards1.bmp";
char creditsButtonImage[30] = "images\\credits1.bmp";
char quitButtonImage[30] = "images\\quit1.bmp";

char easy[30] = "images\\Easy1.bmp", hard[30] = "images\\Hard1.bmp";

bool EHdetermination = 1;

char rrun1[11][60] = { "Sprites\\FireBoy\\Run Right Head\\RRH_(1).bmp", "Sprites\\FireBoy\\Run Right Head\\RRH_(2).bmp",
"Sprites\\FireBoy\\Run Right Head\\RRH_(3).bmp", "Sprites\\FireBoy\\Run Right Head\\RRH_(4).bmp",
"Sprites\\FireBoy\\Run Right Head\\RRH_(5).bmp", "Sprites\\FireBoy\\Run Right Head\\RRH_(6).bmp",
"Sprites\\FireBoy\\Run Right Head\\RRH_(7).bmp", "Sprites\\FireBoy\\Run Right Head\\RRH_(8).bmp",
"Sprites\\FireBoy\\Run Right Head\\RRH_(9).bmp", "Sprites\\FireBoy\\Run Right Head\\RRH_(10).bmp",
"Sprites\\FireBoy\\Run Right Head\\RRH_(11).bmp" };

char lrun1[11][60] = { "Sprites\\FireBoy\\Run Left Head\\RLH_(1).bmp", "Sprites\\FireBoy\\Run Left Head\\RLH_(2).bmp",
"Sprites\\FireBoy\\Run Left Head\\RLH_(3).bmp", "Sprites\\FireBoy\\Run Left Head\\RLH_(4).bmp",
"Sprites\\FireBoy\\Run Left Head\\RLH_(5).bmp", "Sprites\\FireBoy\\Run Left Head\\RLH_(6).bmp",
"Sprites\\FireBoy\\Run Left Head\\RLH_(7).bmp", "Sprites\\FireBoy\\Run Left Head\\RLH_(8).bmp",
"Sprites\\FireBoy\\Run Left Head\\RLH_(9).bmp", "Sprites\\FireBoy\\Run Left Head\\RLH_(10).bmp",
"Sprites\\FireBoy\\Run Left Head\\RLH_(11).bmp" };

char statichead1[19][60] = { "Sprites\\FireBoy\\Static Head\\Head_(1).bmp", "Sprites\\FireBoy\\Static Head\\Head_(2).bmp",
"Sprites\\FireBoy\\Static Head\\Head_(3).bmp", "Sprites\\FireBoy\\Static Head\\Head_(4).bmp",
"Sprites\\FireBoy\\Static Head\\Head_(5).bmp", "Sprites\\FireBoy\\Static Head\\Head_(6).bmp",
"Sprites\\FireBoy\\Static Head\\Head_(7).bmp", "Sprites\\FireBoy\\Static Head\\Head_(8).bmp",
"Sprites\\FireBoy\\Static Head\\Head_(9).bmp", "Sprites\\FireBoy\\Static Head\\Head_(10).bmp",
"Sprites\\FireBoy\\Static Head\\Head_(11).bmp", "Sprites\\FireBoy\\Static Head\\Head_(12).bmp",
"Sprites\\FireBoy\\Static Head\\Head_(13).bmp", "Sprites\\FireBoy\\Static Head\\Head_(14).bmp",
"Sprites\\FireBoy\\Static Head\\Head_(15).bmp", "Sprites\\FireBoy\\Static Head\\Head_(16).bmp",
"Sprites\\FireBoy\\Static Head\\Head_(17).bmp", "Sprites\\FireBoy\\Static Head\\Head_(18).bmp",
"Sprites\\FireBoy\\Static Head\\Head_(19).bmp" };

char rrun2[8][70] = { "Sprites\\WaterGirl\\Run Right Head\\RRH_(1).bmp", "Sprites\\WaterGirl\\Run Right Head\\RRH_(2).bmp",
"Sprites\\WaterGirl\\Run Right Head\\RRH_(3).bmp", "Sprites\\WaterGirl\\Run Right Head\\RRH_(4).bmp",
"Sprites\\WaterGirl\\Run Right Head\\RRH_(5).bmp", "Sprites\\WaterGirl\\Run Right Head\\RRH_(6).bmp",
"Sprites\\WaterGirl\\Run Right Head\\RRH_(7).bmp", "Sprites\\WaterGirl\\Run Right Head\\RRH_(8).bmp" };

char lrun2[8][70] = { "Sprites\\WaterGirl\\Run Left Head\\RLH_(1).bmp", "Sprites\\WaterGirl\\Run Left Head\\RLH_(2).bmp",
"Sprites\\WaterGirl\\Run Left Head\\RLH_(3).bmp", "Sprites\\WaterGirl\\Run Left Head\\RLH_(4).bmp",
"Sprites\\WaterGirl\\Run Left Head\\RLH_(5).bmp", "Sprites\\WaterGirl\\Run Left Head\\RLH_(6).bmp",
"Sprites\\WaterGirl\\Run Left Head\\RLH_(7).bmp", "Sprites\\WaterGirl\\Run Left Head\\RLH_(8).bmp" };

char statichead2[30][70] = { "Sprites\\WaterGirl\\Static Head\\Head_(1).bmp", "Sprites\\WaterGirl\\Static Head\\Head_(2).bmp",
"Sprites\\WaterGirl\\Static Head\\Head_(3).bmp", "Sprites\\WaterGirl\\Static Head\\Head_(4).bmp",
"Sprites\\WaterGirl\\Static Head\\Head_(5).bmp", "Sprites\\WaterGirl\\Static Head\\Head_(6).bmp",
"Sprites\\WaterGirl\\Static Head\\Head_(7).bmp", "Sprites\\WaterGirl\\Static Head\\Head_(8).bmp",
"Sprites\\WaterGirl\\Static Head\\Head_(9).bmp", "Sprites\\WaterGirl\\Static Head\\Head_(10).bmp",
"Sprites\\WaterGirl\\Static Head\\Head_(11).bmp", "Sprites\\WaterGirl\\Static Head\\Head_(12).bmp",
"Sprites\\WaterGirl\\Static Head\\Head_(13).bmp", "Sprites\\WaterGirl\\Static Head\\Head_(14).bmp",
"Sprites\\WaterGirl\\Static Head\\Head_(15).bmp", "Sprites\\WaterGirl\\Static Head\\Head_(16).bmp",
"Sprites\\WaterGirl\\Static Head\\Head_(17).bmp", "Sprites\\WaterGirl\\Static Head\\Head_(18).bmp",
"Sprites\\WaterGirl\\Static Head\\Head_(19).bmp", "Sprites\\WaterGirl\\Static Head\\Head_(20).bmp",
"Sprites\\WaterGirl\\Static Head\\Head_(21).bmp", "Sprites\\WaterGirl\\Static Head\\Head_(22).bmp",
"Sprites\\WaterGirl\\Static Head\\Head_(23).bmp", "Sprites\\WaterGirl\\Static Head\\Head_(24).bmp",
"Sprites\\WaterGirl\\Static Head\\Head_(25).bmp", "Sprites\\WaterGirl\\Static Head\\Head_(26).bmp",
"Sprites\\WaterGirl\\Static Head\\Head_(27).bmp", "Sprites\\WaterGirl\\Static Head\\Head_(28).bmp",
"Sprites\\WaterGirl\\Static Head\\Head_(29).bmp", "Sprites\\WaterGirl\\Static Head\\Head_(30).bmp" };

bool compare(const player &a, const player &b) {
	return a.point > b.point;
}

void leaderboards() {
	sort(p, p + numPlayer, compare);
	ofstream outputFile("Leaderboards.txt");
	int outputCount = min(numPlayer, 5);
	for (int i = 0; i < outputCount; i++)
	{
		outputFile << p[i].name << " " << p[i].point << endl;
	}
	outputFile.close();
}

int level = 3;

void Level3(){

	iShowBMP(0, 0, "images\\level3.bmp");
	iShowBMP2(wdoorx, wdoory, "images\\Water door.bmp", 255);
	iShowBMP2(fdoorx, fdoory, "images\\Fire door.bmp", 255);
	iSetColor(255, 0, 255);
	if (!l1.over){
		iShowBMP2(l1.leverX, l1.leverY, "images\\off button.bmp", 0);
	}
	else if (l1.over){
		iShowBMP2(l1.leverX, l1.leverY, "images\\on button.bmp", 0);
	}
	if (!player1){
		if (!moveRight1 && !moveLeft1)
			iShowBMP2(sq_1.x, sq_1.y - 17, statichead1[shindex1], 0);
		if (moveRight1)
			iShowBMP2(sq_1.x, sq_1.y - 30, rrun1[rrindex1], 0);
		if (moveLeft1)
			iShowBMP2(sq_1.x, sq_1.y - 30, lrun1[lrindex1], 0);
	}
	if (!player2){
		if (!moveRight2 && !moveLeft2)
			iShowBMP2(sq_2.x, sq_2.y - 25, statichead2[shindex2], 0);
		if (moveRight2)
			iShowBMP2(sq_2.x, sq_2.y - 30, rrun2[rrindex2], 0);
		if (moveLeft2)
			iShowBMP2(sq_2.x, sq_2.y - 30, lrun2[lrindex2], 0);
	}

	iSetColor(255, 255, 255);

	iShowBMP(platfrom1.x, 0 + blockGap * 2, "images\\platform.bmp");

	iShowBMP(e1.elevatorX, e1.elevatorY, "images\\elevator.bmp");
	iShowBMP(door1.x, door1.y, "images\\door.bmp");

	iShowBMP(e1.elevatorX, e1.elevatorY, "images\\elevator.bmp");
	for (int i = 0; i < 4; i++)
	{
		if (!d1[i].diamondContact)
			iShowBMP2(d1[i].diamondX, d1[i].diamondY, "images\\diamond.bmp", 0);
	}



	iSetColor(255, 255, 255);
	char pointsStr[20];

	iSetColor(255, 0, 0);
	iShowBMP2(f1.pitX, f1.pitY, "images\\firepit.bmp", 0);
	iSetColor(0, 0, 255);
	iShowBMP2(w1.pitX, w1.pitY, "images\\waterpit.bmp", 0);
	iSetColor(0, 255, 0);
	iShowBMP2(g1.pitX, g1.pitY, "images\\poisonpit.bmp", 0);
	iShowBMP2(g2.pitX, g2.pitY, "images\\poisonpit.bmp", 0);
	iSetColor(128, 128, 128);
	if (!b1.buttonPress)
		iShowBMP2(b1.buttonX, b1.buttonY, "images\\button.bmp", 0);
	if (!b2.buttonPress)
		iShowBMP2(b2.buttonX, b2.buttonY, "images\\button.bmp", 0);
	char pStr[20], p1Str[20];
	sprintf_s(pStr, "Points: %d", p[numPlayer].point);
	iText(screenWidth - 100, screenHeight - 25, pStr, GLUT_BITMAP_TIMES_ROMAN_24);
	if ((!sq_1.life || !sq_2.life))
	{
		if (!dead) {
			numPlayer++;
			dead = true;
			leaderboards();
		}
		iClear();
		iShowBMP(0, 0, "images\\gameover.bmp");
		iSetColor(0, 0, 0);
		sprintf_s(p1Str, "Points: %d", p[numPlayer - 1].point);
		iText(screenWidth / 2 - 50, screenHeight / 2, p1Str, GLUT_BITMAP_TIMES_ROMAN_24);
	}
	if (player1 && player2){
		if (!dead) {
			p[numPlayer].point += 4;
			numPlayer++;
			dead = true;
		}
		iClear();
		iShowBMP(0, 0, "images\\gameover.bmp");
		iSetColor(0, 0, 0);
		sprintf_s(p1Str, "Points: %d", p[numPlayer - 1].point);
		iText(screenWidth / 2 - 50, screenHeight / 2, p1Str, GLUT_BITMAP_TIMES_ROMAN_24);
	}
}

void Level1(){
	iShowBMP(0, 0, "images\\level1 copy.bmp");
	iShowBMP2(wdoorx, wdoory, "images\\Water door.bmp", 255);
	iShowBMP2(fdoorx, fdoory, "images\\Fire door.bmp", 255);
	iShowBMP(e1.elevatorX, e1.elevatorY, "images\\elevator.bmp");
	for (int i = 0; i < 4; i++)
	{
		if (!d1[i].diamondContact)
			iShowBMP2(d1[i].diamondX, d1[i].diamondY, "images\\diamond.bmp", 0);
	}
	if (!player1){
		if (!moveRight1 && !moveLeft1)
			iShowBMP2(sq_1.x, sq_1.y - 17, statichead1[shindex1], 0);
		if (moveRight1)
			iShowBMP2(sq_1.x, sq_1.y - 30, rrun1[rrindex1], 0);
		if (moveLeft1)
			iShowBMP2(sq_1.x, sq_1.y - 30, lrun1[lrindex1], 0);
	}
	if (!player2){
		if (!moveRight2 && !moveLeft2)
			iShowBMP2(sq_2.x, sq_2.y - 25, statichead2[shindex2], 0);
		if (moveRight2)
			iShowBMP2(sq_2.x, sq_2.y - 30, rrun2[rrindex2], 0);
		if (moveLeft2)
			iShowBMP2(sq_2.x, sq_2.y - 30, lrun2[lrindex2], 0);
	}
	iSetColor(255, 255, 255);
	char pStr[20];
	char p1Str[20];
	iSetColor(255, 0, 0);
	iShowBMP2(f1.pitX, f1.pitY, "images\\firepit.bmp", 0);
	iSetColor(0, 0, 255);
	iShowBMP2(w1.pitX, w1.pitY, "images\\waterpit.bmp", 0);
	iSetColor(0, 255, 0);
	iShowBMP2(g1.pitX, g1.pitY, "images\\poisonpit.bmp", 0);
	iShowBMP2(g2.pitX, g2.pitY, "images\\poisonpit.bmp", 0);
	iSetColor(128, 128, 128);
	if (!b1.buttonPress)
		iShowBMP2(b1.buttonX, b1.buttonY, "images\\button.bmp", 0);
	if (!b2.buttonPress)
		iShowBMP2(b2.buttonX, b2.buttonY, "images\\button.bmp", 0);
	sprintf_s(pStr, "Points: %d", p[numPlayer].point);
	iText(screenWidth - 100, screenHeight - 25, pStr, GLUT_BITMAP_TIMES_ROMAN_24);
	if ((!sq_1.life || !sq_2.life))
	{
		if (!dead) {
			numPlayer++;
			dead = true;
		}
		iClear();
		iShowBMP(0, 0, "images\\gameover.bmp");
		iSetColor(0, 0, 0);
		sprintf_s(p1Str, "Points: %d", p[numPlayer - 1].point);
		iText(screenWidth / 2 - 50, screenHeight / 2, p1Str, GLUT_BITMAP_TIMES_ROMAN_24);
	}
	if (player1 && player2){

		if (!dead) {
			p[numPlayer].point += 2;
			numPlayer++;
			dead = true;
		}
		iClear();
		iShowBMP(0, 0, "images\\gameover.bmp");
		iSetColor(0, 0, 0);
		sprintf_s(p1Str, "Points: %d", p[numPlayer - 1].point);
		iText(screenWidth / 2 - 50, screenHeight / 2, p1Str, GLUT_BITMAP_TIMES_ROMAN_24);
	}
}



void iDraw() {
	iClear();
	
	if (menu == 1) {
		iShowBMP(0, 0, "images\\bg.bmp");
		iShowBMP2(startX, playButtonY, playButtonImage, 0);
		iShowBMP2(startX, instructionsButtonY, instructionsButtonImage, 0);
		iShowBMP2(startX, leaderboardsButtonY, leaderboardsButtonImage, 0);
		iShowBMP2(startX, credsButtonY, creditsButtonImage, 0);
		iShowBMP2(startX, quitButtonY, quitButtonImage, 0);
	}
	if (creds == 1) {
		iShowBMP(0, 0, "images\\credit.bmp");
	}
	if (instruction == 1) {
		iShowBMP(0, 0, "images\\instruction.bmp");
	}
	if (leaderboard == 1) {
		iShowBMP(0, 0, "images\\leaderboard.bmp");
		leaderboards();
		int startY = screenHeight - 400;
		int gap = 50;
		int outputCount = min(numPlayer, 5);
		for (int i = 0; i <outputCount; i++) {
			char str1[500], str2[500], str3[500];
			sprintf_s(str1, "%d.", i + 1);
			sprintf_s(str2, "%s", p[i].name);
			sprintf_s(str3, "%d", p[i].point);
			iSetColor(0, 0, 0);
			iText(450, startY - i * gap, str1, GLUT_BITMAP_TIMES_ROMAN_24);
			iText(500 + 100, startY - i * gap, str2, GLUT_BITMAP_TIMES_ROMAN_24);
			iText(650 + 100 + 50, startY - i * gap, str3, GLUT_BITMAP_TIMES_ROMAN_24);
		}
	}

	if (play == 1) {

		if (EHdetermination){

			iShowBMP2(startX, playButtonY - 50, easy, 0);
			iShowBMP2(startX, playButtonY - 150, hard, 0);

		}

		else{
			
			if (!name) {
				iShowBMP(0, 0, "images\\entername.bmp");
				iSetColor(0, 0, 0);
				iText(screenWidth / 2 - 25, screenHeight / 2 + 15, p[numPlayer].name, GLUT_BITMAP_TIMES_ROMAN_24);
			}
			else {
				if (level == 1)
					Level1();
				else if (level == 3)
					Level3();
			}
		}

	}
}

void iMouseMove(int mx, int my) {

}

void iPassiveMouseMove(int mx, int my) {

	if (EHdetermination){

		if (mx >= startX && mx <= startX + 236 && my >= playButtonY - 30 && my <= playButtonY - 50 + 100) {
			strcpy_s(easy, "images\\Easy2.bmp");
		}
		else{
			strcpy_s(easy, "images\\Easy1.bmp");
		}

		if (mx >= startX && mx <= startX + 236 && my >= playButtonY - 130 && my <= playButtonY - 150 + 100) {
			strcpy_s(hard, "images\\Hard2.bmp");
		}
		else{
			strcpy_s(hard, "images\\Hard1.bmp");
		}

	}




	if (menu == 1) {
		if (mx >= startX && mx <= startX + buttonWidth && my >= playButtonY && my <= playButtonY + buttonHeight) {
			strcpy_s(playButtonImage, "images\\play2.bmp");
		}
		else {
			strcpy_s(playButtonImage, "images\\play1.bmp");
		}

		if (mx >= startX && mx <= startX + buttonWidth && my >= instructionsButtonY && my <= instructionsButtonY + buttonHeight) {
			strcpy_s(instructionsButtonImage, "images\\ins2.bmp");
		}
		else {
			strcpy_s(instructionsButtonImage, "images\\ins1.bmp");
		}

		if (mx >= startX && mx <= startX + buttonWidth && my >= leaderboardsButtonY && my <= leaderboardsButtonY + buttonHeight) {
			strcpy_s(leaderboardsButtonImage, "images\\Leaderboards2.bmp");
		}
		else {
			strcpy_s(leaderboardsButtonImage, "images\\Leaderboards1.bmp");
		}

		if (mx >= startX && mx <= startX + buttonWidth && my >= credsButtonY && my <= credsButtonY + buttonHeight) {
			strcpy_s(creditsButtonImage, "images\\credits2.bmp");
		}
		else {
			strcpy_s(creditsButtonImage, "images\\credits1.bmp");
		}

		if (mx >= startX && mx <= startX + buttonWidth && my >= quitButtonY && my <= quitButtonY + buttonHeight) {
			strcpy_s(quitButtonImage, "images\\quit2.bmp");
		}
		else {
			strcpy_s(quitButtonImage, "images\\quit1.bmp");
		}
	}
}

void iMouse(int button, int state, int mx, int my)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{

		if (EHdetermination){

			if (mx >= startX && mx <= startX + 236 && my >= playButtonY - 30 && my <= playButtonY - 50 + 100) {
				level = 1;
				define_Elements();
				EHdetermination = 0;
			}


			if (mx >= startX && mx <= startX + 236 && my >= playButtonY - 130 && my <= playButtonY - 150 + 100) {
				level = 3;
				define_Elements();
				EHdetermination = 0;
			}

		}





		// Check if Play button is clicked
		if (menu == 1 && mx >= startX && mx <= startX + buttonWidth &&
			my >= playButtonY && my <= playButtonY + buttonHeight)
		{
			creds = 0;
			menu = 0;
			instruction = 0;
			leaderboard = 0;
			play = 1;

			define_Elements();
		}
		// Check if Instructions button is clicked
		else if (menu == 1 && mx >= startX && mx <= startX + buttonWidth &&
			my >= instructionsButtonY && my <= instructionsButtonY + buttonHeight)
		{
			creds = 0;
			menu = 0;
			instruction = 1;
			leaderboard = 0;
			play = 0;
		}
		// Check if Leaderboards button is clicked
		else if (menu == 1 && mx >= startX && mx <= startX + buttonWidth &&
			my >= leaderboardsButtonY && my <= leaderboardsButtonY + buttonHeight)
		{
			creds = 0;
			menu = 0;
			instruction = 0;
			leaderboard = 1;
			play = 0;
		}
		// Check if Credits button is clicked
		else if (menu == 1 && mx >= startX && mx <= startX + buttonWidth &&
			my >= credsButtonY && my <= credsButtonY + buttonHeight)
		{
			creds = 1;
			menu = 0;
			instruction = 0;
			leaderboard = 0;
			play = 0;
		}
		else if (menu == 1 && mx >= startX && mx <= startX + buttonWidth &&
			my >= quitButtonY && my <= quitButtonY + buttonHeight)
		{
			exit(0);
		}

	}
}

void specialUp(int key, int x, int y) {
	if (key == GLUT_KEY_RIGHT) {
		moveRight1 = false;
	}
	if (key == GLUT_KEY_LEFT) {
		moveLeft1 = false;
	}
}

void keyboardUp(unsigned char key, int x, int y){

	if (key == 'd' || key == 'D') {
		moveRight2 = false;
	}
	if (key == 'a' || key == 'A') {
		moveLeft2 = false;
	}
}

void iKeyboard(unsigned char key) {
	if (play == 1){
		if (!name)
		{
			if (key != '\b' && key != 13)
			{
				p[numPlayer].name[c++] = key;
				p[numPlayer].name[c] = '\0';
			}
			else if (key == 13)
			{
				p[numPlayer].name[c] = '\0';
				name = true;
			}
			else
			if (c > 0) p[numPlayer].name[--c] = '\0';
		}
	}
	if (key == 'd' || key == 'D') {
		moveRight2 = true;
	}
	if (key == 'a' || key == 'A') {
		moveLeft2 = true;
	}
	if (key == 'w' || key == 'W') {
		if (!moveJump2 &&  !inAir2 && !yMoving2) {
			moveJump2 = true;
			velocityY2 = jumpSpeedDetermination(sq_2.x, sq_2.y, floorLevel2);
			yMoving2 = true;
		}
	}
	if (key == 'm' || key == 'M'){
		if (music){
			music = false;
			PlaySound(0, 0, 0);
		}
		else{
			music = true;
			PlaySound("Music\\NormalOST", NULL, SND_LOOP | SND_ASYNC);
		}
	}

	if (key == 27) {
		creds = 0;
		menu = 1;
		instruction = 0;
		leaderboard = 0;
		play = 0;
		leaderboards();
		define_Elements();
	}
	if (key == 13) {
		if (!sq_1.life || !sq_2.life || player1 && player2) {
			leaderboards();
			define_Elements();
		}
	}

}

void iSpecialKeyboard(unsigned char key) {
	if (key == GLUT_KEY_RIGHT) {
		if (!moveRight1) {
			moveRight1 = true;
		}
	}
	if (key == GLUT_KEY_LEFT) {
		if (!moveLeft1) {
			moveLeft1 = true;
		}
	}
	if (key == GLUT_KEY_UP) {
		if (!moveJump1 &&  !inAir1 && !yMoving1) {
			moveJump1 = true;
			velocityY1 = jumpSpeedDetermination(sq_1.x, sq_1.y, floorLevel1);
			yMoving1 = true;
		}
	}
}

int jumpSpeedDetermination(int x, int y, int floor){

	int velocity;

	if (floor == 0 && x < 1080) {
		velocity = smallJump; // Smaller jump height
	}
	else if (floor == 1 && x > floorOpenGap - 20) {
		velocity = smallJump;
	}
	else if (floor == 2 && x < 1080) {
		velocity = smallJump;
	}
	else if (floor == 3 && x > 200) {
		velocity = smallJump;
	}
	else{
		velocity = bigJump;
	}

	if (level == 3){
		if (l1.over && x + sqSizeW > l1.leverX && x < l1.leverX + leverSize){
			velocity -= 5;
		}
	}

	return velocity;
}

void moveSq1() {
	if (play == 1) {
		floorLevel1 = floorDetermination(sq_1.x, sq_1.y);
		int bottomLine1 = (elevatormovement1) ? e1.elevatorY + blockWidth : blockWidth + floorLevel1 * blockGap;

		if (level == 3){
			if (l1.over && sq_1.x + sqSizeW > l1.leverX && sq_1.x < l1.leverX + leverSize && sq_1.y >= l1.leverY && sq_1.y <= l1.leverY + leverSize){

				bottomLine1 += leverSize - 10;
			}
		}
		if (moveRight1) {
			sq_1.x += dx;
			if (moveJump1){
				sq_1.x += dx / 10 + 2;
			}
		}
		if (moveLeft1) {
			sq_1.x -= dx;
			if (moveJump1){
				sq_1.x -= dx / 10 + 2;
			}

		}
		if (velocityY1 > 0) {
			sq_1.y += velocityY1;
			velocityY1 -= gravity;
			if (velocityY1 < 0)
				velocityY1 = 0;
		}


		else {

			inAir1 = true;
			if (sq_1.y > bottomLine1) {
				velocityY1 -= gravity;
				sq_1.y += velocityY1;
			}
			if (sq_1.y <= bottomLine1) {

				sq_1.y = bottomLine1;
				yMoving1 = false;
				moveJump1 = false;
				velocityY1 = 0;
				inAir1 = false;
			}
		}

		if (level == 1){
			Xboundary1(&sq_1.x, sq_1.y);
		}
		else if (level == 3){
			Xboundary3(sq_1.x, sq_1.y, moveJump1);
		}


	}
}

void moveSq2() {

	if (play == 1) {
		floorLevel2 = floorDetermination(sq_2.x, sq_2.y);
		bottomLine2 = (elevatormovement2) ? e1.elevatorY + blockWidth : blockWidth + floorLevel2 * blockGap;

		if (level == 3){
			if (l1.over && sq_2.x + sqSizeW > l1.leverX && sq_2.x < l1.leverX + leverSize && sq_2.y >= l1.leverY && sq_2.y <= l1.leverY + leverSize){

				bottomLine2 += leverSize - 10;
			}
		}
		if (moveRight2) {
			sq_2.x += dx;
			if (moveJump2){
				sq_2.x += dx / 10 + 2;
			}
		}
		if (moveLeft2) {
			sq_2.x -= dx;
			if (moveJump2){
				sq_2.x -= dx / 10 + 2;
			}
		}
		if (velocityY2 > 0) {
			sq_2.y += velocityY2;
			velocityY2 -= gravity;
			if (velocityY2 < 0)
				velocityY2 = 0;
		}
		else {
			inAir2 = true;
			if (sq_2.y > bottomLine2) {
				velocityY2 -= gravity;
				sq_2.y += velocityY2;
			}
			if (sq_2.y <= bottomLine2) {
				sq_2.y = bottomLine2;
				yMoving2 = false;
				moveJump2 = false;
				velocityY2 = 0;
				inAir2 = false;
			}
		}


		if (level == 1){
			Xboundary1(&sq_2.x, sq_2.y);
		}
		else if (level == 3){
			Xboundary3(sq_2.x, sq_2.y, moveJump2);
		}
	}
}

bool PlatformCheck(int x, int y){
	//platfrom1.x

	if (x + 50 > platfrom1.x && x < platfrom1.x + 200 && y == blockGap * 2 + blockWidth)
		return true;
	else
		return false;

}

void runright1(){
	if (moveRight1)
		rrindex1++;
	if (rrindex1 > 10)
	{
		rrindex1 = 0;
	}
}

void runleft1(){
	if (moveLeft1)
		lrindex1++;
	if (lrindex1 > 10)
	{
		lrindex1 = 0;
	}
}

void shead1(){

	shindex1++;
	if (shindex1 > 18)
	{
		shindex1 = 0;
	}
}


void runright2(){
	if (moveRight2)
		rrindex2++;
	if (rrindex2 > 7)
	{
		rrindex2 = 0;
	}
}

void runleft2(){
	if (moveLeft2)
		lrindex2++;
	if (lrindex2 > 7)
	{
		lrindex2 = 0;
	}
}

void shead2(){

	shindex2++;
	if (shindex2 > 29)
	{
		shindex2 = 0;
	}
}

void moving_obsticles() {

	elevator();
	if (level >= 2){

		door();

		Platfrom1();
	}
}


void Platfrom1(){
	if (platformRight){
		if (platfrom1.x >= screenWidth - 200){
			platformRight = false;
			platformLeft = true;
		}
	}

	else if (platformLeft){
		if (platfrom1.x <= gapPos + 200){
			platformRight = true;
			platformLeft = false;
		}
	}

	if (platformRight){
		platfrom1.x += platformSpeed;
	}
	else if (platformLeft){
		platfrom1.x -= platformSpeed;
	}

	if (PlatformCheck(sq_1.x, sq_1.y) && level == 3){
		if (platformRight){
			sq_1.x += platformSpeed;
		}
		else if (platformLeft){
			sq_1.x -= platformSpeed;
		}
	}

	if (PlatformCheck(sq_2.x, sq_2.y) && level == 3){
		if (platformRight){
			sq_2.x += platformSpeed;
		}
		else if (platformLeft){
			sq_2.x -= platformSpeed;
		}
	}


}


void lever()
{
	if ((sq_1.x + sqSizeW > l1.leverX && sq_1.x < l1.leverX + leverSize && sq_1.y >= l1.leverY  && sq_1.y <= l1.leverY + leverSize) || (sq_2.x + sqSizeW > l1.leverX && sq_2.x < l1.leverX + leverSize && sq_2.y >= l1.leverY  && sq_2.y <= l1.leverY + leverSize))
	{
		if (!l1.over){

			if (l1.leverPress)
				l1.leverPress = false;
			else
				l1.leverPress = true;

			l1.over = true;
		}
	}
	else
		l1.over = false;

}


void door()
{
	lever();
	if (l1.leverPress){
		movingUpD = true;
		movingDownD = false;

		if (door1.y >= blockGap * 4){
			movingUpD = false;
		}

	}
	if (!l1.leverPress){
		movingDownD = true;
		movingUpD = false;

		if (door1.y == blockGap * 3 + blockWidth){
			movingDownD = false;
		}

	}
	if (movingUpD){
		door1.y += doorV;
	}
	if (movingDownD){
		door1.y -= doorV;
	}

}


void elevator(){
	button();

	if (((sq_1.y >= e1.elevatorY + blockWidth && sq_1.y < 2 * blockGap + blockWidth) && (sq_1.x < floorOpenGap - 20)) || ((sq_1.y >= e1.elevatorY + blockWidth && sq_1.y < 3 * blockGap) && (sq_1.x <= floorOpenGap - sqSizeW))){
		elevatormovement1 = true;
	}
	else
		elevatormovement1 = false;

	if (((sq_2.y >= e1.elevatorY + blockWidth && sq_2.y < 2 * blockGap + blockWidth) && (sq_2.x < floorOpenGap - 20)) || ((sq_2.y >= e1.elevatorY + blockWidth && sq_2.y < 3 * blockGap) && (sq_2.x <= floorOpenGap - sqSizeW))){
		elevatormovement2 = true;
	}
	else
		elevatormovement2 = false;

	if (b1.buttonPress || b2.buttonPress){
		movingUp = true;
		movingDown = false;
	}
	else
	{
		movingUp = false;
		movingDown = true;

	}

	if (movingUp) {
		e1.elevatorY += velocityE;
		if (e1.elevatorY >= blockGap * 2) {
			e1.elevatorY = blockGap * 2; // limit
			movingUp = false;

		}
	}
	else if (movingDown){
		e1.elevatorY -= velocityE;
		if (e1.elevatorY <= blockGap) {
			e1.elevatorY = blockGap; // limit
			movingDown = false;
		}
	}

}






void pitCheck() {

	if ((sq_2.x + sqSizeW >= f1.pitX && sq_2.x <= f1.pitX + pitSize && sq_2.y == f1.pitY + blockWidth) || (sq_2.x + sqSizeW >= g1.pitX && sq_2.x <= g1.pitX + pitSize && sq_2.y == g1.pitY + blockWidth)) {
		sq_2.life = false;
	}

	if ((sq_1.x + sqSizeW >= w1.pitX && sq_1.x <= w1.pitX + pitSize && sq_1.y == w1.pitY + blockWidth) || (sq_1.x + sqSizeW >= g1.pitX && sq_1.x <= g1.pitX + pitSize && sq_1.y == g1.pitY + blockWidth) || (sq_1.x + sqSizeW >= g2.pitX && sq_1.x <= g2.pitX + pitSize && sq_1.y == g2.pitY + blockWidth)){
		sq_1.life = false;
	}



	if (sq_2.x + sqSizeW >= g2.pitX && sq_2.x <= g2.pitX + pitSize && sq_2.y == g2.pitY + blockWidth){
		sq_2.life = false;
	}
	if (sq_1.x + sqSizeW >= g2.pitX && sq_1.x <= g2.pitX + pitSize && sq_1.y == g2.pitY + blockWidth) {
		sq_1.life = false;
	}

}





void define_Elements() {

	EHdetermination = 1; //  To check if player wants to play easy or hard
	sq_1.x = 0;
	sq_1.y = blockWidth;
	sq_2.x = 60;
	sq_2.y = blockWidth;

	e1.elevatorX = 10;
	e1.elevatorY = blockGap * 1;


	if (level == 1){
		b1.buttonX = floorOpenGap + 300;
		b1.buttonY = blockGap + blockWidth;
		b2.buttonX = floorOpenGap + 300;
		b2.buttonY = blockGap * 2 + blockWidth;

	}

	else if (level == 3){
		b1.buttonX = floorOpenGap + 100;
		b1.buttonY = blockGap + blockWidth;
		b2.buttonX = floorOpenGap + 100;
		b2.buttonY = blockGap * 2 + blockWidth;
	}

	if (level == 1){
		f1.pitX = 400;
		f1.pitY = 0;
		w1.pitX = 800;
		w1.pitY = 0;
		g1.pitX = 700;
		g1.pitY = blockGap;
		g2.pitX = floorOpenGap + 600;
		g2.pitY = blockGap * 2;
	}

	else if (level == 3){
		f1.pitX = 400;
		f1.pitY = 0;
		w1.pitX = 800;
		w1.pitY = 0;
		g1.pitX = 400;
		g1.pitY = blockGap;
		g2.pitX = floorOpenGap + 250 + dx + 10;
		g2.pitY = blockGap * 3;
	}

	if (level == 3){
		door1.x = floorOpenGap + 250;
		door1.y = blockWidth + blockGap * 3;

		l1.leverX = floorOpenGap + 200;
		l1.leverY = blockWidth + blockGap * 2;
		l1.leverPress = false;
		movingUpD = false, movingDownD = false;
		platformRight = true;
		platformLeft = false;
		platfrom1.x = gapPos + 200;
		onPlatform1 = false;
		onPlatform2 = false;
	}

	sq_1.life = true;
	sq_2.life = true;
	b1.buttonPress = false;
	b2.buttonPress = false;
	for (int i = 0; i < 4; i++)
		d1[i].diamondContact = false;

	d1[0].diamondX = f1.pitX + 100 - 10;
	d1[0].diamondY = blockWidth + 25;

	d1[1].diamondX = g1.pitX + 100 - 10;
	d1[1].diamondY = blockGap + 70 + blockWidth;

	d1[2].diamondX = e1.elevatorX + 95;
	d1[2].diamondY = blockGap * 2 + 25 + blockWidth;
	d1[3].diamondX = w1.pitX + 100 - 10;
	d1[3].diamondY = blockWidth + 25;
	points = 0;
	dead = false;
	name = false;
	c = 0;
	numPlayer = 0;
	ifstream inputFile("Leaderboards.txt");
	while (inputFile >> p[numPlayer].name >> p[numPlayer].point) {
		numPlayer++;
		if (numPlayer >= maxPlayer) break;
	}
	inputFile.close();
	p[numPlayer].name[0] = '\0';
	p[numPlayer].point = 0;
	player1 = false;
	player2 = false;
	wdoory = 570;
	wdoorx = 150;
	fdoory = 570;
	fdoorx = 50;
	doory = 87;
	doorx = 80;


}
void checkdoor(){
	if (sq_1.x >= fdoorx && sq_1.x <= fdoorx + doorx && sq_1.y >= 570){
		player1 = true;

	}
	if (sq_2.x >= wdoorx && sq_2.x <= wdoorx + doorx &&  sq_2.y >= 570){
		player2 = true;

	}
}


void daddy_isettimer(){
	runright1();
	runleft1();
	shead1();
	runright2();
	runleft2();
	shead2();
	checkdoor();
}

int main() {
	if (music)
		PlaySound("Music\\NormalOST", NULL, SND_LOOP | SND_ASYNC);

	define_Elements();
	iSetTimer(20, moveSq1);
	iSetTimer(20, moveSq2);
	iSetTimer(20, moving_obsticles);
	iSetTimer(20, diamonds);
	iSetTimer(20, pitCheck);
	iSetTimer(50, daddy_isettimer);

	iInitialize(screenWidth, screenHeight, "Elementals : Heatblast & Hydrogirl");
	glutSpecialUpFunc(specialUp);
	glutKeyboardUpFunc(keyboardUp);
	iStart();
}

void button() {
	if ((sq_1.x + sqSizeW > b1.buttonX && sq_1.x < b1.buttonX + buttonSize && sq_1.y + sqSizeH > b1.buttonY && sq_1.y < b1.buttonY + buttonSize) || (sq_2.x + sqSizeW > b1.buttonX && sq_2.x < b1.buttonX + buttonSize && sq_2.y + sqSizeH > b1.buttonY && sq_2.y < b1.buttonY + buttonSize)) {
		b1.buttonPress = true;
	}
	else {
		b1.buttonPress = false;
	}
	if ((sq_1.x + sqSizeW > b2.buttonX && sq_1.x < b2.buttonX + buttonSize && sq_1.y + sqSizeH > b2.buttonY && sq_1.y < b2.buttonY + buttonSize) || (sq_2.x + sqSizeW > b2.buttonX && sq_2.x < b2.buttonX + buttonSize && sq_2.y + sqSizeH > b2.buttonY && sq_2.y < b2.buttonY + buttonSize)) {
		b2.buttonPress = true;
	}
	else {
		b2.buttonPress = false;
	}
}


void diamonds() {
	for (int i = 0; i < 4; i++) {
		if (!d1[i].diamondContact) {

			if (sq_1.x <= d1[i].diamondX + diamondsize && sq_1.x + sqSizeW >= d1[i].diamondX && sq_1.y <= d1[i].diamondY + diamondsize && sq_1.y + sqSizeH >= d1[i].diamondY) {
				d1[i].diamondContact = true;
				if (level == 1)
					p[numPlayer].point++;
				else
					p[numPlayer].point += 2;

			}
			if (sq_2.x <= d1[i].diamondX + diamondsize && sq_2.x + sqSizeW >= d1[i].diamondX && sq_2.y <= d1[i].diamondY + diamondsize && sq_2.y + sqSizeH >= d1[i].diamondY) {
				d1[i].diamondContact = true;
				if (level == 1)
					p[numPlayer].point++;
				else
					p[numPlayer].point += 2;
			}
		}
	}
}

int floorDetermination(int x, int y) {
	if (play == 1) {
		int floorLevel = 0;
		if (y >= blockWidth && y < blockGap + blockWidth) {
			floorLevel = 0;
		}
		else if (y >= blockWidth + blockGap && y < blockGap * 2 + blockWidth) {
			if (x < 1080 && x >= floorOpenGap - 20)
				floorLevel = 1;
			else
				floorLevel = 0;
		}
		else if ((y >= blockWidth + blockGap * 2 - 10) && y < blockGap * 3 + blockWidth) {
			if (x > 200 - sqSizeW)
				floorLevel = 2;
		}
		else if (y >= blockWidth + blockGap * 3 && y < blockGap * 4 + blockWidth) {
			if (x < 1080)
				floorLevel = 3;
			else
				floorLevel = 2;
		}

		if (level == 3 && floorLevel == 2){
			if ((x >= gapPos && x + sqSizeW <= platfrom1.x) || x >= platfrom1.x + 200){
				floorLevel--;
			}
		}
		return floorLevel;
	}

}

void Xboundary1(int *xa, int y){
	int x = *xa;
	if (x <= 0) {
		x = 0;
	}

	else if (x >= screenWidth - sqSizeW) {
		x = screenWidth - sqSizeW;
	}

	else if (y < blockWidth + blockGap && y > blockGap - sqSizeH){
		if (x <= 1080 && x >= 1000){
			x = 1080;
		}
	}

	else if (y < blockWidth + e1.elevatorY && y > e1.elevatorY - sqSizeH){
		if (x <= floorOpenGap - 20){
			x = floorOpenGap - 10;
		}
	}

	else if ((y < blockWidth + blockGap * 2) && (y > blockGap * 2 - sqSizeH)){
		if (x >= floorOpenGap - sqSizeW && x <= floorOpenGap){
			x = floorOpenGap - sqSizeW;
		}
	}

	else if ((y < blockWidth + blockGap * 3) && (y > blockGap * 3 - sqSizeH)){
		if (x <= 1080 && x >= 1000){
			x = 1080;
		}
	}
	*xa = x;
}


void Xboundary3(int &x, int y, bool moveJump){
	if (x <= 0) {
		x = 0;
	}
	if (x >= screenWidth - sqSizeW) {
		x = screenWidth - sqSizeW;
	}

	else if (y < blockWidth + blockGap && y > blockGap - sqSizeH){
		if (x <= 1080 && x >= 1000){
			x = 1080;
		}
	}

	else if (y < blockWidth + e1.elevatorY && y > e1.elevatorY - sqSizeH){
		if (x <= floorOpenGap - 20){
			x = floorOpenGap - 10;
		}
	}

	else if (y + sqSizeH > blockGap * 2 && y < blockGap * 2 + blockWidth){

		if (x <= gapPos && x >gapPos - 50){
			x = gapPos;
		}
		if (x + sqSizeW >= platfrom1.x && x + sqSizeW < platfrom1.x + 50){
			x = platfrom1.x - sqSizeW;
		}
		if (x <= platfrom1.x + 200 && x >platfrom1.x + 200 - 50){
			x = platfrom1.x + 200;
		}


	}
	else if ((y < blockWidth + blockGap * 2) && (y > blockGap * 2 - sqSizeH)){
		if (x >= floorOpenGap - sqSizeW && x <= floorOpenGap){
			x = floorOpenGap - sqSizeW;
		}
	}

	else if ((y < blockWidth + blockGap * 3) && (y > blockGap * 3 - sqSizeH)){
		if (x <= screenWidth - floorOpenGap && x >= screenWidth - floorOpenGap - 50){
			x = screenWidth - floorOpenGap;
		}
	}
	if (door1.y < y + sqSizeH){

		if (x + 50 < door1.x + dx + 5 && x + 50 >= door1.x)
		{
			x = door1.x - 50;
		}
		if (x <= door1.x + dx + 5 && x  > door1.x)
		{
			x = door1.x + dx + 5;
		}
	}
	if (!moveJump){ 

		if (!l1.over){

			if (l1.leverY + leverSize > y && l1.leverY <= y){

				if (x + sqSizeW >= l1.leverX && x + sqSizeW < l1.leverX + leverSize)
				{
					x = l1.leverX - sqSizeW;
				}


				if (x <= l1.leverX + leverSize && x  > l1.leverX)
				{
					x = l1.leverX + leverSize;
				}

			}
		}

		else if (l1.over){

			if (l1.leverY + leverSize - 10 > y && l1.leverY <= y){

				if (x + sqSizeW >= l1.leverX && x + sqSizeW < l1.leverX + leverSize)
				{
					x = l1.leverX - sqSizeW;
				}

				if (x <= l1.leverX + leverSize && x  > l1.leverX)
				{
					x = l1.leverX + leverSize;
				}

			}
		}
	}

}