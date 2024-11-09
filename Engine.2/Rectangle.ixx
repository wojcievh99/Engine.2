export module Rectangle;

import Base;
import Drawable;
import Moveable;
import Eventable;
import Updateable;

export class Rectangle : public virtual Base, public Drawable, public Moveable, public Eventable, public Updateable {
	sf::RectangleShape _body;
	std::vector<std::weak_ptr<GraphPoint>> _size;

public:
	Rectangle(sf::Vector2u position, sf::Vector2u size, sf::Color color)
		: Base(typeid(this).raw_name(), position)
	{
		for (unsigned int column = 0; column < size.y; column++) {
			for (unsigned int line = 0; line < size.x; line++) {
				_size.push_back(
					std::make_shared<GraphPoint>(
						sf::Vector2f(
							float(position.x + line) * __graphPointDistance,
							float(position.y + column) * __graphPointDistance
						),
						sf::Vector2u(position.x + line, position.y + column)
					)
				);
			}
		}

		_body.setPosition(_position->getPosition());
		_body.setSize(sf::Vector2f(size.x * __graphPointDistance, size.y * __graphPointDistance));
		_body.setFillColor(color);

		if (this->getID() == 1) {
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
	}

	void drawObject() {
		_body.setPosition(_position->getPosition());
		window->draw(_body);
	}

	void updateObject() {
		
	}

};