#ifndef LASERSHOOTER_H
#define LASERSHOOTER_H
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>

class LaserShooter:public sf::Drawable
{
public:
	void Update(float deltatime);
	void shoot(float entityPosX, float entityPosY);
	void stopShooting();
	void setEnemyType();
	bool isShooting() const;
	sf::FloatRect getGlobalBounds() const;

private:
	int type;
	float width;
	float height;
	float projectileSpeed;
	sf::Texture projectileTexture;
	sf::Sprite projectileSprite;
	sf::SoundBuffer shootingSoundBuffer;
	sf::Sound shootingSound;

	void draw(sf::RenderTarget &target, sf::RenderStates state) const;
	
public:
	LaserShooter(float width = 600.0f, float height = 600.0f);
	LaserShooter(const LaserShooter &origObj);
	LaserShooter& operator = (const LaserShooter &origObj);
	virtual ~LaserShooter();
};

#endif
