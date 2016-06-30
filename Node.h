#pragma once
#include <iostream>
#include "string.h"
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"
#include "Game Setup\sdlWindow.h"
#include "Game Setup\sdlResources.h"
#include "Game Setup\Helper.h"
#include "Header\utility.h"


using namespace Helper;

class Node
{
public:
	Node(float a_x, float a_y, int a_cost)
	{
		m_x = a_x;
		m_y = a_y;
		m_cost = a_cost;
	}
	void updatenode()
	{
		HELP_DrawSprite(m_sprite,0,0,50,50,m_x,m_y,50,50,0,0);
	};

	void ChangeSprite(SDL_Texture * a_sprite)
	{
		m_sprite = a_sprite;
	}
	float m_x;
	float m_y;
	int m_cost;
private:
	SDL_Texture* m_sprite;
};