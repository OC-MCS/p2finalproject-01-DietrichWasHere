//=========================================================
// This is just the starting point for your final project.
// You are expected to modify and add classes/files as needed.
// The code below is the original code for our first graphics
// project (moving the little green ship). 
//========================================================
#include <iostream>
using namespace std;
#include <SFML/Graphics.hpp>
using namespace sf; 
#include "missiles.h"
#include "missiles.h"
#include "bombs.h"

//============================================================
// Dietrich Versaw
// Spcae Invaders Rip-off
// 4/20/19
// attempt to make a space invaders game
//============================================================

// note: a Sprite represents an image on screen. A sprite knows and remembers its own position
// ship.move(offsetX, offsetY) adds offsetX, offsetY to 
// the current position of the ship. 
// x is horizontal, y is vertical. 
// 0,0 is in the UPPER LEFT of the screen, y increases DOWN the screen
void moveShip(Sprite& ship, int windowWidth, unsigned shipSize )
{
	const float DISTANCE = 5.0;

	if (Keyboard::isKeyPressed(Keyboard::Left))
	{
		if (ship.getPosition().x > ((windowWidth * (1.0f / 20.0f)) - shipSize))
		{
			// left arrow is pressed: move our ship left 5 pixels
			// 2nd parm is y direction. We don't want to move up/down, so it's zero.
			ship.move(-DISTANCE, 0);
		}
	}
	else if (Keyboard::isKeyPressed(Keyboard::Right))
	{
		if (ship.getPosition().x < (windowWidth * (19.0f / 20.0f)))
		{
			// right arrow is pressed: move our ship right 5 pixels
			ship.move(DISTANCE, 0);
		}
	}
}



int main()
{
	const int WINDOW_WIDTH = 800;
	const int WINDOW_HEIGHT = 600;

	RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "aliens!");
	// Limit the framerate to 60 frames per second
	window.setFramerateLimit(60);

	// load textures from file into memory. This doesn't display anything yet.
	// Notice we do this *before* going into animation loop.
	Texture shipTexture;
	if (!shipTexture.loadFromFile("ship.png"))
	{
		cout << "Unable to load ship texture!" << endl;
		exit(EXIT_FAILURE);
	}
	Vector2u shipSize = shipTexture.getSize();
	Texture starsTexture;
	if (!starsTexture.loadFromFile("stars.jpg"))
	{
		cout << "Unable to load stars texture!" << endl;
		exit(EXIT_FAILURE);
	}
	Texture alienTexture;
	if (!alienTexture.loadFromFile("alien.png"))
	{
		cout << "Unable to load alien texture!" << endl;
		exit(EXIT_FAILURE);
	}
	Texture bombTexture;
	if (!bombTexture.loadFromFile("bomb.png"))
	{
		cout << "Unable to load bomb texture!" << endl;
		exit(EXIT_FAILURE);
	}
	Texture missileTexture;
	if (!missileTexture.loadFromFile("missile.png"))
	{
		cout << "Unable to load missile texture!" << endl;
		exit(EXIT_FAILURE);
	}
	// A sprite is a thing we can draw and manipulate on the screen.
	// We have to give it a "texture" to specify what it looks like

	Sprite background;
	background.setTexture(starsTexture);
	// The texture file is 640x480, so scale it up a little to cover 800x600 window
	background.setScale(1.5, 1.5);

	// create sprite and texture it
	Sprite ship;
	ship.setTexture(shipTexture);

	Missiles missileGroup;
	AlienHerd herd;
	Bombs bombGroup;

	
	// initial position of the ship will be approx middle of screen
	float shipX = window.getSize().x / 2.0f;
	float shipY = (window.getSize().y * 11)/ 12.0f;
	// used in alien reaching ground loss condition
	ship.setPosition(shipX, shipY);
	herd.addAliens(alienTexture, 10, window.getSize());
	char gameState = 'p';

	while (window.isOpen())
	{
		
		// check all the window's events that were triggered since the last iteration of the loop
		// For now, we just need this so we can click on the window and close it
		Event event;

		while (window.pollEvent(event))
		{
			

				// "close requested" event: we close the window
				if (event.type == Event::Closed)
					window.close();
				// if gamestate = playing,  check for bombSpawn; avoid spawning extra bombs
				if (event.type == Event::KeyPressed && gameState == 'p')
				{
					if (event.key.code == Keyboard::Space)
					{
						missileGroup.spawnMissile(missileTexture, ship.getPosition(), 2);
					}
				}
		}

		//===========================================================
		// Everything from here to the end of the loop is where you put your
		// code to produce ONE frame of the animation. The next iteration of the loop will
		// render the next frame, and so on. All this happens ~ 60 times/second.
		//===========================================================

		// draw background first, so everything that's drawn later 
		// will appear on top of background
		window.draw(background);
		
		// manage gamemode
		if (gameState == 'p')
		{
			moveShip(ship, WINDOW_WIDTH, shipSize.x);
			// draw the ship on top of background 
			// (the ship from previous frame was erased when we drew background)
			window.draw(ship);
			if (!(herd.moveHerd(window, 0.2, shipY))) gameState = 'a'; // herd.moveHerd only called when herd has contents
			// render/move/check collisions for bombs
			if (bombGroup.waitTimeOver(500, 100)) bombGroup.spawnBomb(bombTexture, herd.getBombPos());
			if (bombGroup.moveBombs(window, ship.getGlobalBounds(), 0.2)) gameState = 'a';
			// render/move/check collisions for missiles
			missileGroup.moveMissiles(window, herd, bombGroup);
			// check if 
			if ((gameState == 'p') && (herd.getWin())) gameState = 's'; // change game state if all aliens defeated
		}
		else
		{
			bombGroup.clearBombs();
			missileGroup.clearMissiles();
		}

		
		// end the current frame; this makes everything that we have 
		// already "drawn" actually show up on the screen
		window.display();

		// At this point the frame we have built is now visible on screen.
		// Now control will go back to the top of the animation loop
		// to build the next frame. Since we begin by drawing the
		// background, each frame is rebuilt from scratch.

		// cout << gameState << endl;

	} // end body of animation loop

	return 0;
}

