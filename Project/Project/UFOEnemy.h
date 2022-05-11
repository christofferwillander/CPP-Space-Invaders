#ifndef UFOENEMY_H
#define UFOENEMY_H
#include <SFML\Audio.hpp>
#include "EnemyEntity.h"

class UFOEnemy:public EnemyEntity
{
public:
	void Update(float deltatime);
	void startMovement();
	void stopMovement();
	bool collisionCheck(LaserShooter &playerLaser);

private:
	bool move;
	float enemySpeed;
	float width;
	float height;
	sf::Clock clock;
	sf::Font font;
	sf::Sprite enemySprite;
	sf::Text scoring;
	sf::SoundBuffer ufoFlyingSoundBuffer;
	sf::Sound ufoFlyingSound;
	sf::SoundBuffer ufoCollisionSoundBuffer;
	sf::Sound ufoCollisionSound;

	void draw(sf::RenderTarget &target, sf::RenderStates states) const;

public:
	UFOEnemy(sf::Texture &texture, float xPos = 600.0f, float yPos = 600.0f, int pointValue = 0);
	UFOEnemy(const UFOEnemy &origObj);
	UFOEnemy& operator = (const UFOEnemy &origObj);
	virtual ~UFOEnemy();
};

#endif