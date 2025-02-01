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
			correctPosition(_object.get<sf::RectangleShape>());
			window->draw(*_object.get<sf::RectangleShape>());
			return;
		} catch (const std::bad_variant_access& e) {} //ignore

		try {
			correctPosition(_object.get<sf::CircleShape>());
			window->draw(*_object.get<sf::CircleShape>());
			return;
		} catch (const std::bad_variant_access& e) {} //ignore

		try {
			correctPosition_sprite(_object.get<sf::Sprite>());
			window->draw(*_object.get<sf::Sprite>());
			return;
		} catch (const std::bad_variant_access& e) {} //ignore

	};
};