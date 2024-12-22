// Engine.2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

import std;
import Engine;

import Globals;

import Rectangle;
import Character;


/*
* Zmienić className na type_index(type_info) [+-] (deleted unused and unnecessary classname)
* Globals const [+]

Wzorce Projektowe na kiedyś

Przed code review: 
Wielowątkowość
Wydajność forów
Optymalizacja Delete (stos, kolejka zamiast zmiennej 'alive')
Optymalizacja Drawable (z class Transformable)

Code review:
przemyślana Obsługa Wyjątków

*/
int main()
{

    Engine::get().init(std::make_pair(1000, 1200), "TEST", false, 60, 1);
    
	Engine::get().create<Rectangle>(
        sf::Vector2u(100, 100), sf::Vector2u(100, 100), sf::Color::Red
    );
	Engine::get().create<Character>(
		sf::Vector2u(200, 200), sf::Vector2u(100, 100), sf::Color::Green
	);

        
    Engine::get().run();

    return 0;
}