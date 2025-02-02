export module Character;

import Base;
import Drawable;
import Moveable;
import Eventable;
import Updateable;
import Collidable;
import Deleteable;

import Textureable;
import Animatable;

export class Character : public virtual Base, 
	public virtual Textureable, public Animatable,
	public Drawable, public Moveable, 
	public Eventable, public Collidable 
{

public:
	Character(sf::Vector2i position, sf::Vector2i size, sf::Color color)
		: Base(position), 
		Textureable("assets/MartialHero", sf::Vector2f(2.f, 2.f)),
		Animatable("directives_anim/character_anim_directive.txt"),
		Collidable()
	{
		this->setAccDirection(sf::Vector2i(0, 1));

		this->addKeyAssociation(sf::Keyboard::D, Functor(
			[this]() {
				this->setMoveDirectionX(1);
				this->turn_sprite_x(XA::RIGHT);
			}
		));
		this->addKeyAssociation(sf::Keyboard::A, Functor(
			[this]() {
				this->setMoveDirectionX(-1);
				this->turn_sprite_x(XA::LEFT);
			}
		));
		this->addKeyAssociation(sf::Keyboard::Space, Functor(
			[this]() {
				this->setMoveDirectionY(-10);
			}
		));
		
	}

};