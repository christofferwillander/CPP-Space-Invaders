#ifndef GAMEHANDLER_H
#define GAMEHANDLER_H
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include "GameMap.h"
#include "Menu.h"
#include "HighScoreList.h"

class GameHandler:public sf::Drawable
{
public:
	static const int MENU = -1;
	static const int GAME = 0;
	static const int HIGH_SCORE_LIST = 1;
	static const int GAME_OVER = 3;

	void Update(float deltatime);
	void setState(int state);
	int getState() const;
	Menu& getMenuPtr() const;

private:
	float width;
	float height;
	int state;
	sf::Clock clock;
	sf::Texture gameOverScreenTex;
	sf::Sprite gameOverScreenSp;
	sf::Font font;
	sf::Text guidanceTexts[2];
	sf::SoundBuffer returnSoundBuffer;
	sf::Sound returnSound;
	GameMap *map;
	Menu *menu;
	HighScoreList *highScoreList;

	void draw(sf::RenderTarget &target, sf::RenderStates state) const;

public:
	GameHandler(float width, float height);
	GameHandler(const GameHandler &origObj);
	GameHandler& operator = (const GameHandler &origObj);
	virtual ~GameHandler();
};

#endif
