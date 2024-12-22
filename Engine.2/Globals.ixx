export module Globals;

export import std;
export import "SFML/Graphics.hpp";

export const sf::Clock globalClock;

export std::unique_ptr<sf::RenderWindow> window;

// for future development: 
//ViewLock Variables -> move to engine
//export sf::View view;
//export std::pair<std::string, uint64_t> viewObjectData;

export uint64_t globalID = 0;

export const std::string red("\033[31m");
export const std::string reset("\033[0m");

// Hashes for containers
export struct v2u_hash { // vector<unsigned int, unsigned int>
	const std::size_t operator()(const sf::Vector2u& p) const {
		return std::hash<int>{}(p.x) ^ (std::hash<int>{}(p.y) << 1);
	}
};
export struct pID_hash { // pair<ID, unsigned int>
	const std::size_t operator()(const std::pair<uint64_t, unsigned int>& p) const {
		return p.first;
	}
};

// Mathematical sets differences defined below. Both: A \ B.
export const
std::vector<sf::Vector2u> containerDifference(std::unordered_set<sf::Vector2u, v2u_hash> A, std::vector<sf::Vector2u> B) {
	for (sf::Vector2u e : B) {
		if (A.contains(e)) A.erase(e);
	}	
	std::vector<sf::Vector2u> v(A.begin(), A.end());
	return v;
}
export const
std::vector<sf::Vector2u> containerDifference(std::vector<sf::Vector2u> A, std::unordered_set<sf::Vector2u, v2u_hash> B) {
	for (size_t i = 0; i < A.size(); i++) {
		if (B.contains(A[i])) A.erase(A.begin() + i--);
	}
	return A;
}