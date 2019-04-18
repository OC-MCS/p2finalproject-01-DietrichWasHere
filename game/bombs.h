#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;
#include <list>
#include <ctime>
#include <cstdlib>
using namespace std;
#include "bomb.h"
#include "alienHerd.h"

// 
class Bombs
{
private:
	list<Bomb> bombList;
	int spawnDelay;
public:
	Bombs()
	{
		spawnDelay = 30;
	}
	// check wait time, reset if up
	// base time depends on level
	// returns bool to trigger bomb drop
	bool waitTimeOver(int maxTime, int minTime)
	{
		bool over = false; // return value; communicates if wait time is over
		if (spawnDelay <= 0)
		{
			// if wait time up, reset, generate missile
			over = true;
			unsigned seed = time(0);
			srand(seed);
			spawnDelay = (rand() % (maxTime - minTime)) + minTime;
		}
		else
		{
			// decrement wait time
			spawnDelay--;
		}
		return over;
	}
	// create a bomb, add it to the list
	void spawnBomb(Texture &bombTxtr, Vector2f alienPos)
	{
		Bomb nBomb(bombTxtr, alienPos);
		bombList.push_back(nBomb);
	}
	// handle bomb movement, collison / action, drawing
	// return true if hit player
	// takes in window ref (rendering, window bounds check), shipbounds (collision)
	// speed for downward movement
	bool moveBombs(RenderWindow &win, FloatRect shipBounds, float speed)
	{
		bool hit = false; // if a hit, destroy missile, return true to destroy ship
		list<Bomb>::iterator iter;
		for (iter = bombList.begin(); iter != bombList.end();)
		{

			if (!(iter->moveDown(win.getSize().y, speed))) // if missile can't move up, despawn
			{
				iter = bombList.erase(iter);
			}
			else if (iter->getCollision().intersects(shipBounds)) // alien collision check; check collisions w/ all  aliens
			{
				// collision check action
				iter = bombList.erase(iter);
				hit = true;
			}
			else
			{
				win.draw(iter->getSprite());
				iter++;
			}
		}
		return hit;
	}
	// check collisions w/ missiles
	// return true if hit
	bool checkCollision(FloatRect missileBounds)
	{
		bool hit = false; // if a hit with the input rect is detected, return such
		list<Bomb>::iterator iter;
		iter = bombList.begin();
		while (iter != bombList.end() && !hit)
		{
			if (missileBounds.intersects(iter->getCollision())) hit = true;
			else iter++;
		}
		if (hit) iter = bombList.erase(iter);
		return hit;
	}
};