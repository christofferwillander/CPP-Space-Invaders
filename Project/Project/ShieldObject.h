#ifndef SHIELDOBJECT_H
#define SHIELDOBJECT_H
#include <SFML\Graphics.hpp>
#include "LaserShooter.h"

class ShieldObject:public sf::Drawable
{
public:
	void collisionCheck(LaserShooter &entityLaser);
	void reset();

private:
	bool isBlockHit[200];
	sf::RectangleShape blocks[200];
	int blockAmount;

	void draw(sf::RenderTarget &target, sf::RenderStates states) const;

public:
	ShieldObject(float xPos = 0.0f, float yPos = 0.0f);
	ShieldObject(const ShieldObject &origObj);
	ShieldObject& operator = (const ShieldObject &origObj);
	~ShieldObject();
};

#endif