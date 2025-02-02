export module Drawable;

import Globals;
import Base;

// inherit from it in your object if your object 
// should be drawn on the screen 
// and define what is supposed to be drawn
export class Drawable : public virtual Base {
public:
	virtual void drawObject() {
		// correctpos
		try {
			correctPosition(this->getObject<sf::RectangleShape>());
			window->draw(*this->getObject<sf::RectangleShape>());
			return;
		} catch (const std::bad_variant_access& e) {} //ignore

		try {
			correctPosition(this->getObject<sf::CircleShape>());
			window->draw(*this->getObject<sf::CircleShape>());
			return;
		} catch (const std::bad_variant_access& e) {} //ignore

		try {
			correctPosition_sprite(this->getObject<sf::Sprite>());
			window->draw(*this->getObject<sf::Sprite>());
			return;
		} catch (const std::bad_variant_access& e) {} //ignore

	};
};