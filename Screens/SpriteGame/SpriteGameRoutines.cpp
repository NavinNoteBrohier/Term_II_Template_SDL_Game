#include "SpriteGameRoutines.h"



SpriteCharacterGame::SpriteCharacterGame()
{

}

SpriteCharacterGame::~SpriteCharacterGame()
{

}

SpriteCharacterGame::SpriteCharacterGame(bool a_bool)
{
	a_bool = false;
}

void SpriteCharacterGame::GetKeys(ship a_ship)
{
	Vector3 A(1,	 0,		 0);
	Vector3 B(0,	-1,		 0);
	Vector3 C(0,	 0,		 1);
	Vector3 D(0,	 0,		-1);
	
	if(HELP_Keypresses(SDL_SCANCODE_W)) a_ship.Moveship(A);
	if(HELP_Keypresses(SDL_SCANCODE_S)) a_ship.Moveship(B);
	if(HELP_Keypresses(SDL_SCANCODE_A))	a_ship.Moveship(C);
	if(HELP_Keypresses(SDL_SCANCODE_D))	a_ship.Moveship(D);
	
	if(HELP_Keypresses(SDL_SCANCODE_SPACE));
	
	if(HELP_Keypresses(SDL_SCANCODE_ESCAPE));
}

void SpriteCharacterGame::SpawnNodes(int a_rows, int a_cols, int a_x, int a_y, int a_increment)
{
	enum NodeType
	{
		STARTROOM = 1,ENDROOM = 1,EMPTYROOM,ASTEROIDROOM,ENEMYROOM
	};
	int k = 0;
	int layout[255][255];

	for (int i = 0; i < 255; i++)
	{
		for (int j = 0; j < 255; j++)
		{
			layout[i][j] = 0;
		}
	}

	for (int i = 0; i < a_rows; i++)
	{
		for (int j = 0; j < a_cols; j++)
		{
			layout[i][j] = HELP_Random(EMPTYROOM, ENEMYROOM);
			Waypoint.push_back(new Node(a_x + a_increment*j, a_y + a_increment * i, layout[i][j]));
			if		(layout[i][j] == EMPTYROOM)		{ Waypoint[k]->ChangeSprite(TM_NODEEMPTY); }
			else if (layout[i][j] == ASTEROIDROOM)	{ Waypoint[k]->ChangeSprite(TM_NODEASTEROID); }
			else if (layout[i][j] == ENEMYROOM)		{ Waypoint[k]->ChangeSprite(TM_NODEENEMY); };
			k++;
		}
	}

	layout[0][0] = STARTROOM;
	Waypoint[0]->ChangeSprite(TM_NODE);
	layout[a_rows][a_cols] = ENDROOM;
	Waypoint[k-1]->ChangeSprite(TM_NODEEND);
}



void SpriteCharacterGame::ResetData()
{

}

bool SpriteCharacterGame::init()
{
	return true;
}
