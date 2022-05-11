#ifndef ENEMYENTITY_H
#define ENEMYENTITY_H
#include <SFML/Graphics.hpp>
#include "LaserShooter.h"

class EnemyEntity:public sf::Drawable
{
public:
	virtual void Update(float deltatime) = 0;
	virtual bool collisionCheck(LaserShooter &playerLaser) = 0;
	void setTexture(sf::Sprite &sprite, int spriteID) const;
	void setPointValue(int pointValue);
	void setAlive();
	void loseLife();
	bool isAlive() const;
	int getPointValue() const;

private:
	bool alive;
	int pointValue;
	sf::Texture enemyTexture;

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const = 0;

public:
	EnemyEntity(sf::Texture &enemyTexture, int pointValue = 10);
	EnemyEntity(const EnemyEntity &origObj);
	EnemyEntity& operator = (const EnemyEntity &origObj);
	virtual ~EnemyEntity();
};

#endif
