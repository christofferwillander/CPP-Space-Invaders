#ifndef REGULARENEMY_H
#define REGULARENEMY_H
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include "EnemyEntity.h"

class RegularEnemy:public EnemyEntity 
{
public:
	void Update(float deltatime);
	void setLowest(bool isLowest);
	void shoot();
	void reset();
	bool moveLeft(float deltatime, float speed);
	bool moveRight(float deltatime, float speed);
	bool moveDown(float deltatime, float speed);
	bool collisionCheck(LaserShooter &playerLaser);
	LaserShooter& getLaserPtr() const;
	sf::Sprite& getSpritePtr();

private:
	float width;
	float height;
	bool isLowest;
	sf::Vector2f origPos;
	sf::Clock clock;
	sf::Sprite enemySprite;
	sf::SoundBuffer collisionSoundBuffer;
	sf::Sound collisionSound;
	LaserShooter *enemyLaser;

	void draw(sf::RenderTarget &target, sf::RenderStates states) const;

public:
	RegularEnemy(sf::Texture &texture, float xPos = 0.0f, float yPos = 0.0f, float width = 600.0f, float height = 600.0f, int pointValue = 10, int spriteID = 1);
	RegularEnemy(const RegularEnemy &origObj);
	RegularEnemy& operator = (const RegularEnemy &origObj);
	virtual ~RegularEnemy();
};

#endif
