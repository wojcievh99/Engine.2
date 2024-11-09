export module GraphContainer;

import Globals;
export import GraphPoint;

struct v2u_hash {
	std::size_t operator()(const sf::Vector2u& p) const {
		return std::hash<int>{}(p.x) ^ (std::hash<int>{}(p.y) << 1);
	}
};

bool operator == (sf::Vector2u a, sf::Vector2u b)
{
	if (a.x == b.x and a.y == b.y) return true;
	return false;
};

export class GraphContainer {
	std::unordered_map<sf::Vector2u, std::shared_ptr<GraphPoint>, v2u_hash> __container;

	void _createPoint(sf::Vector2u number) {		
		_graph.addPoint(
			std::make_shared<GraphPoint>(
				sf::Vector2f((float)number.x * __graphPointDistance, (float)number.y * __graphPointDistance),
				sf::Vector2u(number.x, number.y))
		);
	}

public:

	bool addPoint(std::shared_ptr<GraphPoint> newPoint) {
		for (const auto& e : __container)
			if (e.second->getNumber() == newPoint->getNumber()) return false; // Already exists.
		__container[newPoint->getNumber()] = newPoint; 
	}

	bool getPoint(sf::Vector2u number, std::shared_ptr<GraphPoint>& point) {
		/*for (auto& e : __container)
			if (e.second->getNumber() == number) {
				if (e.second->isBlocked()) return false;
				point = e.second; return true;
			}*/

		if (__container.count(number)) {
			point = __container[number]; return true;
			//__container.at(number);
		}
			

		this->_createPoint(number); // if the point doesn't exist yet

		return getPoint(number, point);
	}

	size_t size() {
		return __container.size();
	}

	friend class ObjectContainer;
} inline _graph;