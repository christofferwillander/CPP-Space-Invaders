#include "Menu.h"
#include <iostream>

void Menu::draw(sf::RenderTarget & target, sf::RenderStates state) const
{
	for (int i = 0; i < this->ENTRY_AMOUNT; i++)
	{
		target.draw(this->menuEntry[i]);
	}

	target.draw(this->menuSprite);
}

Menu::Menu(float width, float height)
{
	this->markedItem = 0;

	if (!this->menuTexture.loadFromFile("../Resources/images/logo.png"))
	{
		std::cout << "Texture was not found" << std::endl;
		system("pause");
	}

	this->menuSprite.setTexture(this->menuTexture);
	this->menuSprite.setPosition((width / 2.0f) - (this->menuSprite.getGlobalBounds().width / 2.0f), (height / 8.5f));

	if (!this->font.loadFromFile("../Resources/fonts/space_invaders.ttf"))
	{
		std::cout << "Font was not found" << std::endl;
		system("pause");
	}

	if (!this->menuMovementSoundBuffer.loadFromFile("../Resources/fx/menu_movement.wav"))
	{
		std::cout << "Sound was not found" << std::endl;
		system("pause");
	}

	if (!this->menuSelectionSoundBuffer.loadFromFile("../Resources/fx/menu_selection.wav"))
	{
		std::cout << "Sound was not found" << std::endl;
		system("pause");
	}
	
	this->menuEntry[0].setFont(this->font);
	this->menuEntry[0].setCharacterSize(32);
	this->menuEntry[0].setFillColor(sf::Color::Yellow);

	for (int i = 1; i < this->ENTRY_AMOUNT; i++)
	{
		this->menuEntry[i].setFont(font);
		this->menuEntry[i].setFillColor(sf::Color::White);
	}

	this->menuEntry[0].setString("Start Game");
	this->menuEntry[0].setPosition((width / 2.0f) - (this->menuEntry[0].getGlobalBounds().width / 2.0f), (height / this->ENTRY_AMOUNT + 1) + (height / 8.0f));
	this->menuEntry[1].setString("High Score");
	this->menuEntry[1].setPosition((width / 2.0f) - (this->menuEntry[1].getGlobalBounds().width / 2.0f), (height / this->ENTRY_AMOUNT + 1) + (height / 4.0f));
	this->menuEntry[2].setString("Quit");
	this->menuEntry[2].setPosition((width / 2.0f) - (this->menuEntry[2].getGlobalBounds().width / 2.0f), (height / this->ENTRY_AMOUNT + 1) + (height / 2.7f));

	this->menuMovementSound.setBuffer(this->menuMovementSoundBuffer);
	this->menuSelectionSound.setBuffer(this->menuSelectionSoundBuffer);
}

Menu::Menu(const Menu & origObj)
{
	this->markedItem = origObj.markedItem;
	this->menuTexture = origObj.menuTexture;
	this->menuSprite = origObj.menuSprite;
	this->font = origObj.font;
	this->menuMovementSoundBuffer = origObj.menuMovementSoundBuffer;
	this->menuMovementSound = origObj.menuMovementSound;
	this->menuSelectionSoundBuffer = origObj.menuMovementSoundBuffer;
	this->menuSelectionSound = origObj.menuSelectionSound;

	for (int i = 0; i < origObj.ENTRY_AMOUNT; i++)
	{
		this->menuEntry[i] = origObj.menuEntry[i];
	}
}

Menu & Menu::operator=(const Menu & origObj)
{
	if (this != &origObj)
	{
		this->markedItem = origObj.markedItem;
		this->menuTexture = origObj.menuTexture;
		this->menuSprite = origObj.menuSprite;
		this->font = origObj.font;
		this->menuMovementSoundBuffer = origObj.menuMovementSoundBuffer;
		this->menuMovementSound = origObj.menuMovementSound;
		this->menuSelectionSoundBuffer = origObj.menuMovementSoundBuffer;
		this->menuSelectionSound = origObj.menuSelectionSound;

		for (int i = 0; i < origObj.ENTRY_AMOUNT; i++)
		{
			this->menuEntry[i] = origObj.menuEntry[i];
		}
	}

	return *this;
}

Menu::~Menu()
{

}

void Menu::moveUp()
{
	if ((this->markedItem - 1) >= 0)
	{
		this->menuEntry[this->markedItem].setFillColor(sf::Color::White);
		this->menuEntry[this->markedItem].setCharacterSize(30);
		this->markedItem = this->markedItem - 1;
		this->menuEntry[this->markedItem].setFillColor(sf::Color::Yellow);
		this->menuEntry[this->markedItem].setCharacterSize(32);
		this->menuMovementSound.play();
	}
}

void Menu::moveDown()
{
	if (this->markedItem + 1 < this->ENTRY_AMOUNT)
	{
		this->menuEntry[this->markedItem].setFillColor(sf::Color::White);
		this->menuEntry[this->markedItem].setCharacterSize(30);
		this->markedItem = this->markedItem + 1;
		this->menuEntry[this->markedItem].setFillColor(sf::Color::Yellow);
		this->menuEntry[this->markedItem].setCharacterSize(32);
		this->menuMovementSound.play();
	}
}

int Menu::menuSelect()
{
	int markedItemTemp = this->markedItem;
	this->markedItem = 0;

	this->menuEntry[markedItemTemp].setFillColor(sf::Color::White);
	this->menuEntry[markedItemTemp].setCharacterSize(30);
	this->menuEntry[0].setFillColor(sf::Color::Yellow);
	this->menuEntry[0].setCharacterSize(32);
	this->menuSelectionSound.play();

	return markedItemTemp;
}

