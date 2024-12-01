// Engine.2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

import std;
import Engine;

import Rectangle;
import Character;

int main()
{

    bool condition = Engine::get().init(std::make_pair(1000, 1200), "TEST", false, 60, 3);
    
    Character::create<Character>(sf::Vector2u(100, 100),
        sf::Vector2u(30, 30),
        sf::Color::Green);
        
    if (condition) Engine::get().run();

    return 0;
}