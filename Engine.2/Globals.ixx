export module Globals;

export import std;
export import "SFML/Graphics.hpp";
export import "filesystem";

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
export struct v2i_hash { // vector<unsigned int, unsigned int>
	const std::size_t operator()(const sf::Vector2i& p) const {
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
std::vector<sf::Vector2i> containerDifference(std::unordered_set<sf::Vector2i, v2i_hash> A, std::vector<sf::Vector2i> B) {
	for (sf::Vector2i e : B) {
		if (A.contains(e)) A.erase(e);
	}	
	std::vector<sf::Vector2i> v(A.begin(), A.end());
	return v;
}
export const
std::vector<sf::Vector2i> containerDifference(std::vector<sf::Vector2i> A, std::unordered_set<sf::Vector2i, v2i_hash> B) {
	for (size_t i = 0; i < A.size(); i++) {
		if (B.contains(A[i])) A.erase(A.begin() + i--);
	}
	return A;
}

// Returns a vector of points that are inside of a rectangle defined by two points.
export const
std::vector<sf::Vector2i> getRectangleBound(sf::Vector2i numberA, sf::Vector2i numberB) {
	std::vector<sf::Vector2i> result;
	for (int line = numberA.y; line < numberB.y; line++) {
		for (int column = numberA.x; column < numberB.x; column++) {
			result.push_back(sf::Vector2i(column, line));
		}
	}
	return result;
}