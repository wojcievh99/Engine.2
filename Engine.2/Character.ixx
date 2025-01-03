export module Character;

import Base;
import Drawable;
import Moveable;
import Eventable;
import Updateable;
import Collidable;
import Deleteable;

export class Character : public virtual Base, public Deleteable, public Drawable, public Moveable, public Eventable, public Collidable {

public:
	Character(sf::Vector2u position, sf::Vector2u size, sf::Color color)
		: Base(position), Collidable(size)
	{
		setObject(object_type::RECTANGLE);
		_setSize(size);
		_object.get<sf::RectangleShape>()->setFillColor(color);

		this->setAccDirection(sf::Vector2i(0, 1));

		this->addKeyAssociation(sf::Keyboard::D, Functor(
			[this]() {
				this->setMoveDirectionX(1);
			}
		));
		this->addKeyAssociation(sf::Keyboard::A, Functor(
			[this]() {
				this->setMoveDirectionX(-1);
			}
		));
		this->addKeyAssociation(sf::Keyboard::Space, Functor(
			[this]() {
				this->setMoveDirectionY(-10);
			}
		));
		
	}

};