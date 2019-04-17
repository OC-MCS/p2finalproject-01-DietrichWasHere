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
public:
	void spawnMissile(Texture &missileTxtr, Vector2f shipPos)
	{
		Missile * nMissile = new Missile(missileTxtr, shipPos);
		missileList.push_back(*nMissile);
	}
	void moveMissiles(RenderWindow &win)
	{
		list<Missile>::iterator iter;
		for (iter = missileList.begin(); iter != missileList.end();)
		{
			if (iter->moveUp())
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