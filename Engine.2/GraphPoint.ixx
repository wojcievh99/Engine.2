export module GraphPoint;

import Globals;

export class GraphPoint {
	sf::Vector2u __nr; sf::Vector2f __position;
	std::set<uint64_t> __objects;
public:
	GraphPoint(sf::Vector2f position, sf::Vector2u nr)
		: __position(position), __nr(nr) { }

	unsigned int isBlocked(uint64_t object) {
		if (__objects.contains(object))
			return __objects.size() - 1;
		else 
			return __objects.size();
	}

	sf::Vector2f getPosition() {
		return __position;
	}
	sf::Vector2u getNumber() {
		return __nr;
	}

	void intersected(uint64_t object) {
		__objects.insert(object);
	}
	void diverged(uint64_t object) {
		__objects.erase(object);
	}
};