// Engine.2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

import std;
import Engine;

import Globals;

import Rectangle;
import Character;

/*
"player.png" player.txt
DEFAULT { [30,50,20,100,timeMS],   [], [], [] } [0]

"(.+?) \{\([([0-9]+?),([0-9]+?),...\][ ].)+ "

DEAD { [], []. }
GOLEFT { ... }
GOLRIGHT
GOUP
GODOWN
JUMPLEFT
JUMPRIGHT
BORING { }

&DOITACTUAL =
actual_index =0
+ Wewnętrzny zegar animacji (*)

Event Left Arrow:
changeAnim("GOLEFT")
================================
HEAD
LEFT ARM
RIGHT ARM*/

int main()
{

    Engine::get().init(std::make_pair(1000, 1200), "TEST", false, 60, 3);
    
	Engine::get().create<Rectangle>(
        sf::Vector2i(10, 200), sf::Vector2i(100, 10), sf::Color::Red
    );
    Engine::get().create<Rectangle>(
        sf::Vector2i(50, 220), sf::Vector2i(200, 10), sf::Color::Red
    );
	Engine::get().create<Character>(
		sf::Vector2i(100, 100), sf::Vector2i(10, 15), sf::Color::Green
	);

    Engine::get().run();
    return 0;

}