#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"
#include <iostream>
#include <fstream>
#include "SpriteGameScreen.h"
#include "SpriteGameRoutines.h"
#include "ship.h"
#include "..\screenManager.h"
#include "..\MainMenu\menuscreen.h"
#include "..\..\Game Setup\main.h"
#include "..\..\Game Setup\helper.h"
#include "..\..\Game Setup\sdlWindow.h"
#include "..\..\Game Setup\sdlResources.h"
#include "ship.h"
#include <math.h>


//////////////////////////////////////////////////////////////////////////
//																		///
//	Navin Brohier														////
//	navin.brohier@gmail.com || navinnotebrohier.github.io				////
//																		///
//////////////////////////////////////////////////////////////////////////



SpriteCharacterGame Game;
// this is the name at the top of the screen
static string SpriteName = "Sprite Game";
SpriteCharacterGame game(true);
using namespace Helper;
Matrix3 WorldView(1, 0, 0, 0, 1, 0, 1680 / 2, 1050 / 2, 1);

ship Player(TM_SHIP, 200, 200, 88, 77, 88, 77, 0, 0);
ChildShip Orbitor(TM_SPRITECHARACTER,50, 50, 16, 16, 16, 16, 0, 0,&Player.ShipMat);
char tempStr[256];

enum BUTTON_ID {
	B_NULL,
	B_ONE, B_BACK, B_QUIT
};

static ButtonData l_gameData[] = {
	{ ENTER_BUTTON, B_QUIT, WB_MAIN_TOP_INFO, 969, 20, 42, 42, 143, 1 },
	{ ENTER_BUTTON, B_BACK, WB_MAIN_TOP_INFO, 20, 60, 36, 36, 57, 1 },
	{ ENTER_END, },
};

static BUTTON_STATE checkButtons(BUTTON_ID p_buttonId)
{
	switch (p_buttonId) {
	case B_QUIT:
		return B_NORMAL;
	}
	return B_IGNORE;
}


void CalculateShiptoMouse(float x, float y, float &angle)
{
	int imX, imY;
	SDL_GetMouseState(&imX, &imY);

	float ix = (float)imX;
	float iy = (float)imY;

	if (imX - x)
	{
		angle = (float)atan((float)(iy - y) / float(ix - x));
		angle = angle * 180 / 3.14159f;
	}
	else
	{
		angle = imY > y ? 90.0f : 270.0f;
	}
	angle += 90;
	if (ix - x < 0)
	{
		angle += 180;
	}
}

