#include "EnemyHandler.h"
#include <iostream>
#include <ctime>

void EnemyHandler::stopAction() const
{
	UFOEnemy *enemyPtr = nullptr;

	for (int i = 0; i < this->enemyAmount; i++)
	{
		enemyPtr = dynamic_cast <UFOEnemy*> (this->enemies[i]);

		if (enemyPtr != nullptr)
		{
			enemyPtr->stopMovement();
		}
	}
}

void EnemyHandler::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	for (int i = 0; i < this->enemyAmount; i++)
	{
		target.draw(*this->enemies[i]);
	}
}

EnemyHandler::EnemyHandler(float width, float height)
{
	this->width = width;
	this->height = height;
	this->enemies = new EnemyEntity*[this->enemyCapacity];
	this->enemySpeed = 2.0f;
	this->shootCount = 5;

	this->moveLeft = false;
	this->moveRight = true;
	this->moveDown = true;

	sf::String texturePath = "../Resources/images/enemies_sheet.png";

	if (!this->enemyTexture.loadFromFile(texturePath))
	{
		std::cout << "Texture file not found" << std::endl;
		system("pause");
	}

	this->addRegularEnemies();
	this->addUFO();
}

EnemyHandler::EnemyHandler(const EnemyHandler & origObj)
{
	this->width = origObj.width;
	this->height = origObj.height;
	this->enemySpeed = origObj.enemySpeed;
	this->moveLeft = origObj.moveLeft;
	this->moveRight = origObj.moveRight;
	this->moveDown = origObj.moveDown;
	this->enemyAmount = origObj.enemyAmount;
	this->shootCount = origObj.shootCount;
	this->clock = origObj.clock;
	this->enemyTexture = origObj.enemyTexture;

	RegularEnemy *regEnemyPtr = nullptr;
	UFOEnemy *UFOEnemyPtr = nullptr;

	this->enemies = new EnemyEntity*[origObj.enemyCapacity];

	for (int i = 0; i < origObj.enemyAmount; i++)
	{
		regEnemyPtr = dynamic_cast <RegularEnemy*> (origObj.enemies[i]);

		if (regEnemyPtr != nullptr)
		{
			this->enemies[i] = new RegularEnemy(*regEnemyPtr);
		}
		else
		{
			UFOEnemyPtr = dynamic_cast <UFOEnemy*> (origObj.enemies[i]);

			if (UFOEnemyPtr != nullptr)
			{
				this->enemies[i] = new UFOEnemy(*UFOEnemyPtr);
			}
		}
	}
}

EnemyHandler & EnemyHandler::operator=(const EnemyHandler & origObj)
{
	if (this != &origObj)
	{
		for (int i = 0; i < this->enemyAmount; i++)
		{
			delete this->enemies[i];
		}

		delete[] this->enemies;

		this->width = origObj.width;
		this->height = origObj.height;
		this->enemySpeed = origObj.enemySpeed;
		this->moveLeft = origObj.moveLeft;
		this->moveRight = origObj.moveRight;
		this->moveDown = origObj.moveDown;
		this->enemyAmount = origObj.enemyAmount;
		this->shootCount = origObj.shootCount;
		this->clock = origObj.clock;
		this->enemyTexture = origObj.enemyTexture;

		RegularEnemy *regEnemyPtr = nullptr;
		UFOEnemy *UFOEnemyPtr = nullptr;

		this->enemies = new EnemyEntity*[origObj.enemyCapacity];

		for (int i = 0; i < origObj.enemyAmount; i++)
		{
			regEnemyPtr = dynamic_cast <RegularEnemy*> (origObj.enemies[i]);

			if (regEnemyPtr != nullptr)
			{
				this->enemies[i] = new RegularEnemy(*regEnemyPtr);
			}
			else
			{
				UFOEnemyPtr = dynamic_cast <UFOEnemy*> (origObj.enemies[i]);

				if (UFOEnemyPtr != nullptr)
				{
					this->enemies[i] = new UFOEnemy(*UFOEnemyPtr);
				}
			}
		}
	}

	return *this;
}

