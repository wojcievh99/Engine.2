export module Rectangle;

import Base;
import Drawable;
import Moveable;
import Eventable;
import Updateable;
import Collidable;
import Deleteable;

export class Rectangle : public virtual Base, public Eventable, public Deleteable, public Drawable, public Collidable {

public:
	Rectangle(sf::Vector2i position, sf::Vector2i size, sf::Color color)
		: Base(position), Collidable(size)
	{

		setObject(object_type::RECTANGLE);
		_setSize(size);
		_object.get<sf::RectangleShape>()->setFillColor(color);

		addKeyAssociation(sf::Keyboard::T, Functor(
			[this]() {
				deleteObject();
			}
		));

	}

};