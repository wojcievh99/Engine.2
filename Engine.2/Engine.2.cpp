// Engine.2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

import std;
import Engine;

import Rectangle;

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

    auto r = engine.addObject<Rectangle>(std::make_shared<Rectangle>(
        sf::Vector2u(200, 200),
        sf::Vector2u(30, 30),
        sf::Color::Green
    ));

    /*engine.addObject<Rectangle>(std::make_shared<Rectangle>(
        sf::Vector2u(800, 200),
        sf::Vector2u(00, 500),
        sf::Color::Red
    ));*/
    
    //engine.lockViewOnObject(std::make_pair(r.lock()->getClassName(), r.lock()->getID()));
    
    if (condition) engine.run();

}
