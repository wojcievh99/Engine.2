export module Globals;

export import std;
export import "SFML/Graphics.hpp";

export import Functor;
export import Concepts;
export import Exceptions;

export sf::Clock globalClock;

export unsigned int __framerate;
export float __graphPointDistance;

export std::unique_ptr<sf::RenderWindow> window;

//ViewLock Variables -> move to engine
//export sf::View view;
//export std::pair<std::string, uint64_t> viewObjectData;

export uint64_t globalID = 0;

export const std::string red("\033[31m");
export const std::string reset("\033[0m");

// Hash
export struct v2u_hash { // vector<unsigned int, unsigned int>
	std::size_t operator()(const sf::Vector2u& p) const {
		return std::hash<int>{}(p.x) ^ (std::hash<int>{}(p.y) << 1);
	}
};
export struct pID_hash { // pair<ID, unsigned int>
	std::size_t operator()(const std::pair<uint64_t, unsigned int>& p) const {
		return p.first;
	}
};

// Mathematical sets differences defined below. Always: A \ B.
export 
std::vector<sf::Vector2u> containerDifference(std::unordered_set<sf::Vector2u, v2u_hash> A, std::vector<sf::Vector2u> B) {
	for (sf::Vector2u e : B) {
		if (A.contains(e)) A.erase(e);
	}	
	std::vector<sf::Vector2u> v(A.begin(), A.end());
	return v;
}
export
std::vector<sf::Vector2u> containerDifference(std::vector<sf::Vector2u> A, std::unordered_set<sf::Vector2u, v2u_hash> B) {
	for (size_t i = 0; i < A.size(); i++) {
		if (B.contains(A[i])) A.erase(A.begin() + i--);
	}
	return A;
}