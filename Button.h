#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "TextureManager.h"
class Button : public sf::Sprite
{
	bool hasBeenClicked;
public:
	Button();
	Button(const sf::Texture& texture);
	void setClickedStatusto(bool clicked);
	bool GetClickedStatus();

};

