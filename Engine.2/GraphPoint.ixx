export module GraphPoint;

import Globals;

export class GraphPoint {
	sf::Vector2u __nr; sf::Vector2f __position;
	std::unordered_set<std::pair<uint64_t, unsigned int>, pID_hash> __objects; // <ID, definedBound>
public:
	GraphPoint(sf::Vector2f position, sf::Vector2u nr)
		: __position(position), __nr(nr) { }

	unsigned int isBlocked(uint64_t id, unsigned int definedBound) {
		if (__objects.contains({id, definedBound}))
			return __objects.size() - 1;
		else 
			return __objects.size();
	}
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

	void intersected(uint64_t id, unsigned int definedBound) {
		__objects.insert({ id, definedBound });
	}
	void diverged(uint64_t id, unsigned int definedBound) {
		__objects.erase({ id, definedBound });
	}
};