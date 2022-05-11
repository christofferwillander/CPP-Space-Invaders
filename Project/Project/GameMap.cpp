#include "GameMap.h"
#include <iostream>

void GameMap::draw(sf::RenderTarget & target, sf::RenderStates state) const
{
	target.draw(*this->player);
	
	if (this->player->isAlive())
	{
		target.draw(*this->enemyHandler);
		target.draw(this->livesText);


		for (int i = 0; i < 4; i++)
		{
			target.draw(*this->shields[i]);

			if (i < 2)
			{
				target.draw(this->highScoreText[i]);
				target.draw(this->scoreText[i]);
			}
		}
	}
}

GameMap::GameMap(float width = 600.0f, float height = 600.0f)
{
	this->width = width;
	this->height = height;

	if (!this->font.loadFromFile("../Resources/fonts/space_invaders.ttf"))
	{
		std::cout << "Error loading font" << std::endl;
		system("pause");
	}

	this->player = new PlayerEntity(this->width, this->height);
	this->enemyHandler = new EnemyHandler(this->width, this->height);
	
	for (int i = 0; i < 4; i++)
	{
		this->shields[i] = new ShieldObject((this->width * 0.175f) + ((this->width * 0.183f) * i), (this->height * 0.75f));
	}

	this->livesText.setFont(this->font);
	this->livesText.setCharacterSize(20);

	this->scoreText[0].setString("<Score>");
	this->scoreText[1].setString(std::to_string(0));
	this->highScoreText[0].setString("<Hi-Score>");
	this->highScoreText[1].setString(std::to_string(0));


	this->livesText.setPosition(440.0f, 10.0f);

	for (int i = 0; i < 2; i++)
	{
		this->scoreText[i].setFont(this->font);
		this->highScoreText[i].setFont(this->font);
		this->scoreText[i].setCharacterSize(20);
		this->highScoreText[i].setCharacterSize(20);

		if (i == 0)
		{
			this->scoreText[i].setPosition((this->width / 12.0f), (this->height / 60.0f));
			this->highScoreText[i].setPosition((220.0f / this->width) * this->width, (this->height / 60.0f));
		}
	}
}

GameMap::GameMap(const GameMap & origObj)
{
	this->highScore = origObj.highScore;
	this->width = origObj.width;
	this->height = origObj.height;
	this->font = origObj.font;
	this->livesText = origObj.livesText;
	this->player = new PlayerEntity(*origObj.player);
	this->enemyHandler = new EnemyHandler(*origObj.enemyHandler);

	for (int i = 0; i < 4; i++)
	{
		this->shields[i] = new ShieldObject(*origObj.shields[i]);

		if (i < 2)
		{
			this->scoreText[i] = origObj.scoreText[i];
			this->highScoreText[i] = origObj.highScoreText[i];
		}
	}
}

GameMap & GameMap::operator=(const GameMap & origObj)
{
	if (this != &origObj)
	{
		delete this->player;
		delete this->enemyHandler;

		for (int i = 0; i < 4; i++)
		{
			delete this->shields[i];
		}

		this->highScore = origObj.highScore;
		this->width = origObj.width;
		this->height = origObj.height;
		this->font = origObj.font;
		this->livesText = origObj.livesText;
		this->player = new PlayerEntity(*origObj.player);
		this->enemyHandler = new EnemyHandler(*origObj.enemyHandler);

		for (int i = 0; i < 4; i++)
		{
			this->shields[i] = new ShieldObject(*origObj.shields[i]);

			if (i < 2)
			{
				this->scoreText[i] = origObj.scoreText[i];
				this->highScoreText[i] = origObj.highScoreText[i];
			}
		}
	}

	return *this;
}

GameMap::~GameMap()
{
	delete this->player;
	delete this->enemyHandler;
	
	for (int i = 0; i < 4; i++)
	{
		delete this->shields[i];
	}
}

void GameMap::Update(float deltatime)
{
	if (this->player->isAlive()) // If a game is ongoing (player is alive)
	{
		this->player->Update(deltatime);
		this->enemyHandler->Update(deltatime);

		if (this->player->isShooting()) // Checking collisions between player projectile, shields & enemies
		{
			this->enemyHandler->collisionCheck(this->player->getLaserPtr(), this->player->getScorePtr());
			
			for (int i = 0; i < 4; i++)
			{
				this->shields[i]->collisionCheck(this->player->getLaserPtr());
			}
		}

		for (int i = 0; i < 55; i++) // Checking collisions between enemy projectiles, shields & player
		{
			if (this->enemyHandler->getLaserPtr(i).isShooting())
			{
				if (this->player->collisionCheck(this->enemyHandler->getLaserPtr(i)))
				{
					this->enemyHandler->stopAction();
				}
				
				for (int j = 0; j < 4; j++)
				{
					this->shields[j]->collisionCheck(this->enemyHandler->getLaserPtr(i));
				}
			}
		}

		if (!this->enemyHandler->anyAlive() && this->player->isAlive()) // If all enemies are dead & the player is alive - start new round
		{
			this->enemyHandler->newRound();
			this->player->nextRound();
		}

		if (this->player->getScore() > this->highScore) // If player beats high score - update high score text
		{
			this->highScoreText[1].setString(std::to_string(this->player->getScore())); 
		}

		this->livesText.setString("Lives: " + std::to_string(this->player->getLives())); // Update text showing amount of lives left
		this->scoreText[1].setString(std::to_string(this->player->getScore())); // Update score text
		this->scoreText[1].setPosition((this->width / 12.0f) + (this->scoreText[0].getGlobalBounds().width / 2.0f) - (this->scoreText[1].getGlobalBounds().width / 2.0f), (this->height / 60.0f) + 30.0f); // Center score text
		this->highScoreText[1].setPosition((220.0f / this->width) * this->width + (this->highScoreText[0].getGlobalBounds().width / 2.0f) - (this->highScoreText[1].getGlobalBounds().width / 2), (this->height / 60.0f) + 30.0f); // Center high score text

	}
}

void GameMap::updateHighScore(int highScore)
{
	this->highScore = highScore;
	this->highScoreText[1].setString(std::to_string(highScore));
}

void GameMap::resetAll() const
{
	this->player->reset();
	this->enemyHandler->resetAll();

	for (int i = 0; i < 4; i++)
	{
		this->shields[i]->reset();
	}
}

PlayerEntity & GameMap::getPlayerPtr() const
{
	return this->player->getPlayerPtr();
}
