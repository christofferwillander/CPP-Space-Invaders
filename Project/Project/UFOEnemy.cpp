#include "UFOEnemy.h"
#include <iostream>

void UFOEnemy::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	if (EnemyEntity::isAlive())
	{
		target.draw(this->enemySprite);
	}
	else if (!EnemyEntity::isAlive())
	{
		target.draw(this->scoring);
	}
}

UFOEnemy::UFOEnemy(sf::Texture &texture, float width, float height, int pointValue)
:EnemyEntity(texture, pointValue)
{
	this->width = width;
	this->height = height;
	this->enemySpeed = 200.0f;
	this->move = false;

	this->enemySprite.setPosition(-50.0f, 0.0f);

	EnemyEntity::setTexture(this->enemySprite, 6);

	if (!this->font.loadFromFile("../Resources/fonts/space_invaders.ttf"))
	{
		std::cout << "Font was not found" << std::endl;
		system("pause");
	}

	if (!this->ufoFlyingSoundBuffer.loadFromFile("../Resources/fx/ufo_flying.wav"))
	{
		std::cout << "Sound was not found" << std::endl;
		system("pause");
	}

	if (!this->ufoCollisionSoundBuffer.loadFromFile("../Resources/fx/ufo_killed.wav"))
	{
		std::cout << "Sound was not found" << std::endl;
		system("pause");
	}

	this->scoring.setFont(this->font);
	this->scoring.setFillColor(sf::Color::Yellow);
	this->scoring.setCharacterSize(17);

	this->ufoFlyingSound.setBuffer(this->ufoFlyingSoundBuffer);
	this->ufoFlyingSound.setLoop(true);
	this->ufoCollisionSound.setBuffer(this->ufoCollisionSoundBuffer);
}

UFOEnemy::UFOEnemy(const UFOEnemy & origObj)
:EnemyEntity(origObj)
{
	this->move = origObj.move;
	this->enemySpeed = origObj.enemySpeed;
	this->width = origObj.width;
	this->height = origObj.height;
	this->clock = origObj.clock;
	this->font = origObj.font;
	this->enemySprite = origObj.enemySprite;
	this->scoring = origObj.scoring;
	this->ufoFlyingSoundBuffer = origObj.ufoFlyingSoundBuffer;
	this->ufoFlyingSound = origObj.ufoFlyingSound;
	this->ufoCollisionSoundBuffer = origObj.ufoCollisionSoundBuffer;
	this->ufoCollisionSound = origObj.ufoCollisionSound;
}

UFOEnemy & UFOEnemy::operator=(const UFOEnemy & origObj)
{
	if (this != &origObj)
	{
		EnemyEntity::operator=(origObj);
		this->move = origObj.move;
		this->enemySpeed = origObj.enemySpeed;
		this->width = origObj.width;
		this->height = origObj.height;
		this->clock = origObj.clock;
		this->font = origObj.font;
		this->enemySprite = origObj.enemySprite;
		this->scoring = origObj.scoring;
		this->ufoFlyingSoundBuffer = origObj.ufoFlyingSoundBuffer;
		this->ufoFlyingSound = origObj.ufoFlyingSound;
		this->ufoCollisionSoundBuffer = origObj.ufoCollisionSoundBuffer;
		this->ufoCollisionSound = origObj.ufoCollisionSound;
	}

	return *this;
}

UFOEnemy::~UFOEnemy()
{

}

void UFOEnemy::startMovement()
{
	if (!this->move && EnemyEntity::isAlive() && this->clock.getElapsedTime().asSeconds() > 10.0)
	{
		this->move = true;
		this->enemySprite.setPosition((this->width + 50.0f), (this->height / 7.5f));
		this->ufoFlyingSound.play();
	}
}

void UFOEnemy::stopMovement()
{
	this->move = false;
	this->enemySprite.setPosition(-50.0f, 0.0f);
	this->ufoFlyingSound.stop();
	this->clock.restart();
}

bool UFOEnemy::collisionCheck(LaserShooter & playerLaser)
{
	srand(static_cast <int> (time(NULL)));

	bool hasCollided = false;

	int randomNr = 0;
	int pointValues[4] = { 50, 100, 150, 300 };

	sf::Vector2f position(0.0f, (this->height / 7.5f));

	if (this->enemySprite.getGlobalBounds().intersects(playerLaser.getGlobalBounds()))
	{
		randomNr = rand() % 4;
		position.x = this->enemySprite.getPosition().x;

		this->scoring.setPosition(position);
		this->scoring.setString(std::to_string(pointValues[randomNr]));
		this->stopMovement();

		EnemyEntity::setPointValue(pointValues[randomNr]);
		EnemyEntity::loseLife();

		playerLaser.stopShooting();
		this->ufoCollisionSound.play();
		
		hasCollided = true;
	}

	return hasCollided;
}

void UFOEnemy::Update(float deltatime)
{
	sf::Vector2f direction(-1.0f, 0.0f);

	if (this->enemySprite.getPosition().x <= -100.0f && this->move)
	{
		this->stopMovement();
	}

	if (this->move)
	{
		this->enemySprite.move(direction * this->enemySpeed * deltatime);
	}

	if (!EnemyEntity::isAlive())
	{
		if (this->clock.getElapsedTime().asSeconds() >= 2 && this->clock.getElapsedTime().asSeconds() < 3)
		{
			EnemyEntity::setAlive();
		}
	}
}