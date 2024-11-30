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
	Rectangle(sf::Vector2u position, sf::Vector2u size, sf::Color color, unsigned int bound)
		: Collidable(size, bound)
	{
		set(typeid(this).raw_name(), position);

		_body.setPosition(_position.lock()->getPosition());
		_body.setSize(sf::Vector2f(size.x * __graphPointDistance, size.y * __graphPointDistance));
		_body.setFillColor(color); 

	}

	void drawObject() {
		_body.setPosition(_position.lock()->getPosition());
		window->draw(_body);
	}

	void afterCollision() {
		this->setMoveDirection(sf::Vector2u(0, 0));
	}

};