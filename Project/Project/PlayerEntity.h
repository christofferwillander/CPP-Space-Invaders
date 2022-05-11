#ifndef PLAYERENTITY_H
#define PLAYERENTITY_H
#include "LaserShooter.h"
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>

class PlayerEntity:public sf::Drawable
{
public:
	void Update(float deltatime);
	int getScore() const;
	int getLives() const;
	bool isAlive() const;
	bool isShooting() const;
	bool collisionCheck(LaserShooter &enemyLaser);
	void nextRound();
	void reset();
	PlayerEntity& getPlayerPtr();
	LaserShooter& getLaserPtr() const;
	int& getScorePtr();

private:
	int score;
	int lives;
	float pSpeed;
	float width;
	float height;
	bool extraLifeUsed;
	sf::Texture pTexture;
	sf::Sprite pSprite;
	sf::SoundBuffer loseLifeSoundBuffer;
	sf::Sound loseLifeSound;
	sf::SoundBuffer lifeUnlockedSoundBuffer;
	sf::Sound lifeUnlockedSound;
	LaserShooter *playerLaser;
	
	void draw(sf::RenderTarget &target, sf::RenderStates state) const;

public:
	PlayerEntity(float width, float height);
	PlayerEntity(const PlayerEntity &origObj);
	PlayerEntity& operator = (const PlayerEntity &origObj);
	virtual ~PlayerEntity();
};

#endif
