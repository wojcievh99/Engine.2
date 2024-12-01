export module GraphPoint;

import Globals;

// one single point of a graph
export class GraphPoint {
	// dedicated number and real position
	sf::Vector2u __nr; sf::Vector2f __position;
	// objects that stand on it currently
	std::unordered_set<std::pair<uint64_t, unsigned int>, pID_hash> __objects; // <ID, definedBound>

public:
	GraphPoint(sf::Vector2f position, sf::Vector2u nr)
		: __position(position), __nr(nr) { }

	// check if other objects that given one exist on stand point
	unsigned int isBlocked(uint64_t id, unsigned int definedBound) {
		if (__objects.contains({id, definedBound}))
			return __objects.size() - 1;
		else 
			return __objects.size();
	}
	// check if given object is able to intersect this point
	// _definedBound defined in detail in class Collidable
	bool tryBound(uint64_t id, unsigned int definedBound) { /// std::RATIO
		float sumBound = 0; // if it will be more that 1 then the point is full
		if (!__objects.contains({ id, definedBound })) sumBound = 1.f / float(definedBound);
		for (const auto& e : __objects) sumBound += (1.f / float(e.second));
		return sumBound <= 1.f;
	}

	sf::Vector2f getPosition() {
		return __position;
	}
	sf::Vector2u getNumber() {
		return __nr;
	}

	// object going into that point 
	void intersected(uint64_t id, unsigned int definedBound) {
		__objects.insert({ id, definedBound });
	}
	// object getting out of that point
	void diverged(uint64_t id, unsigned int definedBound) {
		__objects.erase({ id, definedBound });
	}
	// (used wisely in engines inner mechanics; not designed for outside use)
};