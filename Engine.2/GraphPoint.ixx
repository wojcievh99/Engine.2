export module GraphPoint;

import Globals;

export class GraphPoint {
	sf::Vector2u __nr; sf::Vector2f __position;
	unsigned int __objects;
public:
	GraphPoint(sf::Vector2f position, sf::Vector2u nr)
		: __position(position), __nr(nr), __objects(0) { }

	unsigned int isBlocked() {
		return __objects;
	}

	sf::Vector2f getPosition() {
		return __position;
	}
	sf::Vector2u getNumber() {
		return __nr;
	}

	void intersected() {
		__objects++;
	}
	void diverged() {
		__objects--;
	}
};