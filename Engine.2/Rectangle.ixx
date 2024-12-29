export module Rectangle;

import Base;
import Drawable;
import Moveable;
import Eventable;
import Updateable;
import Collidable;
import Deleteable;

export class Rectangle : public virtual Base, public Eventable, public Deleteable, public Drawable, public Collidable {
	sf::RectangleShape _body;

public:
	Rectangle(sf::Vector2u position, sf::Vector2u size, sf::Color color)
		: Base(position), Collidable(size)
	{
		correctPosition(_body);
		_setSize(_body, size);
		_body.setFillColor(color); 

		addKeyAssociation(sf::Keyboard::T, Functor(
			[this]() {
				deleteObject();
			}
		));

	}

	void drawObject() {
		correctPosition(_body);
		window->draw(_body);
	}

};