EnemyHandler::~EnemyHandler()
{
	for (int i = 0; i < this->enemyAmount; i++)
	{
		delete this->enemies[i];
	}

	delete[] this->enemies;
}

void EnemyHandler::Update(float deltatime)
{
	srand(static_cast <int> (time(NULL)));
	int randomNr1 = rand() % 30 + 1;


	UFOEnemy *UFOEnemyPtr = nullptr;
	RegularEnemy *regEnemyPtr = nullptr;

	
	int randomNr2 = 0;

	if (this->clock.getElapsedTime().asSeconds() >= 10.0 && this->enemySpeed <= 30.0f)
	{
		this->enemySpeed += 1.0f;

		if (this->shootCount < 25 && this->enemySpeed > 10.0f)
		{
			this->shootCount +=	1;
		}

		this->clock.restart();
	}

	for (int i = 0; i < this->enemyAmount; i++)
	{
		this->enemies[i]->Update(deltatime);
	}

	if (randomNr1 == 15)
	{
		for (int i = this->enemyAmount - 1; i >= 0 && UFOEnemyPtr == nullptr; i--)
		{
			UFOEnemyPtr = dynamic_cast <UFOEnemy*> (this->enemies[i]);
			if (UFOEnemyPtr != nullptr)
			{
				UFOEnemyPtr->startMovement();
			}
		}
	}
	
	for (int i = 0; i < this->shootCount; i++)
	{
		randomNr2 = (rand() % this->enemyAmount);
		regEnemyPtr = dynamic_cast <RegularEnemy*> (this->enemies[randomNr2]);
		
		if (regEnemyPtr != nullptr)
		{
			regEnemyPtr->shoot();
		}
	}

	this->moveEnemies(deltatime);
}

void EnemyHandler::addUFO()
{
	if (this->enemyAmount != this->enemyCapacity)
	{
		this->enemies[this->enemyAmount] = new UFOEnemy(this->enemyTexture, this->width, this->height, 0);
		this->enemyAmount++;
	}
}

void EnemyHandler::addRegularEnemies()
{
	RegularEnemy *enemyPtr = nullptr;

	if (this->enemyAmount + 55 < this->enemyCapacity)
	{
		for (int i = 0; i < 55; i++)
		{
			if (i < 11)
			{
				this->enemies[this->enemyAmount++] = new RegularEnemy(this->enemyTexture, (this->width / 7.0f) + (i * 40.0f), (this->height / 5.0f) + (40.0f * 0.0f), this->width, this->height, 30, 4);
			}
			else if (i >= 11 && i < 22)
			{
				this->enemies[this->enemyAmount++] = new RegularEnemy(this->enemyTexture, (this->width / 7.0f) + ((i - 11) * 40.0f), (this->height / 5.0f) + (40.0f * 1.0f), this->width, this->height, 20, 5);
			}
			else if (i >= 22 && i < 33)
			{
				this->enemies[this->enemyAmount++] = new RegularEnemy(this->enemyTexture, (this->width / 7.0f) + ((i - 22) * 40.0f), (this->height / 5.0f) + (40.0f * 2.0f), this->width, this->height, 20, 5);
			}
			else if (i >= 33 && i < 44)
			{
				this->enemies[this->enemyAmount++] = new RegularEnemy(this->enemyTexture, (this->width / 7.0f) + ((i - 33) * 40.0f), (this->height / 5.0f) + (40.0f * 3.0f), this->width, this->height, 10, 2);
			}
			else if (i >= 44 && i < 55)
			{
				this->enemies[this->enemyAmount++] = new RegularEnemy(this->enemyTexture, (this->width / 7.0f) + ((i - 44) * 40.0f), (this->height / 5.0f) + (40.0f * 4.0f), this->width, this->height, 10, 2);
				enemyPtr = dynamic_cast <RegularEnemy*> (this->enemies[(this->enemyAmount - 1)]);
				enemyPtr->setLowest(true);
			}
		}
	}
}

