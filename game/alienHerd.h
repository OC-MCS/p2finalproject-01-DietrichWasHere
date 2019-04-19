#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;
#include <list>
#include <ctime>
#include <cstdlib>
using namespace std;
#include "alien.h"

class AlienHerd
{
private:
	list<Alien> alienGroup; // hold all the aliens
public:
	// create an alien, copy constructor into list
	void spawnAlien(Texture &alienTxtr, Vector2f alienPos)
	{
		Alien nAlien(alienTxtr, alienPos);
		alienGroup.push_back(nAlien);
	}
	// add a group of aliens usign spawn alien method
	void addAliens(Texture &alienTxtr, float num, Vector2u windowBounds)
	{
		Vector2f alienPos(0.0f, 0.0f);
		alienPos.y = windowBounds.y / 40.0f;
		for (float i = 1; i <= num; i++)
		{
			alienPos.x = ((windowBounds.x * (i + 2.0f)) / (num + 5.0f)) + 0.25f;
			spawnAlien(alienTxtr, alienPos);
		}
	}
	// handle missile movement, collison / action, drawing
	// if aliens reach bottom of screen, 
	bool moveHerd(RenderWindow &win, float speed, int shipYPos)
	{
		bool cont = true; // if an alien reaches bottom, player loses, continue = false
		list<Alien>::iterator iter = alienGroup.begin();
		// move first missile, check if missiles have reached ship
		iter->moveDown(speed);
		if (iter->getYPos() > shipYPos) cont = false;
		win.draw(iter->getSprite());
		iter++;

		while (iter != alienGroup.end())
		{
			iter->moveDown(speed);
			win.draw(iter->getSprite());
			iter++;
		}
		return cont;
	}
	// check all aliens' collisions against individual missile, if hit, destroy alien
	// return true to tell missiles to destroy missile
	bool checkCollision(FloatRect missileBounds)
	{
		bool hit = false; // if a hit with the input rect is detected, return such
		list<Alien>::iterator iter;
		iter = alienGroup.begin();
		while (iter != alienGroup.end() && !hit)
		{
			if (missileBounds.intersects(iter->getCollision())) hit = true;
			else iter++;
		}
		if (hit) iter = alienGroup.erase(iter);
		return hit;
	}
	// return true if no aliens left
	bool getWin()
	{
		bool win = false;
		if (alienGroup.size() < 1)
		{
			win = true;
		}
		return win;
	}
	// get an alien for a bomb position
	Vector2f getBombPos()
	{
		Vector2f bombPos;
		unsigned seed = time(0);
		srand(seed);
		int alienToDrop = rand() % alienGroup.size(); // the alien in the order that drops the bomb
		list<Alien>::iterator iter;
		iter = alienGroup.begin();
		for (int i = 0; i < alienToDrop; i++) iter++;
		bombPos = iter->getPos();
		bombPos.y += 1.0f;
		bombPos.x += 1.0f;
		return bombPos;
	}
	// clear out any remaining aliens for reset / next level
	void clearAliens()
	{
		alienGroup.clear();
	}
};
	
