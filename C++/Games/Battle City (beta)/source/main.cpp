#include "Logic.h"
using namespace sf;
///////////////////

std::string Tank_NumOfTexture(int NumOfTexture, int Player)
{
	std::stringstream ss_texture;
	std::stringstream ss_player;
	std::string texture;
	std::string player;
	ss_texture << (NumOfTexture % 3)+1;
	ss_player << Player;
	ss_texture >> texture;
	ss_player >> player;
	switch (NumOfTexture / 3)
	{
	case 0:
		return "Textures/PlayerTank/P" + player + "/P" + player + "_up_" + texture + ".png";
		break;
	case 1:
		return "Textures/PlayerTank/P" + player + "/P" + player + "_down_" + texture + ".png";
	case 2:
		return "Textures/PlayerTank/P" + player + "/P" + player + "_left_" + texture + ".png";
		break;
	case 3:
		return "Textures/PlayerTank/P" + player + "/P" + player + "_right_" + texture + ".png";
		break;
	}
}
///////////////////

std::string Tank_BlowUpTexture(int NumOfTexture)
{
	std::stringstream ss_texture;
	std::string texture;
	ss_texture << (NumOfTexture % 8) + 1;
	ss_texture >> texture;
	return "Textures/PlayerTank/blow_" + texture + ".png";
}
///////////////

