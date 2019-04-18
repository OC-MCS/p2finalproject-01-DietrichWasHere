#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;
#include <list>
using namespace std;
#include "missile.h"
#include "alienHerd.h"
#include "bombs.h"


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
	void moveMissiles(RenderWindow &win, AlienHerd &herd, Bombs &bombGroup)
	{
		if (spawnDelay > 0) spawnDelay--;
		list<Missile>::iterator iter;
		for (iter = missileList.begin(); iter != missileList.end();)
		{
		
			if (!(iter->moveUp())) // if missile can't move up, despawn
			{
				iter = missileList.erase(iter);
			}
			else if (herd.checkCollision(iter->getCollision())) // alien collision check; check collisions w/ all  aliens
			{
				// collision check action
				iter = missileList.erase(iter);
			}
			else if (bombGroup.checkCollision(iter->getCollision())) // bomb collision check
			{
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
	// clear out any remaining missiles for reset / next level
	void clearMissiles()
	{
		missileList.clear();
		cout << "cleared" << endl;
	}
};