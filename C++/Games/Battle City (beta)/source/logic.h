#pragma once
#ifndef LOGIC_H
#define LOGIC_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <windows.h>
#include <iostream>
#include <cstdlib>
#include <sstream>
#include <fstream>
#include <ctime>
#include <cmath>
using namespace sf;
const int ScreenWidth = 800;
const int ScreenHeight = 600;
const int ScreenWidthFrame = 25;
const int ScreenHeightFrame = 25;
const int NumOfTanks = 3;
const int cTankHP = 200;
const int Player[NumOfTanks] = { 0,1,2 };
const int SquareTriangle = 50;
const int SleepTime = 5;
const double Damage = 25;
const double CBulletSpeed = 30 / SleepTime;
const int CReloadingTime = 1000 / SleepTime;
const int BattleFieldWidth = ScreenWidth / SquareTriangle;
const int BattleFieldHeight = ScreenHeight / SquareTriangle;
const int CTankSpeed = 1;
const int TankTextFrame = 5;
const int cWall = 1;
const int cTree = 2;
const int cWater = 3;
const int cGround = 4;
const int cWallHP = 50;
const int Level1[BattleFieldHeight * BattleFieldWidth] = {
			4,    4,  4,  4,  4,  4,  4,  4,  1,  222,4,  4,  4,  4,  4,  4,
			4,    4,  4,  4,  4,  4,  4,  4,  1,  1,  4,  4,  1,  1,  4,  4,
			4,    4,  4,  2,  2,  2,  2,  2,  2,  2,  4,  4,  1,  1,  1,  4,
			4,    4,  2,  3,  3,  3,  3,  3,  3,  3,  2,  4,  4,  4,  4,  4,
			4,    4,  3,  3,  3,  3,  2,  2,  3,  3,  2,  2,  4,  4,  4,  4,
			4,    4,  3,  2,  2,  2,  3,  3,  3,  3,  3,  3,  2,  4,  4,  4,
			4,    4,  2,  4,  2,  2,  2,  2,  3,  3,  3,  3,  3,  2,  1,  1,
			4,    4,  4,  4,  4,  4,  4,  2,  2,  2,  3,  3,  3,  3,  1,  1,
			4,    4,  4,  4,  4,  4,  4,  4,  2,  2,  2,  3,  3,  2,  4,  4,
			4,    1,  1,  1,  4,  4,  4,  4,  4,  2,  2,  2,  2,  4,  4,  4,
			4,    4,  1,  1,  4,  4,  4,  4,  1,  1,  4,  4,  4,  4,  4,  4,
			4,    4,  4,  4,  4,  4,  4,  4,  111,1,  4,  4,  4,  4,  4,  4 };