void EnemyHandler::moveEnemies(float deltatime)
{
	RegularEnemy *enemyPtr = nullptr;

	for (int i = 0; i < this->enemyAmount; i++)
	{
		enemyPtr = dynamic_cast <RegularEnemy*> (this->enemies[i]);

		if (enemyPtr != nullptr)
		{
			if (this->moveLeft == true)
			{
				this->moveLeft = enemyPtr->moveLeft(deltatime, this->enemySpeed);

				if (!this->moveLeft)
				{
					for (int i = 0; i < this->enemyAmount; i++)
					{
						enemyPtr = dynamic_cast <RegularEnemy*> (this->enemies[i]);
						
						if (enemyPtr != nullptr && this->moveDown)
						{
							this->moveDown = enemyPtr->moveDown(deltatime, this->enemySpeed);
						}
					}

					this->moveRight = true;
				}
			}
			else if (this->moveRight == true)
			{
				this->moveRight = enemyPtr->moveRight(deltatime, this->enemySpeed);

				if (!this->moveRight)
				{
					for (int i = 0; i < this->enemyAmount; i++)
					{
						enemyPtr = dynamic_cast <RegularEnemy*> (this->enemies[i]);

						if (enemyPtr != nullptr && this->moveDown)
						{
							this->moveDown = enemyPtr->moveDown(deltatime, this->enemySpeed);
						}
					}

					this->moveLeft = true;
				}
			}
		}
	}
}

void EnemyHandler::collisionCheck(LaserShooter & playerLaser, int & scorePtr) const
{
	RegularEnemy *enemyPtr;

	for (int i = 0; i < (this->enemyAmount) && playerLaser.isShooting(); i++)
	{
		if (this->enemies[i]->collisionCheck(playerLaser))
		{
			scorePtr += this->enemies[i]->getPointValue();
			
			if (i > 10)
			{
				enemyPtr = dynamic_cast <RegularEnemy*> (this->enemies[i - 11]);
				enemyPtr->setLowest(true);
			}
		}
		
	}
}

void EnemyHandler::newRound()
{
	RegularEnemy *RegularEnemyPtr = nullptr;
	UFOEnemy *UFOEnemyPtr = nullptr;

	for (int i = 0; i < this->enemyAmount; i++)
	{
		RegularEnemyPtr = dynamic_cast <RegularEnemy*> (this->enemies[i]);
		UFOEnemyPtr = dynamic_cast <UFOEnemy*> (this->enemies[i]);

		if (i < this->enemyAmount - 12 && RegularEnemyPtr != nullptr)
		{
			RegularEnemyPtr->setLowest(false);
		}
		else if (i >= this->enemyAmount - 12 && RegularEnemyPtr != nullptr)
		{
			RegularEnemyPtr->setLowest(true);
		}

		if (RegularEnemyPtr != nullptr)
		{
			RegularEnemyPtr->reset();
		}

		this->moveLeft = false;
		this->moveRight = true;

		if (UFOEnemyPtr != nullptr)
		{
			UFOEnemyPtr->stopMovement();
		}
	}
}

void EnemyHandler::resetAll()
{
	this->newRound();
	this->enemySpeed = 2.0f;
	this->shootCount = 5;
}

bool EnemyHandler::anyAlive() const
{
	bool anyAlive = false;

	for (int i = 0; i < this->enemyAmount - 1; i++)
	{
		if (this->enemies[i]->isAlive())
		{
			anyAlive = true;
		}
	}

	return anyAlive;
}

LaserShooter & EnemyHandler::getLaserPtr(int enemyIndex) const
{
	RegularEnemy *enemyPtr = nullptr;
	
	if (enemyIndex < this->enemyAmount)
	{
		enemyPtr = dynamic_cast <RegularEnemy*> (this->enemies[enemyIndex]);
	}

	return enemyPtr->getLaserPtr();
}

