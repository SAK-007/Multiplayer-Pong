/*
* C++ Pong
*
* Author:SAK-007
*
* Copyright 2022,2023
*
*/


#include<SFML/Graphics.hpp>		//Graphics Library
#include<SFML/Window.hpp>		//Window Library
#include<SFML/Audio.hpp>		//Audio Library
#include<SFML/System.hpp>		//System Library
#include<SFML/Main.hpp>			//Main Library
#include<stdlib.h>				//Standart C C++ Library
#include<iostream>				//C++ IO library
#include"include/Menu.h"		//Library for Menu
#include"include/Splash.h"		//Library for splash screen
#include"include/Player1.h"		//Library for Player1Wins() function
#include"include/Player2.h"		//Library for Player2Wins() function

#define SCREEN_HEIGHT 800	//Height of the Window
#define SCREEN_WIDTH 600    //Width of the Window


using namespace sf; //sf:: Namespace


//Positions
Vector2f Bat1pos = Vector2f(20, 250);
Vector2f Bat2pos = Vector2f(770, 250);
Vector2f BallPos = Vector2f(400, 300);
Vector2f UpBoundPos = Vector2f(0, 0);
Vector2f DownBoundPos = Vector2f(0, 595);

//Sizes
Vector2f batsize = Vector2f(10, 120);


//Colours
Color Green = Color::Green;


//Speeds
float BatSpeed = 0.8;
float BallSpeed = 0.6;

//Variables that will be needed
float BatThickness = 3;
int Random;
int Random2;
int Player1Score = 0;
int Player2Score = 0;
float BallThickness = 12;
int manutemp;
int Splashtemp;
int WinningScore = 49;