/*
const int Level1[BattleFieldHeight*BattleFieldWidth]={
			4,    4,  4,  222,4,  4,  4,  4,  1,  4,  4,  4,  4,  4,  4,  4,
			4,    4,  4,  4,  4,  4,  4,  4,  1,  1,  4,  4,  1,  1,  4,  4,
			4,    4,  4,  2,  2,  2,  2,  2,  2,  2,  4,  4,  1,  1,  1,  4,
			4,    4,  2,  3,  3,  3,  3,  3,  3,  3,  2,  4,  4,  4,  4,  4,
			4,    4,  3,  3,  3,  3,  2,  2,  3,  3,  2,  2,  4,  4,  4,  4,
			1,    1,  3,  2,  2,  2,  3,  3,  3,  3,  3,  3,  2,  4,  4,  4,
			1,    1,  2,  4,  2,  2,  2,  2,  3,  3,  3,  3,  3,  2,  1,  1,
			4,    4,  4,  4,  4,  4,  4,  2,  2,  2,  3,  3,  3,  3,  1,  1,
			4,    4,  4,  4,  4,  4,  4,  4,  2,  2,  2,  3,  3,  2,  4,  4,
			4,    1,  1,  1,  4,  4,  4,  4,  4,  2,  2,  2,  2,  4,  4,  4,
			4,    4,  1,  1,  4,  4,  4,  4,  1,  1,  4,  4,  4,  4,  4,  4,
			4,    4,  4,  4,  4,  4,  4,  4,  111,1,  4,  4,  4,  4,  4,  4      };
*/
enum VALUES
{
	SCREENWIDTH = 0,					//0
	SCREENHEIGHT,						//1
	NUMOFTANKS,							//2
	PLAYERNUMBER,						//3
	SQUARETRIANGLE,						//4
	SLEEPTIME,							//5
	TANK_NUMOFTEXTURE,					//6
	TANK_HP,							//7
	TANK_ISREADYTOSHOOT,				//8
	TANK_NUMOFTANK,						//9
	TANK_POSX,							//10
	TANK_POSY,							//11
	TANK_RELOADINGTIME,					//12
	TANK_ISUP,							//13
	TANK_ISDOWN,						//14
	TANK_ISLEFT,						//15
	TANK_ISRIGHT,						//16
	BULLET_BULLETSPEED,					//17
	BULLET_DAMAGE,						//18
	BULLET_ISCRITICAL,					//19
	BULLET_ISINAIR,						//20
	BULLET_NUMOFTANK,					//21
	BULLET_POSX,						//22
	BULLET_POSY,						//23
	BULLET_VECTOR,						//24
	BULLET_NUMOFBULLETTEXTURE,          //25
	TANK_ISDEAD,						//26
	TANK_NUMOFDEATHTEXTURE,				//27
};
///////////////////////
//BattleField Array specifications:
//0 - nothing
//1 - wall
//2 - tree
//3 - water
//4 - ground
//NNN - Player, where N-NumOfPlayer
///////////////////////
class Logic
{
private:
	int NumOfTexture;
	int NumOfTank;
	int BulletSpeed;
	int ReloadingTime;
	int BattleField[BattleFieldHeight][BattleFieldWidth];
	bool isReadyToShoot;
	bool isCritical;
	///////////////////////////////		
	struct Tanks
	{
		int NumOfTank; int NumOfTexture; int TankSpeed; int posX; int posY; int HP; int ReloadingTime; int dX; int dY; int NumOfDeathTexture;
		bool isReadyToShoot; bool isUp; bool isDown; bool isLeft; bool isRight; bool isShoot; bool isDead;
	};
	//////////////////////////////		
	struct Bullet
	{
		int NumOfTank; bool isInAir; int Vector; double BulletSpeed; int posX; int posY; double Damage; bool isCritical; int NumOfBulletTexture;
	};
	//////////////////////////////
	struct BattleFieldObject
	{
		int TypeOfObject; int NumOfObject; int posX; int posY; int HP; int NumOfTexture; bool isBulletsThrough; bool isSlowDownBullets; bool isSlowedDown;
	};
	//////////////////////////////
	Tanks Tank[NumOfTanks];
	Bullet Bullet[NumOfTanks];
	BattleFieldObject Object[BattleFieldHeight][BattleFieldWidth];
public:
	int GetValues(int NumOfTank, int NumOfValues);
	int Randomiser(int upper_limit, int down_limit);
	int TankTextureChanger(int NumOfTank, int NumOfTexture);
	void DefaultTankCharacters(int NumOfTank);
	int TankVerticalDriving(int NumOfTank, int NumOfTexture);
	int TankHorisontalDriving(int NumOfTank, int NumOfTexture);
	int BulletTexture(int NumOfTank);
	void Shooting(int NumOfTank);
	int BulletReady(int NumOfTank);
	void PlayerControl(int NumOfTank, bool isUp, bool isDown, bool isLeft, bool isRight, bool isShoot);
	void Debugger(int NumOfTank);
	void Hit(int NumOfTank);
	int Death(int NumOfTank);
	void ObjectInitialiser();
	void Interaction(int NumOfTank);
	int ArrayWorker(int NumOfTank);
	int GetMap(int i, int j, int NumOfValue);
};
#endif