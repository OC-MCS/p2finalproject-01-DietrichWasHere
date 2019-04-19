#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

// kill program when font does not load
void die(string msg)
{
	cout << msg << endl;
	exit(-1);
}


// 
class UIGameControl
{
private:
	char gameState; 
	// s - screen (wait for click), g - play, a - alien victory, p - player victory
	// w - win, l - loss
	int lvl; // level of game player is on
	int lives; // lives remaining
	int score; // score, goes up as aliens destroyed
	Text dataTxt; // display game data (lvl, lives, score), constant update
	Text btnTxt; // text for button, changes based on state
	RectangleShape btn; // if clicked, play next level - works regardless of state
	Font font; // for loading font
public:
	// constructor; sets level, starting game state
	UIGameControl(Vector2u winSize)
	{
		// set btn starting values
		btn.setPosition(Vector2f((winSize.x * 3.0f)/ 8.0f, (winSize.y * 3.0f) / 8.0f));
		btn.setOutlineColor(Color::Green);
		btn.setOutlineThickness(2);
		btn.setSize(Vector2f(winSize.x / 4.0f, winSize.y / 4.0f));
		btn.setFillColor(Color::Transparent);
		// set text starting values for btnTxt
		if (!font.loadFromFile("C:\\Windows\\Fonts\\arial.ttf"))
			die("couldn't load font");
		btnTxt.setFont(font);
		btnTxt.setFillColor(Color::Green);
		btnTxt.setCharacterSize(25);
		btnTxt.setString("Start Game");
		btnTxt.setPosition(Vector2f((winSize.x * 7.0f) / 16.0f, (winSize.y * 7.0f) / 16.0f));
		gameState = 's';
		lvl = 1;
		lives = 3;
		score = 0;
		dataTxt.setFont(font);
		dataTxt.setFillColor(Color::Green);
 		dataTxt.setCharacterSize(20);
		// this is super convoluted
		dataTxt.setString("Level: 1\nLives: 3\nScore: 0");
		dataTxt.setPosition(Vector2f((winSize.x * 1.0f) / 32.0f, (winSize.y * 1.0f) / 32.0f));
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
	// check if the state is s - screen (wait for click)
	bool checkStateScreen()
	{
		return (gameState == 's');
	}
	// set state to s - screen (wait for click)
	void setStateScreen()
	{
		gameState = 's';
	}
	// check if the state is a - alien victory
	bool checkStateAlienVictory()
	{
		return (gameState == 'a');
	}
	// set state to a - alien victory
	// decrement lives
	// set btn text appropriately
	// if lives too low, reset game
	void alienVictory()
	{
		lives--;
		if (lives < 1)
		{
			resetGame();
		}
		else
		{
			gameState = 'a';
			btnTxt.setString("Ouch!\nRetry Level");
		}
	}
	// check if the state is p - player victory
	bool checkStatePlayerVictory()
	{
		return (gameState == 'p');
	}
	// if levels left
	// increasen level by 1 and set state to p - player victory
	// other wise, set gameState to w - win, reset level
	// set bnTxt appropriately
	void levelUp()
	{
		if (lvl < 3)
		{
			lvl++;
			gameState = 'p';
			btnTxt.setString("Next Level");
		}
		else
		{
			lvl = 1;
			lives = 3;
			score = 0;
			gameState = 'w';
			btnTxt.setString("Win!\nPlay Again?");
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
		gameState = 'l';
		btnTxt.setString("Game Over!\nPlay Again?");
		lvl = 1;
		lives = 3;
		score = 0;
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
		if (lvl == 1) rate = 5;
		else if (lvl == 2) rate = 8;
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
	void renderBtn(RenderWindow &win)
	{
		win.draw(btnTxt);
		win.draw(btn);
	}
	void renderData(RenderWindow &win)
	{
		// had trouble getting this to work. Didn't know how to in to str;

		string dataStr("Level: ");
		dataStr.append(to_string(lvl));
		dataStr.append("\nLives: ");
		dataStr.append(to_string(lives));
		dataStr.append("\nScore: ");
		dataStr.append(to_string(score));
		dataTxt.setString(dataStr);
		win.draw(dataTxt);
	}
	void checkBtnClick(Vector2f mouse)
	{
		if (btn.getGlobalBounds().contains(mouse))
		{
			setStatePlay();
		}
	}
	bool checkLevel(int level)
	{
		return (lvl == level);
	}
	void increaseScore(int add)
	{
		score += add;
	}
};