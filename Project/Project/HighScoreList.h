#ifndef HIGHSCORELIST_H
#define HIGHSCORELIST_H
#include <SFML\Graphics.hpp>

class HighScoreList:public sf::Drawable
{
public:
	void addHighScore(int score);
	int getHighestScore() const;
	int getLowestScore() const;

private:
	int nrOfScores;
	int scores[10];
	std::string names[10];
	sf::Text scoresText[10];
	sf::Text namesText[10];
	sf::Text rankingText[10];
	sf::Text guidanceTexts[5];
	sf::Font font;

	void draw(sf::RenderTarget &target, sf::RenderStates states) const;

public:
	HighScoreList(float width = 600.0f, float height = 600.0f);
	HighScoreList(const HighScoreList &origObj);
	HighScoreList& operator = (const HighScoreList &origObj);
	~HighScoreList();
};

#endif