//! drawScreen - standard draw screen routine
static void drawScreen()
{
	SDL_Rect winSize = Window::Box();
	Window::Clear();

	Player.m_tex = TM_SHIP;
	Orbitor.m_tex = TM_SPRITECHARACTER;



#pragma region //Scene
	SDL_Rect s1 = { 0, 0,1680, 1050 };
	SDL_Rect d1 = { 0, 0, s1.w, s1.h };
	Window::Draw(TM_SPRITEPAPER, d1, &s1);

	//HELP_DrawSprite(TM_SHIP, 0, 0, 88, 77,50,50, 88, 77, 0, ShipAngle );
#pragma endregion

	for (int i = 0; i < Game.Waypoint.size(); i++)
	{
		Game.Waypoint[i]->updatenode();
	}

	Player.UpdateShip(WorldView);
	Orbitor.UpdateShip(WorldView, Player.ShipMat);
	static bool Debugging = false;
#pragma region //Debug 
	if (HELP_Keypresses(SDL_SCANCODE_HOME)) { Debugging = true; };
	if(Debugging == true)
	{
		if (HELP_Keypresses(SDL_SCANCODE_INSERT)) { Debugging = false; }
		sprintf_s(tempStr, "Ship Angle = %d", Player.ReturnAngle());
		Window::printString(10 + 4, 20, tempStr, cBlue, 15);

		sprintf_s(tempStr, "Q = %d", HELP_Keypresses(SDL_SCANCODE_Q));
		Window::printString(10 + 4, 80, tempStr, cBlue, 15);

		sprintf_s(tempStr, "E = %d", HELP_Keypresses(SDL_SCANCODE_E));
		Window::printString(10 + 4, 100, tempStr, cBlue, 15);

		sprintf_s(tempStr, "W = %d", HELP_Keypresses(SDL_SCANCODE_W));
		Window::printString(10 + 4, 120, tempStr, cBlue, 15);

		sprintf_s(tempStr, "S = %d", HELP_Keypresses(SDL_SCANCODE_S));
		Window::printString(10 + 4, 140, tempStr, cBlue, 15);

		sprintf_s(tempStr, "A = %d", HELP_Keypresses(SDL_SCANCODE_A));
		Window::printString(10 + 4, 160, tempStr, cBlue, 15);

		sprintf_s(tempStr, "D = %d", HELP_Keypresses(SDL_SCANCODE_D));
		Window::printString(10 + 4, 180, tempStr, cBlue, 15);

		sprintf_s(tempStr, "Z = %d", HELP_Keypresses(SDL_SCANCODE_Z));
		Window::printString(10 + 4, 200, tempStr, cBlue, 15);

		sprintf_s(tempStr, "X = %d", HELP_Keypresses(SDL_SCANCODE_X));
		Window::printString(10 + 4, 220, tempStr, cBlue, 15);

		sprintf_s(tempStr, "C = %d", HELP_Keypresses(SDL_SCANCODE_C));
		Window::printString(10 + 4, 240, tempStr, cBlue, 15);

		sprintf_s(tempStr, "V = %d", HELP_Keypresses(SDL_SCANCODE_V));
		Window::printString(10 + 4, 260, tempStr, cBlue, 15);

		sprintf_s(tempStr, "1 = %d", HELP_Keypresses(SDL_SCANCODE_1));
		Window::printString(10 + 4, 280, tempStr, cBlue, 15);

		sprintf_s(tempStr, "0 = %d", HELP_Keypresses(SDL_SCANCODE_0));
		Window::printString(10 + 4, 300, tempStr, cBlue, 15);

		HELP_DrawSprite(TM_NODE, 0, 0, 50, 50, 50, 600, 50, 50, 0, 0);
		sprintf_s(tempStr, "1");
		Window::printString(10 + 4, 600, tempStr, cBlue, 15);

		HELP_DrawSprite(TM_NODEEND, 0, 0, 50, 50, 50, 670, 50, 50, 0, 0);
		sprintf_s(tempStr, "1");
		Window::printString(10 + 4, 670, tempStr, cBlue, 15);

		HELP_DrawSprite(TM_NODEEMPTY, 0, 0, 50, 50, 50, 740, 50, 50, 0, 0);
		sprintf_s(tempStr, "2");
		Window::printString(10 + 4, 740, tempStr, cBlue, 15);

		HELP_DrawSprite(TM_NODEASTEROID, 0, 0, 50, 50, 50, 810, 50, 50, 0, 0);
		sprintf_s(tempStr, "3");
		Window::printString(10 + 4, 810, tempStr, cBlue, 15);

		HELP_DrawSprite(TM_NODEENEMY, 0, 0, 50, 50, 50, 880, 50, 50, 0, 0);
		sprintf_s(tempStr, "4");
		Window::printString(10 + 4, 880, tempStr, cBlue, 15);
	}
#pragma endregion





	// and update the current window rectangle

	Window::Present();
}

void OpenSpriteGame()
{
	if (!game.init())
	{
		cout << "Error: Game init() failed." << endl;
		return;
	}

	Game.SpawnNodes(5, 5, 100, 100, 100);

	gSM.mBData = l_gameData;
	gSM.p_drawScreen = drawScreen;
	gSM.mTexture = TM_SPRITEPAPER;
	gSM.mTexture = TM_HANG_BUTTONS;
}  
