#include "logic.h"
using namespace sf;
/////////////
void Logic::PlayerControl(int NumOfTank, bool isUp, bool isDown, bool isLeft, bool isRight, bool isShoot)
{
	Tank[NumOfTank].isUp = isUp;
	Tank[NumOfTank].isDown = isDown;
	Tank[NumOfTank].isLeft = isLeft;
	Tank[NumOfTank].isRight = isRight;
	Tank[NumOfTank].isShoot = isShoot;
}
/////////////
int Logic::GetValues(int NumOfTank, int NumOfValue)
{
	switch (NumOfValue)
	{
	case 0:  return ScreenWidth;
	case 1:  return ScreenHeight;
	case 2:  return NumOfTanks;
	case 3:  return Player[NumOfTanks];
	case 4:  return SquareTriangle;
	case 5:  return SleepTime;
	case 6:  return Tank[NumOfTank].NumOfTexture;
	case 7:  return Tank[NumOfTank].HP;
	case 8:  return Tank[NumOfTank].isReadyToShoot;
	case 9:  return Tank[NumOfTank].NumOfTank;
	case 10:  return Tank[NumOfTank].posX;
	case 11:  return Tank[NumOfTank].posY;
	case 12:  return Tank[NumOfTank].ReloadingTime;
	case 13:  return Tank[NumOfTank].isUp;
	case 14:  return Tank[NumOfTank].isDown;
	case 15:  return Tank[NumOfTank].isLeft;
	case 16:  return Tank[NumOfTank].isRight;
	case 17:  return Bullet[NumOfTank].BulletSpeed;
	case 18:  return Bullet[NumOfTank].Damage;
	case 19:  return Bullet[NumOfTank].isCritical;
	case 20:  return Bullet[NumOfTank].isInAir;
	case 21:  return Bullet[NumOfTank].NumOfTank;
	case 22:  return Bullet[NumOfTank].posX;
	case 23:  return Bullet[NumOfTank].posY;
	case 24:  return Bullet[NumOfTank].Vector;
	case 25:  return Bullet[NumOfTank].NumOfBulletTexture;
	case 26:  return Tank[NumOfTank].isDead;
	case 27:  return Tank[NumOfTank].NumOfDeathTexture;
	default:  return 0;
	}
}
/////////////
int Logic::Randomiser(int upper_limit, int down_limit)
{
	return int(rand() % upper_limit) + down_limit;
}
/////////////
int Logic::TankTextureChanger(int NumOfTank, int NumOfTexture)
{
	if (Tank[NumOfTank].isUp + Tank[NumOfTank].isDown + Tank[NumOfTank].isLeft + Tank[NumOfTank].isRight != 1)
		return Tank[NumOfTank].NumOfTexture;
	if (Tank[NumOfTank].isUp and !Tank[NumOfTank].isDown)
	{
		Tank[NumOfTank].NumOfTexture++;
		if (Tank[NumOfTank].NumOfTexture < 0 or Tank[NumOfTank].NumOfTexture >= 3)
			Tank[NumOfTank].NumOfTexture = 0;
	}
	if (!Tank[NumOfTank].isUp and Tank[NumOfTank].isDown)
	{
		Tank[NumOfTank].NumOfTexture++;
		if (Tank[NumOfTank].NumOfTexture < 3 or Tank[NumOfTank].NumOfTexture >= 6)
			Tank[NumOfTank].NumOfTexture = 3;
	}
	if (Tank[NumOfTank].isLeft and !Tank[NumOfTank].isRight)
	{
		Tank[NumOfTank].NumOfTexture++;
		if (Tank[NumOfTank].NumOfTexture < 6 or Tank[NumOfTank].NumOfTexture >= 9)
			Tank[NumOfTank].NumOfTexture = 6;
	}
	if (!Tank[NumOfTank].isLeft and Tank[NumOfTank].isRight)
	{
		Tank[NumOfTank].NumOfTexture++;
		if (Tank[NumOfTank].NumOfTexture < 9 or Tank[NumOfTank].NumOfTexture >= 12)
			Tank[NumOfTank].NumOfTexture = 9;
	}
	return Tank[NumOfTank].NumOfTexture;
}
/////////////
void Logic::DefaultTankCharacters(int NumOfTank)
{
	Tank[NumOfTank].HP = cTankHP;
	Tank[NumOfTank].isReadyToShoot = false;
	Tank[NumOfTank].ReloadingTime = CReloadingTime;
	Tank[NumOfTank].TankSpeed = CTankSpeed;
	Tank[NumOfTank].NumOfTexture = 0;
	Tank[NumOfTank].isUp = false;
	Tank[NumOfTank].isDown = false;
	Tank[NumOfTank].isLeft = false;
	Tank[NumOfTank].isRight = false;
	Tank[NumOfTank].isShoot = false;
	Tank[NumOfTank].dY = round(ScreenHeight / SquareTriangle);
	Tank[NumOfTank].dX = round(ScreenWidth / SquareTriangle);
	Tank[NumOfTank].isDead = false;
	Tank[NumOfTank].NumOfDeathTexture = 0;
	Bullet[NumOfTank].BulletSpeed = CBulletSpeed;
	Bullet[NumOfTank].NumOfTank = NumOfTank;
	Bullet[NumOfTank].isInAir = false;
	Bullet[NumOfTank].posX = Tank[NumOfTank].posX + SquareTriangle / 2 - TankTextFrame;
	Bullet[NumOfTank].posY = Tank[NumOfTank].posY + SquareTriangle / 2 - TankTextFrame;
	Bullet[NumOfTank].Damage = Damage;
	Bullet[NumOfTank].isCritical = Randomiser(2, 0);
	Bullet[NumOfTank].Vector = 1;
	Bullet[NumOfTank].NumOfBulletTexture = 0;
}
/////////////
int Logic::TankVerticalDriving(int NumOfTank, int NumOfTexture)
{
	if ((Tank[NumOfTank].isLeft or Tank[NumOfTank].isRight) or (Tank[NumOfTank].posY <= (0 + ScreenHeightFrame + TankTextFrame) and Tank[NumOfTank].isUp)
		or (Tank[NumOfTank].posY >= (ScreenHeight - SquareTriangle + ScreenHeightFrame + TankTextFrame) and Tank[NumOfTank].isDown))
		return Tank[NumOfTank].posY;
	for (int i = 1; i < NumOfTanks; i++)
	{
		if (i == NumOfTank)
			continue;
		if ((Tank[NumOfTank].posY - Tank[i].posY >= (0 + TankTextFrame) and Tank[NumOfTank].posY - Tank[i].posY <= (SquareTriangle - TankTextFrame)) and abs(Tank[NumOfTank].posX - Tank[i].posX) < (SquareTriangle - TankTextFrame) and Tank[NumOfTank].isUp)
			return Tank[NumOfTank].posY;
		if ((Tank[NumOfTank].posY - Tank[i].posY >= -(SquareTriangle - TankTextFrame) and Tank[NumOfTank].posY - Tank[i].posY <= (0 + TankTextFrame)) and abs(Tank[NumOfTank].posX - Tank[i].posX) < (SquareTriangle - TankTextFrame) and Tank[NumOfTank].isDown)
			return Tank[NumOfTank].posY;
	}
	if (Tank[NumOfTank].isUp) { Tank[NumOfTank].posY -= Tank[NumOfTank].TankSpeed; TankTextureChanger(NumOfTank, NumOfTexture); }
	if (Tank[NumOfTank].isDown) { Tank[NumOfTank].posY += Tank[NumOfTank].TankSpeed; TankTextureChanger(NumOfTank, NumOfTexture); }
	return Tank[NumOfTank].posY;
}
/////////////
int Logic::TankHorisontalDriving(int NumOfTank, int NumOfTexture)
{
	if ((Tank[NumOfTank].isUp or Tank[NumOfTank].isDown) or (Tank[NumOfTank].posX <= (0 + ScreenWidthFrame + TankTextFrame) and Tank[NumOfTank].isLeft)
		or (Tank[NumOfTank].posX >= (ScreenWidth - SquareTriangle + ScreenWidthFrame + TankTextFrame) and Tank[NumOfTank].isRight))
		return Tank[NumOfTank].posX;
	for (int i = 1; i < NumOfTanks; i++)
	{
		if (i == NumOfTank)
			continue;
		if ((Tank[NumOfTank].posX - Tank[i].posX >= (0 + TankTextFrame) and Tank[NumOfTank].posX - Tank[i].posX <= (SquareTriangle - TankTextFrame)) and abs(Tank[NumOfTank].posY - Tank[i].posY) < (SquareTriangle - TankTextFrame) and Tank[NumOfTank].isLeft)
			return Tank[NumOfTank].posX;
		if ((Tank[NumOfTank].posX - Tank[i].posX >= -(SquareTriangle - TankTextFrame) and Tank[NumOfTank].posX - Tank[i].posX <= (0 - TankTextFrame)) and abs(Tank[NumOfTank].posY - Tank[i].posY) < (SquareTriangle - TankTextFrame) and Tank[NumOfTank].isRight)
			return Tank[NumOfTank].posX;
	}
	if (Tank[NumOfTank].isLeft) { Tank[NumOfTank].posX -= Tank[NumOfTank].TankSpeed; TankTextureChanger(NumOfTank, NumOfTexture); }
	if (Tank[NumOfTank].isRight) { Tank[NumOfTank].posX += Tank[NumOfTank].TankSpeed; TankTextureChanger(NumOfTank, NumOfTexture); }
	return Tank[NumOfTank].posX;
}
/////////////
int Logic::BulletTexture(int NumOfTank)
{
	if (Bullet[NumOfTank].Vector == 1 and Tank[NumOfTank].isUp and !Tank[NumOfTank].isDown and !Tank[NumOfTank].isLeft and !Tank[NumOfTank].isRight)
		Bullet[NumOfTank].NumOfBulletTexture = 0;
	else if (Bullet[NumOfTank].Vector == 2 and !Tank[NumOfTank].isUp and Tank[NumOfTank].isDown and !Tank[NumOfTank].isLeft and !Tank[NumOfTank].isRight)
		Bullet[NumOfTank].NumOfBulletTexture = 1;
	else if (Bullet[NumOfTank].Vector == 3 and !Tank[NumOfTank].isUp and !Tank[NumOfTank].isDown and Tank[NumOfTank].isLeft and !Tank[NumOfTank].isRight)
		Bullet[NumOfTank].NumOfBulletTexture = 2;
	else if (Bullet[NumOfTank].Vector == 4 and !Tank[NumOfTank].isUp and !Tank[NumOfTank].isDown and !Tank[NumOfTank].isLeft and Tank[NumOfTank].isRight)
		Bullet[NumOfTank].NumOfBulletTexture = 3;
	else Bullet[NumOfTank].NumOfBulletTexture = 0;
	return Bullet[NumOfTank].NumOfBulletTexture;
}
/////////////
void Logic::Hit(int NumOfTank)
{
	for (int i = 0; i < NumOfTanks; i++)
	{
		if (i == NumOfTank)
			continue;
		if (abs(Bullet[NumOfTank].posX - (Tank[i].posX + SquareTriangle / 2 - TankTextFrame / 2)) <= (SquareTriangle / 2 - TankTextFrame) and abs(Bullet[NumOfTank].posY - (Tank[i].posY + SquareTriangle / 2 - TankTextFrame / 2)) <= SquareTriangle / 2 - TankTextFrame)
		{
			Tank[i].HP -= (Bullet[NumOfTank].Damage + Bullet[NumOfTank].Damage * Bullet[NumOfTank].isCritical);
			Bullet[NumOfTank].isInAir = false;
			if (Tank[i].HP <= 0)
				Tank[i].isDead = true;
		}
	}
}
////////////
void Logic::Shooting(int NumOfTank)
{
	if (Bullet[NumOfTank].Vector == 1) { Bullet[NumOfTank].posY -= Bullet[NumOfTank].BulletSpeed; }
	if (Bullet[NumOfTank].Vector == 2) { Bullet[NumOfTank].posY += Bullet[NumOfTank].BulletSpeed; }
	if (Bullet[NumOfTank].Vector == 3) { Bullet[NumOfTank].posX -= Bullet[NumOfTank].BulletSpeed; }
	if (Bullet[NumOfTank].Vector == 4) { Bullet[NumOfTank].posX += Bullet[NumOfTank].BulletSpeed; }
	if (Bullet[NumOfTank].posX >= 0 and Bullet[NumOfTank].posX <= (ScreenWidth + 2 * ScreenWidthFrame) and Bullet[NumOfTank].posY >= 0 and Bullet[NumOfTank].posY <= (ScreenHeight + 2 * ScreenHeightFrame))
		Bullet[NumOfTank].isInAir = true;
	else
	{
		Bullet[NumOfTank].isInAir = false;
	}
	if (Tank[NumOfTank].ReloadingTime <= 0 and Bullet[NumOfTank].isInAir == true)
		Tank[NumOfTank].ReloadingTime = CReloadingTime;
}
////////////
int Logic::BulletReady(int NumOfTank)
{
	if (Bullet[NumOfTank].isInAir == false)
	{
		Bullet[NumOfTank].posX = Tank[NumOfTank].posX + SquareTriangle / 2 - 1.5 * TankTextFrame;
		Bullet[NumOfTank].posY = Tank[NumOfTank].posY + SquareTriangle / 2 - 1.5 * TankTextFrame;
		Tank[NumOfTank].isReadyToShoot = false;
	}
	if (Tank[NumOfTank].ReloadingTime > 0 and !Tank[NumOfTank].isReadyToShoot)
	{
		Tank[NumOfTank].ReloadingTime--;
		Tank[NumOfTank].isReadyToShoot = false;
	}
	else
		Tank[NumOfTank].isReadyToShoot = true;
	if (Tank[NumOfTank].NumOfTexture >= 9 and Tank[NumOfTank].NumOfTexture <= 12 and !Bullet[NumOfTank].isInAir)       Bullet[NumOfTank].Vector = 4;
	if (Tank[NumOfTank].NumOfTexture >= 6 and Tank[NumOfTank].NumOfTexture <= 8 and !Bullet[NumOfTank].isInAir)	      Bullet[NumOfTank].Vector = 3;
	if (Tank[NumOfTank].NumOfTexture >= 3 and Tank[NumOfTank].NumOfTexture <= 5 and !Bullet[NumOfTank].isInAir)        Bullet[NumOfTank].Vector = 2;
	if (Tank[NumOfTank].NumOfTexture >= 0 and Tank[NumOfTank].NumOfTexture <= 2 and !Bullet[NumOfTank].isInAir)        Bullet[NumOfTank].Vector = 1;
	if ((Tank[NumOfTank].isReadyToShoot and Tank[NumOfTank].isShoot) or Bullet[NumOfTank].isInAir)
	{
		Bullet[NumOfTank].isCritical = Randomiser(2, 0);
		Shooting(NumOfTank);
		Hit(NumOfTank);
	}
	return Bullet[NumOfTank].Vector - 1;
}
////////////
int Logic::Death(int NumOfTank)
{
	Tank[NumOfTank].NumOfDeathTexture++;
	if (Tank[NumOfTank].NumOfDeathTexture >= 8)
		Tank[NumOfTank].NumOfDeathTexture = 5;
	return Tank[NumOfTank].NumOfDeathTexture;
}
////////////
void Logic::Debugger(int NumOfTank)
{
	system("cls");
	std::cout << Bullet[NumOfTank].Vector << "=Vector X=" << Bullet[NumOfTank].posX << " Y=" << Bullet[NumOfTank].posY << " HP=" << Tank[NumOfTank].HP << " TimeToReload:" << Tank[NumOfTank].ReloadingTime << std::endl;
	std::cout << "X=" << Tank[NumOfTank].dX << "Y=" << Tank[NumOfTank].dY << std::endl;
	std::cout << std::endl;
}
///////////
void Logic::ObjectInitialiser()
{
	for (int i = 0; i < BattleFieldHeight; i++)
	{
		for (int j = 0; j < BattleFieldWidth; j++)
		{
			BattleField[i][j] = Level1[i * (BattleFieldWidth)+j];
			if (BattleField[i][j] == 111)
			{
				Tank[Player[1]].posY = SquareTriangle * i + ScreenHeightFrame + TankTextFrame;
				Tank[Player[1]].posX = SquareTriangle * j + ScreenWidthFrame + TankTextFrame;
				continue;
			}
			if (BattleField[i][j] == 222)
			{
				Tank[Player[2]].posY = SquareTriangle * i + ScreenWidthFrame + TankTextFrame;
				Tank[Player[2]].posX = SquareTriangle * j + ScreenHeightFrame + TankTextFrame;
				continue;
			}
			if (BattleField[i][j] == 0)
			{
				BattleField[i][j] == cGround;
			}
		}
	}
	for (int i = 0; i < BattleFieldHeight; i++)
	{
		for (int j = 0; j < BattleFieldWidth; j++)
		{
			if (BattleField[i][j] == cWall)
			{
				Object[i][j].TypeOfObject = cWall;
				Object[i][j].NumOfObject = i * (BattleFieldWidth)+j;
				Object[i][j].posX = j * SquareTriangle + ScreenWidthFrame;
				Object[i][j].posY = i * SquareTriangle + ScreenHeightFrame;
				Object[i][j].HP = 50;
				Object[i][j].NumOfTexture = 0;
				Object[i][j].isBulletsThrough = false;
				Object[i][j].isSlowDownBullets = false;
				Object[i][j].isSlowedDown = false;
			}
			else if (BattleField[i][j] == cTree)
			{
				Object[i][j].TypeOfObject = cTree;
				Object[i][j].NumOfObject = i * (BattleFieldWidth)+j;
				Object[i][j].posX = j * SquareTriangle + ScreenWidthFrame;
				Object[i][j].posY = i * SquareTriangle + ScreenHeightFrame;
				Object[i][j].HP = 100;
				Object[i][j].NumOfTexture = 0;
				Object[i][j].isBulletsThrough = true;
				Object[i][j].isSlowDownBullets = true;
				Object[i][j].isSlowedDown = false;
			}
			else if (BattleField[i][j] == cWater)
			{
				Object[i][j].TypeOfObject = cWater;
				Object[i][j].NumOfObject = i * (BattleFieldWidth)+j;
				Object[i][j].posX = j * SquareTriangle + ScreenWidthFrame;
				Object[i][j].posY = i * SquareTriangle + ScreenHeightFrame;
				Object[i][j].HP = 100;
				Object[i][j].NumOfTexture = 0;
				Object[i][j].isBulletsThrough = true;
				Object[i][j].isSlowDownBullets = false;
				Object[i][j].isSlowedDown = false;
			}
			else
			{
				Object[i][j].TypeOfObject = cGround;
				Object[i][j].NumOfObject = i * (BattleFieldWidth)+j;
				Object[i][j].posX = j * SquareTriangle + ScreenWidthFrame;
				Object[i][j].posY = i * SquareTriangle + ScreenHeightFrame;
				Object[i][j].HP = 100;
				Object[i][j].NumOfTexture = 0;
				Object[i][j].isBulletsThrough = true;
				Object[i][j].isSlowDownBullets = false;
				Object[i][j].isSlowedDown = false;
			}
		}
	}
}
///////////
void Logic::Interaction(int NumOfTank)
{
	for (int i = 0; i < BattleFieldHeight; i++)
	{
		for (int j = 0; j < BattleFieldWidth; j++)
		{
			if ((IntRect(j * SquareTriangle + ScreenWidthFrame, i * SquareTriangle + ScreenHeightFrame, SquareTriangle, SquareTriangle).contains(Bullet[NumOfTank].posX, Bullet[NumOfTank].posY) and !Object[i][j].isBulletsThrough) and Bullet[NumOfTank].isInAir)
			{
				Bullet[NumOfTank].isInAir = false;
				Object[i][j].HP -= (Bullet[NumOfTank].Damage + Bullet[NumOfTank].Damage * Bullet[NumOfTank].isCritical);
				if (Object[i][j].HP <= 0)
				{
					Object[i][j].TypeOfObject = cGround;
					Object[i][j].NumOfTexture = 0;
					Object[i][j].isBulletsThrough = true;
					Object[i][j].isSlowDownBullets = false;
				}
			}
			if (Object[i][j].isSlowedDown and !IntRect(j * SquareTriangle + ScreenWidthFrame, i * SquareTriangle + ScreenHeightFrame, SquareTriangle, SquareTriangle).contains(Bullet[NumOfTank].posX, Bullet[NumOfTank].posY))
				Object[i][j].isSlowedDown = false;
			if (IntRect(j * SquareTriangle + ScreenWidthFrame, i * SquareTriangle + ScreenHeightFrame, SquareTriangle, SquareTriangle).contains(Bullet[NumOfTank].posX, Bullet[NumOfTank].posY) and Object[i][j].isSlowDownBullets and Object[i][j].isSlowedDown == false and Object[i][j].TypeOfObject == cTree and Bullet[NumOfTank].isInAir)
			{
				Object[i][j].isSlowedDown = true;
				Bullet[NumOfTank].BulletSpeed -= 0.05;
				Bullet[NumOfTank].Damage -= 0.4;
				if (Bullet[NumOfTank].BulletSpeed <= CBulletSpeed / 3 or Bullet[NumOfTank].Damage <= 0)
				{
					Bullet[NumOfTank].isInAir = false;
				}
			}
			else
				Object[i][j].isSlowedDown = false;
			if (!Bullet[NumOfTank].isInAir)
			{
				Bullet[NumOfTank].BulletSpeed = CBulletSpeed;
				Bullet[NumOfTank].Damage = Damage;
			}
			if (Object[i][j].TypeOfObject == cWall or Object[i][j].TypeOfObject == cWater)
			{
				if ((Tank[NumOfTank].posY - Object[i][j].posY >= (0 + TankTextFrame) and Tank[NumOfTank].posY - Object[i][j].posY <= (SquareTriangle - TankTextFrame)) and abs(Tank[NumOfTank].posX - Object[i][j].posX) < (SquareTriangle - TankTextFrame) and Tank[NumOfTank].isUp)
					Tank[NumOfTank].posY += Tank[NumOfTank].TankSpeed;
				if ((Tank[NumOfTank].posY - Object[i][j].posY <= -(0 + TankTextFrame) and Tank[NumOfTank].posY - Object[i][j].posY >= -(SquareTriangle - TankTextFrame)) and abs(Tank[NumOfTank].posX - Object[i][j].posX) < (SquareTriangle - TankTextFrame) and Tank[NumOfTank].isDown)
					Tank[NumOfTank].posY -= Tank[NumOfTank].TankSpeed;
				if ((Tank[NumOfTank].posX - Object[i][j].posX >= (0 + TankTextFrame) and Tank[NumOfTank].posX - Object[i][j].posX <= (SquareTriangle - TankTextFrame)) and abs(Tank[NumOfTank].posY - Object[i][j].posY) < (SquareTriangle - TankTextFrame) and Tank[NumOfTank].isLeft)
					Tank[NumOfTank].posX += Tank[NumOfTank].TankSpeed;
				if ((Tank[NumOfTank].posX - Object[i][j].posX <= -(0 + TankTextFrame) and Tank[NumOfTank].posX - Object[i][j].posX >= -(SquareTriangle - TankTextFrame)) and abs(Tank[NumOfTank].posY - Object[i][j].posY) < (SquareTriangle - TankTextFrame) and Tank[NumOfTank].isRight)
					Tank[NumOfTank].posX -= Tank[NumOfTank].TankSpeed;
			}
		}
	}
}
/////////////
int Logic::GetMap(int i, int j, int NumOfValue)
{
	switch (NumOfValue)
	{
	case 1: return Object[i][j].TypeOfObject;
	case 2: return Object[i][j].NumOfObject;
	case 3: return Object[i][j].posX;
	case 4: return Object[i][j].posY;
	case 5: return Object[i][j].HP;
	case 6: return Object[i][j].NumOfTexture;
	case 7: return Object[i][j].isBulletsThrough;
	case 8: return Object[i][j].isSlowDownBullets;
	case 9: return Object[i][j].isSlowedDown;
	default: return 0;
	}
}
/////////////
