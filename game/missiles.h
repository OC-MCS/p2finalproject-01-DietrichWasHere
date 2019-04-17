#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;
#include <list>
using namespace std;
#include "missile.h"


class Missiles
{
private:
	list<Missile> missileList;
	int spawnDelay;
public:
	Missiles()
	{
		spawnDelay = 0;
	}
	void spawnMissile(Texture &missileTxtr, Vector2f shipPos, int spawnWaitTime)
	{
		if (spawnDelay <= 0)
		{
			Missile nMissile(missileTxtr, shipPos);
			missileList.push_back(nMissile);
			spawnDelay = spawnWaitTime;
		}
	}
	// handle missile movement, collison / action, drawing
	void moveMissiles(RenderWindow &win)
	{
		if (spawnDelay > 0) spawnDelay--;
		list<Missile>::iterator iter;
		for (iter = missileList.begin(); iter != missileList.end();)
		{
		
			if (!(iter->moveUp())) // if missile can't move up, despawn
			{
				iter = missileList.erase(iter);
			}
			else if (false) // alien collision check
			{
				iter->getCollision();
				// collision check action
				iter = missileList.erase(iter);
			}
			else if (false) // bomb collision check
			{
				iter->getCollision();
				// collision check action
				iter = missileList.erase(iter);
			}
			else
			{
				win.draw(iter->getSprite());
				iter++;
			}
		}
	}
};