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
#include "ui.h"

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

	UIGameControl game(window.getSize());

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
	Texture * alienTexture; // point to current alien texture
	Texture alienTexture1;
	if (!alienTexture1.loadFromFile("alien2.png"))
	{
		cout << "Unable to load alien texture!" << endl;
		exit(EXIT_FAILURE);
	}
	Texture alienTexture2;
	if (!alienTexture2.loadFromFile("alien3.png"))
	{
		cout << "Unable to load alien texture!" << endl;
		exit(EXIT_FAILURE);
	}
	Texture alienTexture3;
	if (!alienTexture3.loadFromFile("alien.png"))
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
	alienTexture = &alienTexture1; // set to first alien texture
	ship.setPosition(shipX, shipY);
	herd.addAliens(*alienTexture, game.getNumAliens(), window.getSize());

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
				if (event.type == Event::KeyPressed && game.checkStatePlay())
				{
					if (event.key.code == Keyboard::Space) // && !Keyboard::isKeyPressed(Keyboard::Left) && !Keyboard::isKeyPressed(Keyboard::Right))
						// if continued work, modify to prevent strafing; attempted a fix (!'s); never mind, just increasing time between missiles
					{
						missileGroup.spawnMissile(missileTexture, ship.getPosition(), game.getMissileSpawnRate());
					}
				}
				else if (event.type == Event::MouseButtonReleased)
				{
					// maybe they just clicked on btn
					// check for this and handle it. Done!
					game.checkBtnClick(window.mapPixelToCoords(Mouse::getPosition(window)));
					// will set state to play
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
		if (game.checkStatePlay())
		{
			moveShip(ship, WINDOW_WIDTH, shipSize.x);
			// draw the ship on top of background 
			// (the ship from previous frame was erased when we drew background)
			window.draw(ship);
			if (!(herd.moveHerd(window, game.getAlienDropSpeed(), shipY))) game.alienVictory(); // herd.moveHerd only called when herd has contents
			// render/move/check collisions for bombs
			if (bombGroup.waitTimeOver(game.getBombSpawnTime())) bombGroup.spawnBomb(bombTexture, herd.getBombPos());
			if (bombGroup.moveBombs(window, ship.getGlobalBounds(), game.getAlienDropSpeed() * 2.0f)) game.alienVictory();
			// alien speed * 2 is missile speed

			// render/move/check collisions for missiles
			game.increaseScore(missileGroup.moveMissiles(window, herd, bombGroup)); // move missiles, increase score accordingly
			// check if 
			if (herd.getWin()) game.levelUp(); // change game state if all aliens defeated
			// render data - since data renders after stats change, loss of all lives results in frame where new stats arre shown
			game.renderData(window);
		}
		// if game needed to reset
		else if (game.checkStateAlienVictory() || game.checkStatePlayerVictory() || game.checkStateWin() || game.checkStateLoss())
		{
			// clear extra sprites
			bombGroup.clearBombs();
			missileGroup.clearMissiles();
			herd.clearAliens();
			// set texture based on level
			if (game.checkLevel(1)) alienTexture = &alienTexture1;
			else if (game.checkLevel(2)) alienTexture = &alienTexture2;
			else if (game.checkLevel(3)) alienTexture = &alienTexture3;
			// create game objects for level
			// used in alien reaching ground loss condition
			ship.setPosition(shipX, shipY);
			herd.addAliens(*alienTexture, game.getNumAliens(), window.getSize());
			game.setStateScreen();
		}
		else // should only work if state is screen
		{
			game.renderBtn(window);
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

