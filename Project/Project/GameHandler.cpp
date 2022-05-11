#include "GameHandler.h"
#include <iostream>

void GameHandler::draw(sf::RenderTarget & target, sf::RenderStates state) const
{
	if (this->state == this->MENU)
	{
		target.draw(*this->menu);
	}
	else if (this->state == this->GAME)
	{
		target.draw(*this->map);
	}
	else if (this->state == this->HIGH_SCORE_LIST)
	{
		target.draw(*this->highScoreList);
	}
	else if (this->state == this->GAME_OVER)
	{
		target.draw(this->gameOverScreenSp);
		
		for (int i = 0; i < 2; i++)
		{
			target.draw(this->guidanceTexts[i]);
		}
	}
}

GameHandler::GameHandler(float width, float height)
{
	this->width = width;
	this->height = height;
	this->state = -1;
	this->map = new GameMap(this->width, this->height);
	this->menu = new Menu(this->width, this->height);
	this->highScoreList = new HighScoreList(this->width, this->height);

	this->map->updateHighScore(this->highScoreList->getHighestScore());

	if (!this->gameOverScreenTex.loadFromFile("../Resources/images/game_over.png"))
	{
		std::cout << "Texture was not found" << std::endl;
		system("pause");
	}

	if (!this->returnSoundBuffer.loadFromFile("../Resources/fx/menu_selection.wav"))
	{
		std::cout << "Sound was not found" << std::endl;
		system("pause");
	}

	if (!this->font.loadFromFile("../Resources/fonts/space_invaders.ttf"))
	{
		std::cout << "Font was not found" << std::endl;
		system("pause");
	}

	this->gameOverScreenSp.setTexture(this->gameOverScreenTex);
	this->gameOverScreenSp.setPosition((this->width / 2.0f) - (this->gameOverScreenSp.getGlobalBounds().width / 2.0f), (this->height / 12.0f));

	this->guidanceTexts[0].setFont(this->font);
	this->guidanceTexts[1].setFont(this->font);

	this->guidanceTexts[0].setCharacterSize(25);
	this->guidanceTexts[1].setCharacterSize(15);

	this->returnSound.setBuffer(this->returnSoundBuffer);
}

GameHandler::GameHandler(const GameHandler & origObj)
{
	this->width = origObj.width;
	this->height = origObj.height;
	this->state = origObj.state;
	this->clock = origObj.clock;
	this->gameOverScreenTex = origObj.gameOverScreenTex;
	this->gameOverScreenSp = origObj.gameOverScreenSp;
	this->font = origObj.font;
	this->guidanceTexts[0] = origObj.guidanceTexts[0];
	this->guidanceTexts[1] = origObj.guidanceTexts[1];
	this->returnSoundBuffer = origObj.returnSoundBuffer;
	this->returnSound = origObj.returnSound;

	this->map = new GameMap(*origObj.map);
	this->menu = new Menu(*origObj.menu);
	this->highScoreList = new HighScoreList(*origObj.highScoreList);
}

GameHandler & GameHandler::operator=(const GameHandler & origObj)
{
	if (this != &origObj)
	{
		delete this->map;
		delete this->menu;
		delete this->highScoreList;

		this->width = origObj.width;
		this->height = origObj.height;
		this->state = origObj.state;
		this->clock = origObj.clock;
		this->gameOverScreenTex = origObj.gameOverScreenTex;
		this->gameOverScreenSp = origObj.gameOverScreenSp;
		this->font = origObj.font;
		this->guidanceTexts[0] = origObj.guidanceTexts[0];
		this->guidanceTexts[1] = origObj.guidanceTexts[1];
		this->returnSoundBuffer = origObj.returnSoundBuffer;
		this->returnSound = origObj.returnSound;

		this->map = new GameMap(*origObj.map);
		this->menu = new Menu(*origObj.menu);
		this->highScoreList = new HighScoreList(*origObj.highScoreList);
	}

	return *this;
}

GameHandler::~GameHandler()
{
	delete this->map;
	delete this->menu;
	delete this->highScoreList;
}

void GameHandler::Update(float deltatime)
{
	if (!this->map->getPlayerPtr().isAlive() && this->state != this->GAME_OVER) // If player is dead - set state to game over
	{
		this->state = this->GAME_OVER;
		this->guidanceTexts[0].setString(std::to_string(this->map->getPlayerPtr().getScore()));
		this->guidanceTexts[0].setPosition((this->width / 2) - (this->guidanceTexts[0].getGlobalBounds().width / 2), (this->height * 0.65f));

		if (this->map->getPlayerPtr().getScore() > this->highScoreList->getLowestScore()) // If player has beaten the lowest score on high score list
		{
			this->guidanceTexts[1].setString("Congratulations! New High Score!");
		}
		else
		{
			this->guidanceTexts[1].setString("You will be sent to the High Score screen in a few seconds");
		}
		this->clock.restart();
		this->guidanceTexts[1].setPosition((this->width / 2) - (this->guidanceTexts[1].getGlobalBounds().width / 2), (this->height * 0.9f)); // Center text
	}

	if (this->state == this->GAME) // If a game is ongoing
	{
		this->map->Update(deltatime);
	}
	else if (this->state == this->GAME_OVER) // If game is over
	{
		if (this->map->getPlayerPtr().getScore() > this->highScoreList->getLowestScore())
		{
			
			this->highScoreList->addHighScore(this->map->getPlayerPtr().getScore()); // Add high score to high score list
			this->map->updateHighScore(this->highScoreList->getHighestScore()); // Update high score text in-game
		}

		this->map->resetAll(); // Reset game map (enemies, shields, player) to prepare for new game

		if (this->clock.getElapsedTime().asSeconds() > 10.0) // Continue to high score list after 10 seconds
		{
			this->state = this->HIGH_SCORE_LIST;
		}
	}
	else if (this->state == this->HIGH_SCORE_LIST) // Return to main menu if space is pressed
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			this->returnSound.play();
			this->state = this->MENU;
		}
	}
}

void GameHandler::setState(int state)
{
	this->state = state;
}

int GameHandler::getState() const
{
	return this->state;
}

Menu & GameHandler::getMenuPtr() const
{
	return *this->menu;
}
