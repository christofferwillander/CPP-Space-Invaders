#include "RegularEnemy.h"
#include <iostream>

void RegularEnemy::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	if (EnemyEntity::isAlive())
	{
		target.draw(this->enemySprite);
	}

	target.draw(*this->enemyLaser);
}

RegularEnemy::RegularEnemy(sf::Texture &texture, float xPos, float yPos, float width, float height, int pointValue, int spriteID)
:EnemyEntity(texture, pointValue)
{
	this->enemySprite.setPosition(xPos, yPos);
	this->origPos.x = xPos;
	this->origPos.y = yPos;
	this->width = width;
	this->height = height;

	this->clock.restart();
	EnemyEntity::setTexture(this->enemySprite, spriteID);

	this->enemyLaser = new LaserShooter(this->width, this->height);
	this->enemyLaser->setEnemyType();
	this->isLowest = false;

	if (!this->collisionSoundBuffer.loadFromFile("../Resources/fx/invader_killed.wav"))
	{
		std::cout << "Sound was not found" << std::endl;
		system("pause");
	}

	this->collisionSound.setBuffer(this->collisionSoundBuffer);
}

RegularEnemy::RegularEnemy(const RegularEnemy & origObj)
:EnemyEntity(origObj)
{
	this->width = origObj.width;
	this->height = origObj.height;
	this->isLowest = origObj.isLowest;
	this->origPos = origObj.origPos;
	this->clock = origObj.clock;
	this->enemySprite = origObj.enemySprite;
	this->collisionSoundBuffer = origObj.collisionSoundBuffer;
	this->collisionSound = origObj.collisionSound;
	this->enemyLaser = new LaserShooter(*origObj.enemyLaser);
}

RegularEnemy & RegularEnemy::operator=(const RegularEnemy & origObj)
{
	if (this != &origObj)
	{
		delete this->enemyLaser;
		this->width = origObj.width;
		this->height = origObj.height;
		this->isLowest = origObj.isLowest;
		this->origPos = origObj.origPos;
		this->clock = origObj.clock;
		this->enemySprite = origObj.enemySprite;
		this->collisionSoundBuffer = origObj.collisionSoundBuffer;
		this->collisionSound = origObj.collisionSound;
		this->enemyLaser = new LaserShooter(*origObj.enemyLaser);
	}

	return *this;
}

RegularEnemy::~RegularEnemy()
{
	delete this->enemyLaser;
}

void RegularEnemy::Update(float deltatime)
{
	this->enemyLaser->Update(deltatime);
}

void RegularEnemy::shoot()
{
	if (this->isLowest && EnemyEntity::isAlive() && this->clock.getElapsedTime().asSeconds() > 0.5)
	{
		this->enemyLaser->shoot(this->enemySprite.getPosition().x, this->enemySprite.getPosition().y);
		this->clock.restart();
	}
}

void RegularEnemy::reset()
{
	this->enemySprite.setPosition(this->origPos);
	EnemyEntity::setAlive();
}

void RegularEnemy::setLowest(bool isLowest)
{
	this->isLowest = isLowest;
}

bool RegularEnemy::collisionCheck(LaserShooter & playerLaser)
{
	bool hasCollided = false;

	if (this->enemySprite.getGlobalBounds().intersects(playerLaser.getGlobalBounds()) && this->isAlive() && this->isLowest)
	{
		EnemyEntity::loseLife();
		this->collisionSound.play();
		playerLaser.stopShooting();
		hasCollided = true;
	}

	return hasCollided;
}

LaserShooter & RegularEnemy::getLaserPtr() const
{
	return *this->enemyLaser;
}

sf::Sprite & RegularEnemy::getSpritePtr()
{
	return this->enemySprite;
}

bool RegularEnemy::moveLeft(float deltatime, float speed)
{
	bool continueMovement = true;
	sf::Vector2f direction(-1.0f, 0.0f);

	if (EnemyEntity::isAlive() && !(this->enemySprite.getPosition().x < (this->width / 9.0f)))
	{
		this->enemySprite.move(direction * speed * deltatime);
	}
	else if (EnemyEntity::isAlive() && (this->enemySprite.getPosition().x <= (this->width / 9.0f)))
	{
		continueMovement = false;
	}

	return continueMovement;
}

bool RegularEnemy::moveRight(float deltatime, float speed)
{
	bool continueMovement = true;
	sf::Vector2f direction(1.0f, 0.0f);

	if (EnemyEntity::isAlive() && !(this->enemySprite.getPosition().x > (this->width - (this->width / 9.0f) - this->enemySprite.getGlobalBounds().width)))
	{
		this->enemySprite.move(direction * speed * deltatime);
	}
	else if (EnemyEntity::isAlive() && (this->enemySprite.getPosition().x >= (this->width - (this->width / 9.0f) - this->enemySprite.getGlobalBounds().width)))
	{
		continueMovement = false;
	}
	
	return continueMovement;
}

bool RegularEnemy::moveDown(float deltatime, float speed)
{
	bool continueMovement = true;

	sf::Vector2f direction(0.0f, 10.0f);

	if (EnemyEntity::isAlive() && !(this->enemySprite.getPosition().y > (this->height * 0.7f - this->enemySprite.getGlobalBounds().height)))
	{
		this->enemySprite.move(direction);
	}
	else if (EnemyEntity::isAlive() && (this->enemySprite.getPosition().y >= (this->height * 0.7f - this->enemySprite.getGlobalBounds().height)))
	{
		continueMovement = false;
	}
	
	return continueMovement;
}
