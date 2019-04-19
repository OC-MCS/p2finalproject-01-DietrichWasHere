#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

// Missiles to shoot aliens; spawning / despawning dependent on Missiles class
class Bomb
{
private:
	Sprite  bombSprite; // sprite depicting missile, holding location
public:
	// constructor; pass texture by reference; ship pos determines spawn location
	Bomb(Texture &bombTxtr, Vector2f alienPos)
	{
		bombSprite.setTexture(bombTxtr);
		bombSprite.setPosition(alienPos.x + (2 * bombTxtr.getSize().x), alienPos.y);
	}
	// change sprite's position, return false if off screen to initiate destruction
	// window heigth, speed as input
	// bool tells whether if bomb has not exited screen
	bool moveDown(float windH, float speed)
	{
		bool continueFlight = true; // tell program to delete dynamically alocated sprite if true
		if (bombSprite.getPosition().y < windH)
		{
			bombSprite.move(0, speed);
		}
		else
		{
			continueFlight = false;
		}
		return continueFlight;
	}
	// for collisions (check for collision with aliens)
	FloatRect getCollision()
	{
		return bombSprite.getGlobalBounds();
	}
	// for drawing the missile's sprite
	Sprite getSprite()
	{
		return bombSprite;
	}
};