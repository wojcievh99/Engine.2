// Engine.2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

import std;
import Engine;

import Globals;

import Rectangle;
import Character;


int main()
{

    Engine::get().init(std::make_pair(1000, 1200), "TEST", false, 60, 3);
    
	Engine::get().create<Rectangle>(
        sf::Vector2u(10, 200), sf::Vector2u(100, 10), sf::Color::Red
    );
    Engine::get().create<Rectangle>(
        sf::Vector2u(50, 220), sf::Vector2u(200, 10), sf::Color::Red
    );
	Engine::get().create<Character>(
		sf::Vector2u(100, 100), sf::Vector2u(10, 15), sf::Color::Green
	);
        
    Engine::get().run();
    return 0;

}