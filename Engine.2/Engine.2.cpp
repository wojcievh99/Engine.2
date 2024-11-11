// Engine.2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

import std;
import Engine;

import Rectangle;
import Character;

/*
# Ignoruj wszystkie pliki
*

# Wyklucz z ignorowania folder .gitignore
!.gitignore

# Wyklucz z ignorowania pliki z rozszerzeniem .txt
!*.ixx



emplace, emplace*
insert_|or_assign
insert_range (!)
at()
*/

int main()
{
    bool condition = engine.init(std::make_pair(1000, 1200), "TEST", false, 60, 3.f);

    auto r = engine.addObject<Character>(std::make_shared<Character>(
        sf::Vector2u(100, 100),
        sf::Vector2u(30, 30),
        sf::Color::Green
    ));

    engine.addObject<Rectangle>(std::make_shared<Rectangle>(
        sf::Vector2u(50, 50),
        sf::Vector2u(10, 50),
        sf::Color::Red,
        2
    ));

    engine.addObject<Rectangle>(std::make_shared<Rectangle>(
        sf::Vector2u(200, 80),
        sf::Vector2u(50, 200),
        sf::Color::Red, 1
    ));
        
    if (condition) engine.run();

    return 0;
}
