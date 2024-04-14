#include "stdlib.h"
#include "conio.h"
#include "iostream"
#include "functional"
#include "assert.h"


#include "Core/Core.h"

#include "Charecters.h"
#include "../Engine/Renderer/Screen.h"

#include "SFML/Graphics.hpp"

namespace Game
{
	// Globals for the game
	static SmartPointer<player> p;
	static SmartPointer<enemy> e;

	static int initialEnemyCount;
	
	static int localLoop;

	static bool ToPlay;

	void InitializeGame()
	{
		using namespace std::placeholders;
		p = new player;
		p->InitializePlayerFromJSON("data\\GoodGuy.json");
		p->CO->CollisionCallback = std::bind(&player::CollisionResponse, &(*p));

		e = new enemy;
		e->InitializeEnemyFromJSON("data\\Enemy.json");
		e->CO->CollisionCallback = std::bind(&enemy::CollisionResponse, &(*e));
		
		initialEnemyCount = 0;
		localLoop = 0;
		ToPlay = true;
	}

	void ShutdownGame()
	{
		p->RemovePlayer();
		p = nullptr;

		e->RemoveEnemy();
		e = nullptr;
	}
}


#pragma region Old Code

//void freeMem()
//{
//	localLoop = 0;
//	while (localLoop <= 9)
//	{
//		delete Enemy[localLoop];
//		localLoop++;
//	}
//	delete p;
//	delete screenObject;
//}

//// tick function
//bool update()
//{
//	// update time
//	time++;
//
//	// move charecters
//	ToPlay = p.move();
//	for (localLoop = 0; localLoop <= 9; localLoop++)
//		if (Enemy[localLoop]->lifetime > 0) //Checking in array if enemy is alive or dead and show only alive ones
//			Enemy[localLoop]->move();  // call the enemy's move function
//
//	// generate new enemy after 5 moves in empty location (location with dead enemy)
//	if (time % 5 == 0)   
//	{
//		for (localLoop = 0; localLoop <= 9; localLoop++)
//		{
//			if (Enemy[localLoop]->lifetime == 0)
//			{
//				delete Enemy[localLoop];     // replace the dead enemies with new ones.. delete so no memory leak
//				Enemy[localLoop] = new enemy;
//			}
//		}
//	}
//
//	return ToPlay;
//}

//int main()
//{
//	{
//		p = new player;
//		char ch = 'w';
//
//		std::cout << "Please enter the name of the player ";
//		p.playerName = GetString();
//
//		std::cout << "\nPlease enter the numbver of initial enemies upto 5 ";
//		std::cin >> initialEnemyCount;
//
//		startGame();
//
//		while (1) // MAIN GAME LOOP
//		{
//			ToPlay = update();
//			if( ToPlay )
//				render();
//			else break;
//		}
//		freeMem();
//	}
//	_CrtDumpMemoryLeaks();
//	return 0;
//}

#pragma endregion

using namespace Game;

void TestKeyCallback(unsigned int i_VKeyID, bool bWentDown)
{
#ifdef _DEBUG
	const size_t	lenBuffer = 65;
	char			Buffer[lenBuffer];

	sprintf_s(Buffer, lenBuffer, "VKey 0x%04x went %s\n", i_VKeyID, bWentDown ? "down" : "up");
	OutputDebugStringA(Buffer);
#endif // __DEBUG

	const point2d UP(0, .02f), DOWN(0, -.02f), LEFT(-.01f, 0), RIGHT(.01f, 0), Z(0.f,0.f);

	if (p) // If player exists
	{
		switch (i_VKeyID)
		{
		case 0x0057: // Virtual Key w
			
			bWentDown ? p->move(UP) : p->move(Z);
			break;

		case 0x0053: // Virtual Key s

			bWentDown ? p->move(DOWN) : p->move(Z);
			break;

		case 0x0041: // Virtual Key a

			bWentDown ? p->move(LEFT) : p->move(Z);
			break;

		case 0x0044: // Virtual Key d

			bWentDown ? p->move(RIGHT) : p->move(Z);
			break;

		}
	}
}

bool MatrixUnitTest()
{
	point4d InitialScreenLocation(1.f, 2.f, 3.f, 0.f);
	Matrix4 ConversionMat, RotationMat, TranslationMat;
	RotationMat = RotationMat.CV_CreateZRotationMat(180.f);
	TranslationMat = TranslationMat.CV_CreateTranslationMat(point3d(2.f, 2.f, 2.f));
	Multiply(TranslationMat, RotationMat, ConversionMat);
	point4d ConvertedCoordinate = ConversionMat * InitialScreenLocation;

	Matrix4 InversionMat;
	ConversionMat.Inverse(InversionMat);
	point4d ReconvertedScreenLocation;

	ReconvertedScreenLocation = InversionMat * ConvertedCoordinate;
	//Multiply(InversionMat, ConversionMat, ReconvertedScreenLocation);
	//ReconvertedScreenLocation = InversionMat * ConversionMat;

	if (ReconvertedScreenLocation == InitialScreenLocation)
		return true;
	return false;
}


int WINAPI wWinMain(HINSTANCE i_hInstance, HINSTANCE i_hPrevInstance, LPWSTR i_lpCmdLine, int i_nCmdShow)
{
	// Initialize GLib

#if USE_SFML
	sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(shape);
		window.display();
	}

#else
	bool bSuccess = GLib::Initialize(i_hInstance, i_nCmdShow, "GLibTest", -1, 1280, 720);
	Engine::Initialize();
	InitializeGame();
	if (bSuccess)
	{
		// Set a callback for notification of key presses
		GLib::SetKeyStateChangeCallback(TestKeyCallback);

		bool bQuit = false;

		do
		{
			// IMPORTANT: We need to let GLib do it's thing. 
			GLib::Service(bQuit);
			
			if (!bQuit)
			{
				Engine::Tick();
				if (p->QuitRequested)
					bQuit = true;
			}
		} while (bQuit == false);

		ShutdownGame();

		if (!Engine::ShutDown())
			DebugPrint120("\nEngine Shutdown Failed!/n");
	}
#endif
	
#if defined _DEBUG
	_CrtDumpMemoryLeaks();
#endif // _DEBUG

}