int main()
{
	Splashtemp = Splash();
	manutemp = menu();
	//Booleans
	bool hitball = true;
	bool ballhitbat1 = false;
	bool ballhitbat2 = false;
	bool space = false;

	//Logics
	if (manutemp == 0)
	{
		return 0;
	}

	RenderWindow window(VideoMode(SCREEN_HEIGHT, SCREEN_WIDTH), "Multiplayer Pong"); //Rendering window
	window.setMouseCursorVisible(false);
	window.setVerticalSyncEnabled(true);
	
	//Bats
	RectangleShape bat(batsize);			//Setting up bat size
	bat.setPosition(Bat1pos);				//Set position
	bat.setOutlineThickness(BatThickness);  //Set outline thickness
	bat.setOutlineColor(Color::Black);		//Set outline color

	RectangleShape bat2(batsize);			//Setting up bat size
	bat2.setPosition(Bat2pos);				//Set position
	bat2.setOutlineThickness(BatThickness); //Set outline thickness
	bat2.setOutlineColor(Color::Black);		//Set outline color


	//Ball
	CircleShape ball(BallThickness);	//Initializing ball thickness
	ball.setFillColor(Color::Red);		//Setting ball color
	ball.setOutlineThickness(3);		//Setting outline thickness
	ball.setOutlineColor(Color::Black);	//Setting outline color
	ball.setPosition(BallPos);			//Positioning ball


	//Boundaries
	RectangleShape BoundforPlayer1(Vector2f(5,850));
	RectangleShape BoundforPlayer2(Vector2f(5, 850));
	BoundforPlayer2.setPosition(795, 0);

	RectangleShape UpBound(Vector2f(800, 5));
	UpBound.setPosition(UpBoundPos);

	RectangleShape DownBound(Vector2f(800, 5));
	DownBound.setPosition(DownBoundPos);

	//Sounds
	SoundBuffer buffer;
	buffer.loadFromFile("Resources/ball.wav");
	Sound doink;
	doink.setBuffer(buffer);

	//Fonts
	Font Consolas;
	Consolas.loadFromFile("Resources/Consolas.ttf");

	//Text
	Text Player1ScoreText;
	Player1ScoreText.setFont(Consolas);
	Player1ScoreText.setPosition(20,0);
	Player1ScoreText.setFillColor(Color::Yellow);

	Text Player2ScoreText;
	Player2ScoreText.setFont(Consolas);
	Player2ScoreText.setPosition(745, 0);
	Player2ScoreText.setFillColor(Color::Yellow);

	//Times
	Time waittime = sf::seconds(0.1);


	while (window.isOpen()) //Main loop
	{
		bat.setFillColor(Color::White);
		bat2.setFillColor(Color::White);
		srand(time(NULL));
		Random = rand() % 2;
		Random2 = rand() % 2;

		Event event; //Initializing event
		while (window.pollEvent(event)) //Event loop
		{
			if(event.type == Event::Closed) { return 0; } //Close by pressing x
			if(Keyboard::isKeyPressed(Keyboard::Escape)) { return 0; } //Close by pressing Esc
		}

		if (!hitball)
		{
		    ball.move(-BallSpeed, 0);
		}
		
		

		if (Keyboard::isKeyPressed(Keyboard::Space) && hitball && !space)
		{
			space = true;
			hitball = false;
		}

		/* Update things */
		Player1ScoreText.setString((std::to_string(Player1Score)));
		Player2ScoreText.setString((std::to_string(Player2Score)));


		//Move bat 1
		if (Keyboard::isKeyPressed(Keyboard::W) && bat.getPosition().y > 3)
		{
			bat.move(0, -BatSpeed);
		}

		if (Keyboard::isKeyPressed(Keyboard::S) && bat.getPosition().y < 447)
		{
			bat.move(0, BatSpeed);
		}

		//Move bat 2
		if (Keyboard::isKeyPressed(Keyboard::Up) && bat2.getPosition().y > 3)
		{
			bat2.move(0, -BatSpeed);
		}

		if (Keyboard::isKeyPressed(Keyboard::Down) && bat2.getPosition().y < 447)
		{
			bat2.move(0, BatSpeed);
		}


		/*  Collision logics here */


		if (bat2.getGlobalBounds().intersects(ball.getGlobalBounds()))
		{
			doink.play();
			hitball = true;
			ballhitbat2 = true;
			ballhitbat1 = false;
		}

		if (bat.getGlobalBounds().intersects(ball.getGlobalBounds()))
		{
			doink.play();
			hitball = true;
			ballhitbat2 = false;
			ballhitbat1 = true;
		}


		if (ballhitbat2)
		{
			if (Random == 1)
			{
				ball.move(-BallSpeed, 0.1);
			}
			else if (Random == 0)
			{
				ball.move(-BallSpeed, -0.1);
			}
		}

		if (ballhitbat1)
		{
			if (Random2 == 1)
			{
				ball.move(BallSpeed, 0.1);
			}
			else if (Random2 == 0)
			{
				ball.move(BallSpeed, -0.1);
			}
		}




		if (ball.getGlobalBounds().intersects(UpBound.getGlobalBounds()))
		{
			ball.setPosition(Vector2f(BallPos));
			sleep(waittime);
		}

		if (ball.getGlobalBounds().intersects(DownBound.getGlobalBounds()))
		{
			ball.setPosition(Vector2f(BallPos));
			sleep(waittime);
		}

		if (ball.getGlobalBounds().intersects(BoundforPlayer1.getGlobalBounds()))
		{		
			ball.setPosition(Vector2f(700, 300));
			Player2Score++;
			sleep(waittime);
		}

		if (ball.getGlobalBounds().intersects(BoundforPlayer2.getGlobalBounds()))
		{			
			ball.setPosition(Vector2f(200,300));
			Player1Score++;
			sleep(waittime);
		}

		if (Player1Score > WinningScore)
		{
			Player1Win();
		}

		if (Player2Score > WinningScore)
		{
			Player2Win();
		}


		/* Render things here */

		window.clear(Green);			//Clear window
		window.draw(Player1ScoreText);	//Player1 Score Text
		window.draw(Player2ScoreText);	//Player2 Score Text
		window.draw(bat);				//Render bat
		window.draw(bat2);				//Render bat 2
		window.draw(ball);				//Render the nice ball		
		window.display();				//Display the window
	}

	return 0;
}