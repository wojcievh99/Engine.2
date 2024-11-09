export module GraphPoint;

import Globals;

export class GraphPoint {
	bool __b;
	sf::Vector2u __nr; sf::Vector2f __position;
public:
	GraphPoint(sf::Vector2f position, sf::Vector2u nr)
		: __position(position), __nr(nr), __b(false) { }

	bool isBlocked() {
		return __b;
	}

	sf::Vector2f getPosition() {
		return __position;
	}
	sf::Vector2u getNumber() {
		return __nr;
	}

	void block() {
		__b = true;
	}
	void unblock() {
		__b = false;
	}
};