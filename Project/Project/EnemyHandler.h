#ifndef ENEMYHANDLER_H
#define ENEMYHANDLER_H
#include <SFML\Graphics.hpp>
#include "EnemyEntity.h"
#include "RegularEnemy.h"
#include "UFOEnemy.h"

class EnemyHandler:public sf::Drawable
{
public:
	static const int enemyCapacity = 56;

	void Update(float deltatime);
	void collisionCheck(LaserShooter &playerLaser, int &scorePtr) const;
	void newRound();
	void resetAll();
	void stopAction() const;
	bool anyAlive() const;
	LaserShooter& getLaserPtr(int enemyIndex) const;

private:
	float width;
	float height;
	float enemySpeed;
	bool moveLeft;
	bool moveRight;
	bool moveDown;
	int enemyAmount;
	int shootCount;
	sf::Clock clock;
	sf::Texture enemyTexture;
	EnemyEntity* *enemies;

	void draw(sf::RenderTarget &target, sf::RenderStates states) const;
	void addUFO();
	void addRegularEnemies();
	void moveEnemies(float deltatime);

public:
	EnemyHandler(float width = 600.0f, float height = 600.0f);
	EnemyHandler(const EnemyHandler& origObj);
	EnemyHandler& operator = (const EnemyHandler& origObj);
	virtual ~EnemyHandler();
};

#endif