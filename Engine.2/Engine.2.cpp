// Engine.2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

import std;
import Engine;

import Globals;
import Depen;

class Ground 
    : public virtual Base, public Drawable, public Collidable 
{

public:
    Ground(sf::Vector2i _position, sf::Vector2i _size) 
        : Base(_position), Collidable(_size)
    {

		this->setObject(object_type::RECTANGLE);
		this->setSize(_size);
        this->getObject<sf::RectangleShape>()->setFillColor(sf::Color::Red);

    };
};

class Hero
	:	public virtual Base, public virtual Textureable, public Animatable,
		public Drawable, public Collidable, public Moveable
{
public:
	Hero(sf::Vector2i _position, sf::Vector2i _size, sf::Color _color)
		: Base(_position),  
		Textureable("assets/MartialHero", sf::Vector2f(2.f, 2.f)),
		Animatable("directives_anim/character_anim_directive.txt"),
		Collidable()
	{
		this->setAccDirection(sf::Vector2i(0, 1));

	};
};


int main()
{

    Engine::get().init(std::make_pair(1000, 1200), "SuperGame", false, false, 60, 2);
    
	Engine::get().create<Ground>(
		sf::Vector2i(50, 200), sf::Vector2i(100, 20)
	);
	Engine::get().create<Hero>(
		sf::Vector2i(80, 10), sf::Vector2i(10, 15), sf::Color::Green
	);

    Engine::get().run();
    return 0;

}