#include "LaserShooter.h"
#include <iostream>

void LaserShooter::draw(sf::RenderTarget & target, sf::RenderStates state) const
{
	target.draw(this->projectileSprite);
}

LaserShooter::LaserShooter(float width, float height)
{
	this->width = width;
	this->height = height;
	this->projectileSpeed = 400.0f;
	this->type = 0;
	
	sf::String spritePath = "../Resources/images/projectile.png";

	if (!this->projectileTexture.loadFromFile(spritePath))
	{
		std::cout << "Could not load texture";
		system("pause");
	}

	if (!this->shootingSoundBuffer.loadFromFile("../Resources/fx/shoot.wav"))
	{
		std::cout << "Sound was not found" << std::endl;
		system("pause");
	}

	this->projectileSprite.setTexture(this->projectileTexture);
	this->projectileSprite.setPosition(-20.0f, 0.0f);

	this->shootingSound.setBuffer(this->shootingSoundBuffer);
}

LaserShooter::LaserShooter(const LaserShooter & origObj)
{
	this->type = origObj.type;
	this->width = origObj.width;
	this->height = origObj.height;
	this->projectileSpeed = origObj.projectileSpeed;
	this->projectileTexture = origObj.projectileTexture;
	this->projectileSprite = origObj.projectileSprite;
	this->shootingSoundBuffer = origObj.shootingSoundBuffer;
	this->shootingSound = origObj.shootingSound;
}

LaserShooter & LaserShooter::operator=(const LaserShooter & origObj)
{
	if (this != &origObj)
	{
		this->type = origObj.type;
		this->width = origObj.width;
		this->height = origObj.height;
		this->projectileSpeed = origObj.projectileSpeed;
		this->projectileTexture = origObj.projectileTexture;
		this->projectileSprite = origObj.projectileSprite;
		this->shootingSoundBuffer = origObj.shootingSoundBuffer;
		this->shootingSound = origObj.shootingSound;
	}

	return *this;
}

LaserShooter::~LaserShooter()
{

}

void LaserShooter::shoot(float entityPosX, float entityPosY)
{
	if (!this->isShooting() && this->type == 0)
	{
		this->projectileSprite.setPosition(entityPosX + 11.0f, entityPosY - 14.0f);
		this->shootingSound.play();
	}
	else if (!this->isShooting() && this->type == 1)
	{
		this->projectileSprite.setPosition(entityPosX + 15.0f, entityPosY + 29.0f);
	}
}

void LaserShooter::Update(float deltatime)
{
	sf::Vector2f direction(0.0f, 0.0f);
	
	if (this->type == 0)
	{
		direction.y = -1.0f;
	}
	else if (this->type == 1)
	{
		direction.y = 1.0f;
	}
	
	if (this->projectileSprite.getPosition().y <= this->height * (80.0f / this->height) && this->isShooting() && this->type == 0)
	{
		this->stopShooting();
	}
	else if (this->projectileSprite.getPosition().y >= (this->height - (this->height / 12.0f)) && this->isShooting() && this->type == 1)
	{
		this->stopShooting();
	}

	if (this->isShooting())
	{
		this->projectileSprite.move(direction * this->projectileSpeed * deltatime);
	}
}

bool LaserShooter::isShooting() const
{
	return (!(this->projectileSprite.getPosition().x == -20.0f && this->projectileSprite.getPosition().y == 0.0f));
}

void LaserShooter::stopShooting()
{
	this->projectileSprite.setPosition(-20.0f, 0.0f);
}

void LaserShooter::setEnemyType()
{
	this->type = 1;
	this->projectileSpeed = 300.0f;
	this->projectileSprite.rotate(180);
}

sf::FloatRect LaserShooter::getGlobalBounds() const
{
	return projectileSprite.getGlobalBounds();
}
