#ifndef MENU_H
#define MENU_H
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>

class Menu:public sf::Drawable
{
public:
	static const int ENTRY_AMOUNT = 3;
	void moveUp();
	void moveDown();
	int menuSelect();

private:
	int markedItem;
	sf::Texture menuTexture;
	sf::Sprite menuSprite;
	sf::Font font;
	sf::Text menuEntry[ENTRY_AMOUNT];
	sf::SoundBuffer menuMovementSoundBuffer;
	sf::Sound menuMovementSound;
	sf::SoundBuffer menuSelectionSoundBuffer;
	sf::Sound menuSelectionSound;

	void draw(sf::RenderTarget &target, sf::RenderStates state) const;

public:
	Menu(float width = 600.0f, float height = 600.0f);
	Menu(const Menu &origObj);
	Menu& operator = (const Menu &origObj);
	virtual ~Menu();
};

#endif