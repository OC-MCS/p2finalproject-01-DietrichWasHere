#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;



class Alien
{
private:
	Sprite  alienSprite; // sprite depicting missile, holding location
public:
	// constructor; pass texture by reference; ship pos determines spawn location
	Alien(Texture &alienTxtr, Vector2f alienPos)
	{
		alienSprite.setTexture(alienTxtr);
		alienSprite.setPosition(alienPos.x, alienPos.y);
	}
	// move alien towards player
	void moveDown(float speed)
	{
		alienSprite.move(0, speed);
		/*
		bool continueFlight = true; // tell program to delete dynamically alocated sprite if true
		if (alienSprite.getPosition().y < shipYPos)
		{
			
		}
		else
		{
			continueFlight = false;
		}
		return continueFlight;*/
	}
	// return y poss for loss check
	float getYPos()
	{
		return alienSprite.getPosition().y;
	}
	// send position for bomb creation
	Vector2f getPos()
	{
		return alienSprite.getPosition();
	}
	// for collisions (check for collision with aliens)
	FloatRect getCollision()
	{
		return alienSprite.getGlobalBounds();
	}
	// for drawing the alien's sprite
	Sprite getSprite()
	{
		return alienSprite;
	}
};