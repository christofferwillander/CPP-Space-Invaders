#include "HighScoreList.h"
#include <fstream>
#include <iostream>

void HighScoreList::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	for (int i = 0; i < 5; i++)
	{
		target.draw(this->guidanceTexts[i]);
	}

	for (int i = 0; i < 10; i++)
	{
		if (this->scores[i] > 0)
		{
			target.draw(this->rankingText[i]);
			target.draw(this->scoresText[i]);
			target.draw(this->namesText[i]);
		}
	}
}

HighScoreList::HighScoreList(float width, float height)
{
	int tempScore = -1;
	this->nrOfScores = 0;

	std::ifstream inFile;
	std::ofstream outFile;

	inFile.open("../Resources/data/highScore.dat"); // Open inFile

	if (inFile.fail()) // If file could not be found - create it with placeholder content
	{
		outFile.open("../Resources/data/highScore.dat");

		for (int i = 0; i < 10; i++)
		{
			outFile << 0 << std::endl; //Placeholder for score
			outFile << "Empty\n"; // Placeholder for name
		}

		outFile.close();

		inFile.open("../Resources/data/highScore.dat"); // Re-open inFile
	}

	if (!this->font.loadFromFile("../Resources/fonts/space_invaders.ttf"))
	{
		std::cout << "Font was not found" << std::endl;
		system("pause");
	}

	for (int i = 0; i < 10; i++)
	{
		this->scores[i] = 0;
		this->names[i] = "Empty\n";

		this->scoresText[i].setFont(this->font);
		this->scoresText[i].setCharacterSize(15);
		this->scoresText[i].setPosition((width * 0.45f), (height / 3.0f) + (i * (height * 0.05f)));

		this->namesText[i].setFont(this->font);
		this->namesText[i].setCharacterSize(15);
		this->namesText[i].setPosition((width * 0.79f), (height / 3.0f) + (i * (height * 0.05f)));

		this->rankingText[i].setFont(this->font);
		this->rankingText[i].setCharacterSize(15);
		this->rankingText[i].setPosition((width * 0.12f), (height / 3.0f) + (i * (height * 0.05f)));
		this->rankingText[i].setString(std::to_string(i + 1) + ".");

		if (i < 3)
		{
			this->guidanceTexts[i].setFont(this->font);
			this->guidanceTexts[i].setCharacterSize(20);
		}
		else if (i == 3)
		{
			this->guidanceTexts[i].setFont(this->font);
			this->guidanceTexts[i].setCharacterSize(35);
			this->guidanceTexts[i].setFillColor(sf::Color::Yellow);
			this->guidanceTexts[i].setPosition(sf::Vector2f(140.0f, 50.0f));
			this->guidanceTexts[i].setString("Top Defenders");
		}
		else if (i == 4)
		{
			this->guidanceTexts[i].setFont(this->font);
			this->guidanceTexts[i].setCharacterSize(15);
			this->guidanceTexts[i].setPosition(sf::Vector2f(160.0f, 540.0f));
			this->guidanceTexts[i].setString("Press space to go to main menu");
		}
	}

	this->guidanceTexts[0].setString("RANK");
	this->guidanceTexts[0].setPosition((width / 6.0f) - (this->guidanceTexts[0].getGlobalBounds().width / 2.0f), (height / 4.0f));
	this->guidanceTexts[1].setString("SCORE");
	this->guidanceTexts[1].setPosition(3.0f * (width / 6.0f)  - (this->guidanceTexts[1].getGlobalBounds().width / 2.0f), (height / 4.0f));
	this->guidanceTexts[2].setString("NAME");
	this->guidanceTexts[2].setPosition(5.0f * (width / 6.0f) - (this->guidanceTexts[2].getGlobalBounds().width / 2.0f), (height / 4.0f));

	for (int i = 0; i < 10 && tempScore != 0; i++)
	{
		inFile >> tempScore;

		if (tempScore > 0)
		{
			this->scores[i] = tempScore;
			inFile.ignore();
			std::getline(inFile, this->names[i]);
			this->namesText[i].setString(this->names[i]);
			this->nrOfScores++;
			this->scoresText[i].setString(std::to_string(this->scores[i]));
		}
	}

	inFile.close();
}

HighScoreList::HighScoreList(const HighScoreList & origObj)
{
	this->nrOfScores = origObj.nrOfScores;
	this->font = origObj.font;

	for (int i = 0; i < 10; i++)
	{
		this->scores[i] = origObj.scores[i];
		this->names[i] = origObj.names[i];
		this->scoresText[i] = origObj.scoresText[i];
		this->namesText[i] = origObj.namesText[i];
		this->rankingText[i] = origObj.rankingText[i];

		if (i < 5)
		{
			this->guidanceTexts[i] = origObj.guidanceTexts[i];
		}
	}
}

HighScoreList & HighScoreList::operator=(const HighScoreList & origObj)
{
	if (this != &origObj)
	{
		this->nrOfScores = origObj.nrOfScores;
		this->font = origObj.font;

		for (int i = 0; i < 10; i++)
		{
			this->scores[i] = origObj.scores[i];
			this->names[i] = origObj.names[i];
			this->scoresText[i] = origObj.scoresText[i];
			this->namesText[i] = origObj.namesText[i];
			this->rankingText[i] = origObj.rankingText[i];

			if (i < 5)
			{
				this->guidanceTexts[i] = origObj.guidanceTexts[i];
			}
		}
	}

	return *this;
}

HighScoreList::~HighScoreList()
{

}

void HighScoreList::addHighScore(int score)
{
	bool isGreater = true;

	std::string name = "";

	std::ofstream outFile;

	if (this->nrOfScores < 10)
	{
		this->nrOfScores++;
	}

	std::cout << "Enter your initials (max 3 characters): ";
	std::cin >> name;

	for (int i = this->nrOfScores - 1; i >= 0 && isGreater; i--)
	{
		if (score > this->scores[i] && i < 9)
		{
			this->scores[i + 1] = this->scores[i];
			this->names[i + 1] = this->names[i];
			this->scoresText[i + 1].setString(std::to_string(this->scores[i]));
			this->namesText[i + 1].setString(this->names[i]);

			this->scores[i] = score;
			this->names[i] = name;
			this->scoresText[i].setString(std::to_string(score));
			this->namesText[i].setString(name);
		}
		else if (score > this->scores[i] && i == 9)
		{
			this->scores[i] = score;
			this->names[i] = name;
			this->scoresText[i].setString(std::to_string(score));
			this->namesText[i].setString(name);
		}
		else if (score < this->scores[i])
		{
			isGreater = false;
		}
	}

	outFile.open("../Resources/data/highScore.dat");

	for (int i = 0; i < 10; i++)
	{
		if (i < this->nrOfScores)
		{
			outFile << this->scores[i] << std::endl;
			outFile << this->names[i] << std::endl;
		}
		else
		{
			outFile << this->scores[i] << std::endl;
			outFile << this->names[i];
		}
	}

	outFile.close();
}

int HighScoreList::getHighestScore() const
{
	return this->scores[0];
}

int HighScoreList::getLowestScore() const
{
	return this->scores[9];
}