int main()
{
	srand(time(0));
	int NumOfTexture[NumOfTanks] = { 0 };
	int NumOfDegrees = 0;
	int BulletPosX = 0;
	int BulletPosY = 0;
	std::string String[NumOfTanks];
	Event event;
	bool inGame = true;
	bool isUp[NumOfTanks] = { false };
	bool isDown[NumOfTanks] = { false };
	bool isLeft[NumOfTanks] = { false };
	bool isRight[NumOfTanks] = { false };
	bool isShoot[NumOfTanks] = { false };
	Logic ObjLogic;
	///////////////////////////////////////////
	std::string Bullet_Texture[4] = {
	"Textures/bullet_up.png",
	"Textures/bullet_down.png",
	"Textures/bullet_left.png",
	"Textures/bullet_right.png" };
	///////////////////////////////////////////
	std::string ARR_BrickWall[3] = { "Textures/brick_wall_full.png","Textures/brick_wall_med.png","Textures/brick_wall_low.png" };
	std::string ARR_Water[2] = { "Textures/Water_1.png","Textures/Water_2.png" };
	std::string ARR_Tree[2] = { "Textures/Tree_1.png","Textures/Tree_2.png" };
	std::string ARR_Ground[1] = { "Textures/ground.png" };
	Image BLOW1;
	Image BLOW2;
	Image P1TANK;
	Image P2TANK;
	Image P1_BULLET;
	Image P2_BULLET;
	Image IMG_Water;
	Image IMG_Tree;
	Image IMG_BrickWall_fullHP;
	Image IMG_BrickWall_mediumHP;
	Image IMG_BrickWall_lowHP;
	Image IMG_Ground;
	P1TANK.loadFromFile(Tank_NumOfTexture(0, Player[1]));
	P2TANK.loadFromFile(Tank_NumOfTexture(0, Player[2]));
	BLOW1.loadFromFile(Tank_BlowUpTexture(0));
	BLOW2.loadFromFile(Tank_BlowUpTexture(0));
	P1_BULLET.loadFromFile(Bullet_Texture[0]);
	P2_BULLET.loadFromFile(Bullet_Texture[0]);
	//	IMG_BrickWall.loadFromFile(ARR_BrickWall[0]);
	//	P2_BULLET.loadFromFile(Bullet_Texture[0]);
	IMG_BrickWall_fullHP.loadFromFile(ARR_BrickWall[0]);
	IMG_BrickWall_mediumHP.loadFromFile(ARR_BrickWall[1]);
	IMG_BrickWall_lowHP.loadFromFile(ARR_BrickWall[2]);
	Texture P1, P2, P1_T_Bullet, P2_T_Bullet, T1_B, T2_B;
	Texture T_BrickWall, T_Water, T_Tree, T_Ground;
	///////////////////
	P1TANK.createMaskFromColor(Color::Black);
	P2TANK.createMaskFromColor(Color::Black);
	P1_BULLET.createMaskFromColor(Color::Black);
	P2_BULLET.createMaskFromColor(Color::Black);
	BLOW1.createMaskFromColor(Color::Black);
	BLOW2.createMaskFromColor(Color::Black);
	IMG_BrickWall_fullHP.createMaskFromColor(Color::Black);
	IMG_BrickWall_mediumHP.createMaskFromColor(Color::Black);
	IMG_BrickWall_lowHP.createMaskFromColor(Color::Black);
	IMG_Ground.createMaskFromColor(Color::Black);
	///////////////////////////////////////////
	ObjLogic.DefaultTankCharacters(Player[1]);
	ObjLogic.DefaultTankCharacters(Player[2]);
	T1_B.loadFromFile(Tank_BlowUpTexture(0));
	T2_B.loadFromFile(Tank_BlowUpTexture(0));
	T1_B.loadFromImage(BLOW1);
	T2_B.loadFromImage(BLOW2);
	//	T_BrickWall.loadFromImage(IMG_BrickWall);
	T_Water.loadFromFile(ARR_Water[0]);
	T_Tree.loadFromFile(ARR_Tree[0]);
	T_Ground.loadFromFile(ARR_Ground[0]);
	P1_T_Bullet.loadFromImage(P1_BULLET);
	P2_T_Bullet.loadFromImage(P2_BULLET);
	///////////////////////////////////////////	
	Sprite P1_Tank(P1), P2_Tank(P2), P1_Bullet(P1_T_Bullet), P2_Bullet(P2_T_Bullet);
	Sprite P1_Tank_Blowing(T1_B), P2_Tank_Blowing(T2_B);
	Sprite BrickWall(T_BrickWall);
	Sprite Tree(T_Tree);
	Sprite Water(T_Water);
	Sprite Ground(T_Ground);
	///////////////////////////////////////////
	///////////////////////////////////////////
	Music Music;
	SoundBuffer Sound_Driving;
	SoundBuffer Sound_Shoot;
	SoundBuffer Sound_Death;
	Sound Driving(Sound_Driving);
	Sound P1_Shoot(Sound_Shoot);
	Sound P2_Shoot(Sound_Shoot);
	Sound Death(Sound_Death);
	///////////////////////////////////////////	
	Font Font;
	Font.loadFromFile("Fonts/arial.ttf");
	Text P1_HP("", Font, 10);
	Text P2_HP("", Font, 10);
	P1_HP.setFillColor(Color::White);
	P2_HP.setFillColor(Color::White);
	///////////////////////////////////////////
	Sound_Driving.loadFromFile("Music/Driving.wav");
	Sound_Shoot.loadFromFile("Music/Shoot.wav");
	Sound_Death.loadFromFile("Music/Death.wav");
	//	Music.openFromFile("Music/TMNT.ogg");
	Music.openFromFile("Music/Medieval.ogg");
	///////////////////////////////////////////	
	RenderWindow window(VideoMode(ScreenWidth + 2 * ScreenWidthFrame, ScreenHeight + 2 * ScreenHeightFrame), "Battle City");
	ObjLogic.ObjectInitialiser();
	Music.play();
	///////////////////////////////////////////	
	int DebugCounter = 0;
	bool isNewGameButtonPressed = false;
	while (inGame)
	{
		window.clear(Color(Color::Black));
		if (Keyboard::isKeyPressed(Keyboard::N))
		{
			if (!isNewGameButtonPressed)
			{
				isNewGameButtonPressed = true;
				ObjLogic.ObjectInitialiser();
				for (int i = 0; i < NumOfTanks; i++)
					ObjLogic.DefaultTankCharacters(Player[i]);
			}
		}
		else
			isNewGameButtonPressed = false;
		if (DebugCounter % 50 == 0)
		{
			IMG_Tree.loadFromFile(ARR_Tree[ObjLogic.Randomiser(2, 0)]);
			T_Water.loadFromFile(ARR_Water[ObjLogic.Randomiser(2, 0)]);
			IMG_Tree.createMaskFromColor(Color::Black);
			T_Tree.loadFromImage(IMG_Tree);
			Sprite Tree(T_Tree);
			Sprite Water(T_Water);
		}
		for (int i = 0; i < BattleFieldHeight; i++)
		{
			for (int j = 0; j < BattleFieldWidth; j++)
			{
				Ground.setPosition(j * SquareTriangle + ScreenWidthFrame, i * SquareTriangle + ScreenHeightFrame);
				window.draw(Ground);
				if (ObjLogic.GetMap(i, j, 1) == cWater)
				{
					Water.setPosition(j * SquareTriangle + ScreenWidthFrame, i * SquareTriangle + ScreenHeightFrame);
					window.draw(Water);
				}
			}
		}
		///////////////////
		isUp[Player[1]] = Keyboard::isKeyPressed(Keyboard::W);
		isDown[Player[1]] = Keyboard::isKeyPressed(Keyboard::S);
		isLeft[Player[1]] = Keyboard::isKeyPressed(Keyboard::A);
		isRight[Player[1]] = Keyboard::isKeyPressed(Keyboard::D);
		isShoot[Player[1]] = Keyboard::isKeyPressed(Keyboard::Q);
		ObjLogic.PlayerControl(Player[1], isUp[Player[1]], isDown[Player[1]], isLeft[Player[1]], isRight[Player[1]], isShoot[Player[1]]);
		////////////
		isUp[Player[2]] = Keyboard::isKeyPressed(Keyboard::Up);
		isDown[Player[2]] = Keyboard::isKeyPressed(Keyboard::Down);
		isLeft[Player[2]] = Keyboard::isKeyPressed(Keyboard::Left);
		isRight[Player[2]] = Keyboard::isKeyPressed(Keyboard::Right);
		isShoot[Player[2]] = Keyboard::isKeyPressed(Keyboard::Numpad0);
		////////////
		ObjLogic.PlayerControl(Player[2], isUp[Player[2]], isDown[Player[2]], isLeft[Player[2]], isRight[Player[2]], isShoot[Player[2]]);
		if (!Music.getStatus())
			Music.play();
		if (!Driving.getStatus())
			Driving.play();
		if (isShoot[Player[1]]
			and
			!ObjLogic.GetValues(Player[1], BULLET_ISINAIR)
			and
			!ObjLogic.GetValues(Player[1], TANK_ISDEAD)
			and
			ObjLogic.GetValues(Player[1], TANK_RELOADINGTIME) == 0)
		{
			P1_Shoot.play();
		}
		if (isShoot[Player[2]]
			and
			!ObjLogic.GetValues(Player[2], BULLET_ISINAIR)
			and
			!ObjLogic.GetValues(Player[2], TANK_ISDEAD)
			and
			ObjLogic.GetValues(Player[2], TANK_RELOADINGTIME) == 0)
		{
			P2_Shoot.play();
		}
		if ((isUp[Player[1]] + isDown[Player[1]] + isLeft[Player[1]] + isRight[Player[1]] == 1
			and
			!ObjLogic.GetValues(Player[1], TANK_ISDEAD))
			or
			(isUp[Player[2]] + isDown[Player[2]] + isLeft[Player[2]] + isRight[Player[2]] == 1)
			and
			!ObjLogic.GetValues(Player[2], TANK_ISDEAD))
		{
			Driving.setVolume(100);
		}
		else
		{
			Driving.setVolume(0);
			Driving.stop();
		}
		////////////////////////////////////////////
		////////////////////////////////////////////
		if (!ObjLogic.GetValues(Player[1], TANK_ISDEAD))
		{
			std::stringstream P1_ss;
			P1_ss << ObjLogic.GetValues(Player[1], TANK_HP);
			P1_ss >> String[Player[1]];
			P1_HP.setString(String[Player[1]] + "HP");
			P1_HP.setPosition(ObjLogic.GetValues(Player[1], TANK_POSX) + SquareTriangle / 5 - TankTextFrame - 2, ObjLogic.GetValues(Player[1], TANK_POSY) - SquareTriangle / 2);
			P1TANK.loadFromFile(Tank_NumOfTexture(ObjLogic.TankTextureChanger(Player[1], NumOfTexture[Player[1]]), Player[1]));
			P1TANK.createMaskFromColor(Color::Black);
			P1.loadFromImage(P1TANK);
			P1_Tank.setTextureRect(IntRect(0 + TankTextFrame, 0 + TankTextFrame, SquareTriangle - 2 * TankTextFrame, SquareTriangle - 2 * TankTextFrame));
			if (ObjLogic.GetValues(Player[1], BULLET_VECTOR) > 2)
				P1_Bullet.setTextureRect(IntRect(0, 0, 7, 5));
			else
				P1_Bullet.setTextureRect(IntRect(0, 0, 5, 7));
			P1_Tank.setPosition(ObjLogic.TankHorisontalDriving(Player[1], NumOfTexture[Player[1]]), ObjLogic.TankVerticalDriving(Player[1], NumOfTexture[Player[1]]));
			P1_Tank_Blowing.setPosition(ObjLogic.GetValues(Player[1], TANK_POSX) - TankTextFrame, ObjLogic.GetValues(Player[1], TANK_POSY) - TankTextFrame);
			P1_BULLET.loadFromFile(Bullet_Texture[ObjLogic.BulletReady(Player[1])]);
			P1_BULLET.createMaskFromColor(Color::Black);
			P1_T_Bullet.loadFromImage(P1_BULLET);
			P1_Bullet.setPosition(ObjLogic.GetValues(Player[1], BULLET_POSX), ObjLogic.GetValues(Player[1], BULLET_POSY));
			///////////////////////////////////

			//////////////////////////////////
		}
		else
		{
			P1_Tank_Blowing.setTextureRect(IntRect(0, 0, SquareTriangle, SquareTriangle));
			if (DebugCounter % 25 == 0)
				T1_B.loadFromFile(Tank_BlowUpTexture(ObjLogic.Death(Player[1])));
			if (ObjLogic.Death(Player[1]) == 2)
				Death.play();
		}
		RectangleShape P1_ReloadLine(Vector2f(abs(ObjLogic.GetValues(Player[1], TANK_RELOADINGTIME) - CReloadingTime) / 4, 5));
		P1_ReloadLine.setPosition(ObjLogic.GetValues(Player[1], TANK_POSX) - TankTextFrame, ObjLogic.GetValues(Player[1], TANK_POSY) - 2 * TankTextFrame);
		P1_ReloadLine.setFillColor(Color(255, 255, 255));
		///////////////////////////////////	
		////////////////////////////////////
		if (!ObjLogic.GetValues(Player[2], TANK_ISDEAD))
		{
			std::stringstream P2_HP_ss;
			P2_HP_ss << ObjLogic.GetValues(Player[2], TANK_HP);
			P2_HP_ss >> String[Player[2]];
			P2_HP.setString(String[Player[2]] + "HP");
			P2_HP.setPosition(ObjLogic.GetValues(Player[2], TANK_POSX) + SquareTriangle / 5 - TankTextFrame - 2, ObjLogic.GetValues(Player[2], TANK_POSY) - SquareTriangle / 2);
			P2TANK.loadFromFile(Tank_NumOfTexture(ObjLogic.TankTextureChanger(Player[2], NumOfTexture[Player[2]]), Player[2]));
			P2TANK.createMaskFromColor(Color::Black);
			P2.loadFromImage(P2TANK);
			P2_Tank.setTextureRect(IntRect(0 + TankTextFrame, 0 + TankTextFrame, SquareTriangle - 2 * TankTextFrame, SquareTriangle - 2 * TankTextFrame));
			if (ObjLogic.GetValues(Player[2], BULLET_VECTOR) > 2)
				P2_Bullet.setTextureRect(IntRect(0, 0, 7, 5));
			else
				P2_Bullet.setTextureRect(IntRect(0, 0, 5, 7));
			P2_Tank.setPosition(ObjLogic.TankHorisontalDriving(Player[2], NumOfTexture[Player[2]]), ObjLogic.TankVerticalDriving(Player[2], NumOfTexture[Player[2]]));
			P2_Tank_Blowing.setPosition(ObjLogic.GetValues(Player[2], TANK_POSX) - TankTextFrame, ObjLogic.GetValues(Player[2], TANK_POSY) - TankTextFrame);
			P2_BULLET.loadFromFile(Bullet_Texture[ObjLogic.BulletReady(Player[2])]);
			P2_BULLET.createMaskFromColor(Color::Black);
			P2_T_Bullet.loadFromImage(P2_BULLET);
			P2_Bullet.setPosition(ObjLogic.GetValues(Player[2], BULLET_POSX), ObjLogic.GetValues(Player[2], BULLET_POSY));
		}
		else
		{
			P2_Tank_Blowing.setTextureRect(IntRect(0, 0, SquareTriangle, SquareTriangle));
			if (DebugCounter % 25 == 0)
				T2_B.loadFromFile(Tank_BlowUpTexture(ObjLogic.Death(Player[2])));
			if (ObjLogic.Death(Player[2]) == 2)
				Death.play();
		}
		////////////////////////////////////
		DebugCounter++;
		ObjLogic.Interaction(Player[1]);
		ObjLogic.Interaction(Player[2]);
		///////////////////////////////////
		RectangleShape P2_ReloadLine(Vector2f(abs(ObjLogic.GetValues(Player[2], TANK_RELOADINGTIME) - CReloadingTime) / 4, 5));
		P2_ReloadLine.setPosition(ObjLogic.GetValues(Player[2], TANK_POSX) - TankTextFrame, ObjLogic.GetValues(Player[2], TANK_POSY) - 2 * TankTextFrame);
		P2_ReloadLine.setFillColor(Color(255, 255, 255));
		///////////////////////////////////
		if (!ObjLogic.GetValues(Player[1], TANK_ISDEAD)) { window.draw(P1_Bullet); window.draw(P1_Tank); }
		else { window.draw(P1_Tank); window.draw(P1_Tank_Blowing); }
		//////////
		if (!ObjLogic.GetValues(Player[2], TANK_ISDEAD)) { window.draw(P2_Bullet); window.draw(P2_Tank); }
		else { window.draw(P2_Tank); window.draw(P2_Tank_Blowing); }
		//////////
		for (int i = 0; i < BattleFieldHeight; i++)
		{
			for (int j = 0; j < BattleFieldWidth; j++)
			{
				if (ObjLogic.GetMap(i, j, 1) == cWall)
				{
					if (ObjLogic.GetMap(i, j, 5) <= cWallHP / 3)
						T_BrickWall.loadFromImage(IMG_BrickWall_lowHP);
					if (ObjLogic.GetMap(i, j, 5) > cWallHP / 3 and ObjLogic.GetMap(i, j, 5) <= 2 * cWallHP / 3)
						T_BrickWall.loadFromImage(IMG_BrickWall_mediumHP);
					if (ObjLogic.GetMap(i, j, 5) > 2 * cWallHP / 3)
						T_BrickWall.loadFromImage(IMG_BrickWall_fullHP);
					Sprite BrickWall(T_BrickWall);
					BrickWall.setPosition(j * SquareTriangle + ScreenWidthFrame, i * SquareTriangle + ScreenHeightFrame);
					window.draw(BrickWall);
				}
				if (ObjLogic.GetMap(i, j, 1) == cTree)
				{
					Tree.setPosition(j * SquareTriangle + ScreenWidthFrame, i * SquareTriangle + ScreenHeightFrame);
					window.draw(Tree);
				}
			}
		}
		///////////////////////////////////
		if (!ObjLogic.GetValues(Player[1], TANK_ISDEAD)) { window.draw(P1_HP); window.draw(P1_ReloadLine); }
		if (!ObjLogic.GetValues(Player[2], TANK_ISDEAD)) { window.draw(P2_HP); window.draw(P2_ReloadLine); }
		window.display();
		if (Keyboard::isKeyPressed(Keyboard::Escape) or !window.isOpen())
			inGame = false;
		/////////////////
		///////////////////////////////////
		Sleep(SleepTime);
		///////////////////////////////////
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}
		/////////////////	
	}
	return 0;
}
