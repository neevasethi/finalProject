#include "Button.h"
Button::Button() {
	hasBeenClicked = false;
}
Button::Button(const sf::Texture& texture) : sf::Sprite(texture) {
	hasBeenClicked = false;
}
void Button::setClickedStatusto(bool clicked) {
	hasBeenClicked = clicked;
}
bool Button::GetClickedStatus() {
	return hasBeenClicked;
}
