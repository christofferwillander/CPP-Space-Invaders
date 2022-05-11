#ifndef GAMEMAP_H
#define GAMEMAP_H
#include <SFML\Graphics.hpp>
#include "PlayerEntity.h"
#include "EnemyHandler.h"
#include "ShieldObject.h"

class GameMap:public sf::Drawable
{
public:
	void Update(float deltatime);
	void updateHighScore(int highScore);
	void resetAll() const;
	PlayerEntity& getPlayerPtr() const;

private:
	int highScore;
	float width;
	float height;
	sf::Font font;
	sf::Text scoreText[2];
	sf::Text livesText;
	sf::Text highScoreText[2];
	PlayerEntity *player;
	EnemyHandler *enemyHandler;
	ShieldObject *shields[4];

	void draw(sf::RenderTarget &target, sf::RenderStates state) const;

public:
	GameMap(float width, float height);
	GameMap(const GameMap &origObj);
	GameMap& operator = (const GameMap &origObj);
	virtual ~GameMap();
};

#endif