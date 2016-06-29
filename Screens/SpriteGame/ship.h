#pragma once
#include "string.h"
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"
#include "..\..\Game Setup\Helper.h"
#include "..\..\Game Setup\sdlWindow.h"
#include "..\..\Game Setup\sdlResources.h"
#include "../../Game Setup/Helper.h"
#include "Header\utility.h"
#include <fstream>

using namespace Helper;

class ship
{
public:
	ship();
	ship(SDL_Texture* a_tex,float a_x, float a_y, float a_width, float a_height, int a_frameWidth, int a_frameHeight, int a_frameX, int a_frameY);
	~ship();
	enum Wepname
	{
		MG, Pulse, Lazer, Missile
	};
	struct Weapons
	{
		string name;
		int attack;
		SDL_Texture* Projectile;
		int ProjectileNo;
		float Velocity;
		int Firespeed;
		float X;
		float Y;
		int ammo;
	};

	void SetShip(float a_topspeed, int a_weapon, int a_ammo, float a_health, int a_attack);
	void Moveship(Vector3 a_Direction);
	void DrawShip(); 
	void UpdateShip(Matrix3 p_mat);
	void ShipPos(float a_x, float a_y);
	void KeyPress();

	void Saveship();
	bool LoadShip();

	int ReturnAngle();

	Matrix3 ShipMat;
	SDL_Texture* m_tex;
protected:
	string		 m_name;
	Matrix3		 Translation;
	Matrix3		 Rotation;
	Matrix3		 Scale;
	Matrix3		 LocalSpace = Scale * Rotation * Translation;
	Vector3		 m_Position;
	SDL_Rect	 Dest;
	bool		 m_save;
	float		 m_angle;
	float		 m_width;
	float		 m_height;
	float		 m_Fwidth;
	float		 m_Fheight;
	float		 m_x;
	float		 m_y;
	float		 m_TopSpeed;
	float		 m_Decellerate;
	float		 m_health;
	float		 m_attack;
	Weapons		 m_weapon;
	int			 m_framewidth;
	int			 m_frameheight;
	int			 m_FrameX;
	int			 m_FrameY;
	float		 m_delay;
};

class ChildShip : public ship
{
public:
	ChildShip(SDL_Texture* a_tex, float a_x, float a_y, float a_width, float a_height, int a_frameWidth, int a_frameHeight, int a_frameX, int a_frameY,Matrix3* a_mat);

	void UpdateShip(Matrix3 p_world, Matrix3 p_parent);

private:
	Matrix3 *m_Pmat;
};