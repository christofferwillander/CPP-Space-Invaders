#include "PlayerEntity.h"
#include <iostream>

void PlayerEntity::draw(sf::RenderTarget & target, sf::RenderStates state) const
{
	target.draw(this->pSprite);
	target.draw(*this->playerLaser);
}

PlayerEntity::PlayerEntity(float width, float height)
{	
	this->width = width;
	this->height = height;
	this->pSpeed = 400.0f;
	this->score = 0;
	this->lives = 3;
	this->extraLifeUsed = false;

	this->playerLaser = new LaserShooter(this->width, this->height);

	if (!this->pTexture.loadFromFile("../Resources/images/player.png"))
	{
		std::cout << "Texture was not found" << std::endl;
		system("pause");
	}

	if (!this->loseLifeSoundBuffer.loadFromFile("../Resources/fx/lose_life.wav"))
	{
		std::cout << "Sound was not found" << std::endl;
		system("pause");
	}

	if (!this->lifeUnlockedSoundBuffer.loadFromFile("../Resources/fx/life_unlocked.wav"))
	{
		std::cout << "Sound was not found" << std::endl;
		system("pause");
	}


	this->pSprite.setTexture(this->pTexture);
	this->pSprite.setPosition((this->width / 2.0f) - (this->pSprite.getGlobalBounds().width / 2.0f), (this->height * 0.9f));

	this->loseLifeSound.setBuffer(this->loseLifeSoundBuffer);
	this->lifeUnlockedSound.setBuffer(this->lifeUnlockedSoundBuffer);
}

PlayerEntity::PlayerEntity(const PlayerEntity & origObj)
{
	this->score = origObj.score;
	this->lives = origObj.lives;
	this->pSpeed = origObj.pSpeed;
	this->width = origObj.width;
	this->height = origObj.height;
	this->extraLifeUsed = origObj.extraLifeUsed;
	this->pTexture = origObj.pTexture;
	this->pSprite = origObj.pSprite;
	this->loseLifeSoundBuffer = origObj.loseLifeSoundBuffer;
	this->loseLifeSound = origObj.loseLifeSound;
	this->lifeUnlockedSoundBuffer = origObj.lifeUnlockedSoundBuffer;
	this->lifeUnlockedSound = origObj.lifeUnlockedSound;
	this->playerLaser = new LaserShooter(*origObj.playerLaser);
}

PlayerEntity & PlayerEntity::operator=(const PlayerEntity & origObj)
{
	if (this != &origObj)
	{
		delete this->playerLaser;
		this->score = origObj.score;
		this->lives = origObj.lives;
		this->pSpeed = origObj.pSpeed;
		this->width = origObj.width;
		this->height = origObj.height;
		this->extraLifeUsed = origObj.extraLifeUsed;
		this->pTexture = origObj.pTexture;
		this->pSprite = origObj.pSprite;
		this->loseLifeSoundBuffer = origObj.loseLifeSoundBuffer;
		this->loseLifeSound = origObj.loseLifeSound;
		this->lifeUnlockedSoundBuffer = origObj.lifeUnlockedSoundBuffer;
		this->lifeUnlockedSound = origObj.lifeUnlockedSound;
		this->playerLaser = new LaserShooter(*origObj.playerLaser);
	}

	return *this;
}

PlayerEntity::~PlayerEntity()
{
	delete this->playerLaser;
}

void PlayerEntity::Update(float deltatime)
{
	sf::Vector2f direction(0.0f, 0.0f);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && this->isAlive())
	{
		if (!(this->pSprite.getPosition().x < (this->width / 9.0f)))
		{
			direction.x = -1.0f;
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && this->isAlive())
	{
		if (!(this->pSprite.getPosition().x > ((this->width - (this->width / 9.0f)) - this->pSprite.getGlobalBounds().width)))
		{
			direction.x = 1.0f;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !this->playerLaser->isShooting() && this->isAlive())
	{
		this->playerLaser->shoot(this->pSprite.getPosition().x, this->pSprite.getPosition().y);
	}

	this->pSprite.move(direction * this->pSpeed * deltatime);

	this->playerLaser->Update(deltatime);
}

int PlayerEntity::getScore() const
{
	return this->score;
}

int PlayerEntity::getLives() const
{
	return this->lives;
}

bool PlayerEntity::isAlive() const
{
	return !(this->lives == 0);
}

bool PlayerEntity::isShooting() const
{
	return this->playerLaser->isShooting();
}

bool PlayerEntity::collisionCheck(LaserShooter & enemyLaser)
{
	bool hasCollided = false;

	if (this->pSprite.getGlobalBounds().intersects(enemyLaser.getGlobalBounds()) && this->isAlive())
	{
		this->lives--;
		this->loseLifeSound.play();
		this->pSprite.setPosition((this->width / 2.0f) - (this->pSprite.getGlobalBounds().width / 2.0f), (this->height * 0.9f));
		enemyLaser.stopShooting();
		hasCollided = true;
	}

	return hasCollided;
}

void PlayerEntity::nextRound()
{
	this->pSprite.setPosition((this->width / 2.0f) - (this->pSprite.getGlobalBounds().width / 2.0f), (this->height * 0.9f));

	if (!this->extraLifeUsed)
	{
		this->lives++;
		this->extraLifeUsed = true;
		this->lifeUnlockedSound.play();
	}
}

void PlayerEntity::reset()
{
	this->pSprite.setPosition((this->width / 2.0f) - (this->pSprite.getGlobalBounds().width / 2.0f), (this->height * 0.9f));
	this->score = 0;
	this->lives = 3;
	this->extraLifeUsed = false;
}

PlayerEntity & PlayerEntity::getPlayerPtr()
{
	return *this;
}

LaserShooter & PlayerEntity::getLaserPtr() const
{
	return *this->playerLaser;
}

int & PlayerEntity::getScorePtr()
{
	return this->score;
}
