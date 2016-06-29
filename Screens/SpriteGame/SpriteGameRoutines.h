#pragma once
#include "SDL.h"
#include <fstream> // input from a file
#include <string>
#include <vector>
#include "../../Game Setup/Helper.h"
#include "ship.h"
#include "../../Node.h"
using std::string;
using std::vector;

using namespace Helper;

class SpriteCharacterGame
{
public:
	SpriteCharacterGame();
	~SpriteCharacterGame();

	SpriteCharacterGame(bool a_bool);

	void GetKeys(ship a_ship);
	void SpawnNodes(int a_rows, int a_cols, int a_x, int a_y, int a_increment);
	vector<Node*>Waypoint;
	void ResetData();
	bool init();

protected:
	bool m_initialized;

};