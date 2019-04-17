#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;
#include <list>
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
			alienPos.x = (windowBounds.x * (i + 2.0f)) / (num + 2.0f);
			spawnAlien(alienTxtr, alienPos);
		}
	}
	// handle missile movement, collison / action, drawing
	// if aliens reach bottom of screen, 
	bool moveHerd(RenderWindow &win, int speed, int shipYPos)
	{
		bool loss = false; // if an alien reaches bottom, player loses
		list<Alien>::iterator iter = alienGroup.begin();
		// move first missile, check if missiles have reached ship
		iter->moveDown(speed);
		if (iter->getYPos() > shipYPos) loss = true;
		win.draw(iter->getSprite());
		iter++;


		while (iter != alienGroup.end())
		{
			iter->moveDown(speed);
			win.draw(iter->getSprite());
			iter++;
		}
		return loss;
	}
	bool checkCollision(FloatRect missileBounds)
	{
		bool hit = false; // if a hit with the input rect is detected, return such
		list<Alien>::iterator iter;
		for (iter = alienGroup.begin(); iter != alienGroup.end() && !hit;iter++)
		{
			if (missileBounds.intersects(iter->getCollision())) hit = true;
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
};
	
