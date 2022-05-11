#include "ShieldObject.h"

void ShieldObject::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	for (int i = 0; i < this->blockAmount; i++)
	{
		if (!this->isBlockHit[i])
		{
			target.draw(this->blocks[i]);
		}
	}
}

ShieldObject::ShieldObject(float xPos, float yPos)
{
	this->blockAmount = 0;

	for (int i = 0; i < 12; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			if (!(i > 6 && (j > 5 && j < 14)))
			{
				this->isBlockHit[this->blockAmount] = false;
				this->blocks[this->blockAmount].setSize(sf::Vector2f(3.0f, 3.0f));
				this->blocks[this->blockAmount].setPosition(sf::Vector2f(xPos + (3.0f * j), yPos + (3.0f * i)));
				this->blocks[this->blockAmount].setFillColor(sf::Color::Green);
				this->blockAmount++;
			}
		}
	}
}

ShieldObject::ShieldObject(const ShieldObject & origObj)
{
	this->blockAmount = origObj.blockAmount;

	for (int i = 0; i < 200; i++)
	{
		this->isBlockHit[i] = origObj.isBlockHit[i];
		this->blocks[i] = origObj.blocks[i];
	}
}

ShieldObject & ShieldObject::operator=(const ShieldObject & origObj)
{
	if (this != &origObj)
	{
		this->blockAmount = origObj.blockAmount;

		for (int i = 0; i < 200; i++)
		{
			this->isBlockHit[i] = origObj.isBlockHit[i];
			this->blocks[i] = origObj.blocks[i];
		}
	}

	return *this;
}

ShieldObject::~ShieldObject()
{

}

void ShieldObject::collisionCheck(LaserShooter & entityLaser)
{
	for (int i = 0; i < this->blockAmount; i++)
	{
		if (this->blocks[i].getGlobalBounds().intersects(entityLaser.getGlobalBounds()) && !this->isBlockHit[i])
		{
			this->isBlockHit[i] = true;
			entityLaser.stopShooting();
		}
	}
}

void ShieldObject::reset()
{
	for (int i = 0; i < 200; i++)
	{
		this->isBlockHit[i] = false;
	}
}
