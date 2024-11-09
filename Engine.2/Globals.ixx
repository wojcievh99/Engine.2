export module Globals;

export import std;
export import "SFML/Graphics.hpp";

export import Functor;
export import Concepts;

export sf::Clock globalClock;
export std::mutex deleteMutex; // <- move to engine

export unsigned int __framerate; // <- move to engine
export float __graphPointDistance;
export bool isWindowOpen = false; // <- move to engine

export std::unique_ptr<sf::RenderWindow> window;
export std::unique_ptr<sf::Event> event; // <- move to engine

//ViewLock Variables -> move to engine
export sf::View view;
export std::pair<std::string, uint64_t> viewObjectData;
export bool viewLock = false;

export uint64_t globalID = 0;

export const std::string red("\033[31m");
export const std::string reset("\033[0m");

export struct v2u_hash {
	std::size_t operator()(const sf::Vector2u& p) const {
		return std::hash<int>{}(p.x) ^ (std::hash<int>{}(p.y) << 1);
	}
};