export module Rectangle;

import Base;
import Drawable;
import Moveable;
import Eventable;
import Updateable;
import Collidable;

export class Rectangle : public virtual Base, public Drawable, public Moveable, public Collidable {
	sf::RectangleShape _body;

public:
	Rectangle(sf::Vector2u position, sf::Vector2u size, sf::Color color)
		: Base(position), Collidable(size)
	{

		_body.setPosition(_position.lock()->getPosition());
		_setSize(_body, size);
		_body.setFillColor(color); 

	}

	void drawObject() {
		_body.setPosition(_position.lock()->getPosition());
		window->draw(_body);
	}

};