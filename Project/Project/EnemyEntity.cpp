#include "EnemyEntity.h"

EnemyEntity::EnemyEntity(sf::Texture &enemyTexture, int pointValue)
{
	this->pointValue = pointValue;
	this->enemyTexture = enemyTexture;
	this->alive = true;
}

EnemyEntity::EnemyEntity(const EnemyEntity & origObj)
{
	this->alive = origObj.alive;
	this->pointValue = origObj.pointValue;
	this->enemyTexture = origObj.enemyTexture;
}

EnemyEntity & EnemyEntity::operator=(const EnemyEntity & origObj)
{
	if (this != &origObj)
	{
		this->alive = origObj.alive;
		this->pointValue = origObj.pointValue;
		this->enemyTexture = origObj.enemyTexture;
	}

	return *this;
}

EnemyEntity::~EnemyEntity()
{

}

void EnemyEntity::setTexture(sf::Sprite &sprite, int spriteID) const
{
	sprite.setTexture(this->enemyTexture);

	if(spriteID == 1)
	sprite.setTextureRect(sf::IntRect(2, 1, 24, 16));
	if (spriteID == 2)
		sprite.setTextureRect(sf::IntRect(172, 2, 24, 16));
	if (spriteID == 3)
		sprite.setTextureRect(sf::IntRect(99, 1, 24, 16));
	if (spriteID == 4)
		sprite.setTextureRect(sf::IntRect(35, 1, 24, 16));
	if (spriteID == 5)
		sprite.setTextureRect(sf::IntRect(66, 1, 24, 16));
	if (spriteID == 6)
		sprite.setTextureRect(sf::IntRect(208, 0, 48, 21));
}

void EnemyEntity::setPointValue(int pointValue)
{
	this->pointValue = pointValue;
}

void EnemyEntity::setAlive()
{
	this->alive = true;
}

bool EnemyEntity::isAlive() const
{
	return this->alive;
}

void EnemyEntity::loseLife()
{
	this->alive = false;
}

int EnemyEntity::getPointValue() const
{
	return this->pointValue;
}
