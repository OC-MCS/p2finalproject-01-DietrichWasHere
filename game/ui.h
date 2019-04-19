#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

// 
class UIGameControl
{
private:
	char gameState; 
	// s - startScreen, g - play, a - alien victory, p - player victory
	// w - win, l - loss
	int lvl; // level of game player is on
	int lives; // lives remaining
public:
	// constructor; sets level, starting game state
	UIGameControl()
	{
		gameState = 's';
		lvl = 1;
		lives = 3;
	}
	// check if the state is g - play
	bool checkStatePlay()
	{
		return (gameState == 'g');
	}
	// set state to g - play
	void setStatePlay()
	{
		gameState = 'g';
	}
	// check if the state is g - play
	bool checkStateStart()
	{
		return (gameState == 's');
	}
	// set state to s - play
	// reset to first level
	void setStateStart()
	{
		gameState = 's';
		lvl = 1;
	}
	// check if the state is a - alien victory
	bool checkStateAlienVictory()
	{
		return (gameState == 'a');
	}
	// set state to a - alien victory
	// decrement lives
	// if lives too low, reset game
	void setStateAlienVictory()
	{
		gameState = 'a';
		lives--;
		if (lives < 1)
		{
			resetGame();
		}
	}
	// check if the state is p - player victory
	bool checkStatePlayerVictory()
	{
		return (gameState == 'p');
	}
	// set state to p - player victory
	// increasen level by 1; 
	void setStatePlayerVictory()
	{
		gameState = 'p';
		levelUp();
	}
	// increase level by 1 if there is another level
	// other wise, set gameState to w - win, reset level
	void levelUp()
	{
		if (lvl < 3) lvl++;
		else
		{
			lvl = 1;
			gameState = 'w';
		}
	}
	// check if the state is w - win
	bool checkStateWin()
	{
		return (gameState == 'w');
	}
	// if lives too low, reset game
	// set state to l - loss
	void resetGame()
	{
		cout << lives << " " << lvl << endl;
		gameState = 'l';
		lvl = 1;
		lives = 3;
	}
	// check if the state is l - loss
	bool checkStateLoss()
	{
		return (gameState == 'l');
	}

	// methods for level data
	// based on level, return the number of aliens that should be spawned
	int getNumAliens()
	{
		int aliens = 0;
		if (lvl == 1) aliens = 10;
		else if (lvl == 2) aliens = 12;
		else if (lvl == 3) aliens = 5;
		return aliens;
	}
	// based on level, control missile spawn rate;
	int getMissileSpawnRate()
	{
		int rate = 0;
		if (lvl == 1) rate = 2;
		else if (lvl == 2) rate = 5;
		else if (lvl == 3) rate = 10;
		return rate;
	}
	// based on level, control alien drop speed;
	// double this value used for missile drop speed
	float getAlienDropSpeed()
	{
		float rate = 0;
		if (lvl == 1) rate = 0.2;
		else if (lvl == 2) rate = 0.5;
		else if (lvl == 3) rate = 1;
		return rate;
	}
	// get vector holding  max (x val) and min (y val) for bomb spawn time (randomized)
	Vector2i getBombSpawnTime()
	{
		Vector2i spawnTime;
		if (lvl == 1)
		{
			spawnTime.x = 500;
			spawnTime.y = 100;
		}
		else if (lvl == 2)
		{
			spawnTime.x = 200;
			spawnTime.y = 50;
		}
		else if (lvl == 3)
		{
			spawnTime.x = 40;
			spawnTime.y = 15;
		}
		return spawnTime;
	}
};