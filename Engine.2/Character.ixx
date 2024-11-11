export module Character;

import Base;
import Drawable;
import Moveable;
import Eventable;
import Updateable;
import Collidable;

export class Character : public virtual Base, public Drawable, public Moveable, public Eventable, public Collidable {
	sf::RectangleShape _body;

public:
	Character(sf::Vector2u position, sf::Vector2u size, sf::Color color)
		: Base(typeid(this).raw_name(), position), Collidable(size, 2)
	{

		_body.setPosition(_position.lock()->getPosition());
		_body.setSize(sf::Vector2f(size.x * __graphPointDistance, size.y * __graphPointDistance));
		_body.setFillColor(color);

		this->addKeyAssociation(sf::Keyboard::D, Functor(
			[this]() {
				this->setMoveDirection(sf::Vector2u(1, 0));
			}
		));
		this->addKeyAssociation(sf::Keyboard::A, Functor(
			[this]() {
				this->setMoveDirection(sf::Vector2u(-1, 0));
			}
		));
		this->addKeyAssociation(sf::Keyboard::W, Functor(
			[this]() {
				this->setMoveDirection(sf::Vector2u(0, -1));
			}
		));
		this->addKeyAssociation(sf::Keyboard::S, Functor(
			[this]() {
				this->setMoveDirection(sf::Vector2u(0, 1));
			}
		));
		
	}

	void drawObject() {
		_body.setPosition(_position.lock()->getPosition());
		window->draw(_body);
	}

};