export module GraphContainer;

import Globals;
export import GraphPoint;

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
		if (__container.count(newPoint->getNumber())) // always 1 or 0
			return false; // Already exists.
		__container[newPoint->getNumber()] = newPoint; 
	}

	void getPoint(sf::Vector2u number, std::weak_ptr<GraphPoint>& point) {
		if (__container.count(number)) { // always 1 or 0
			point = __container[number]; return;
		}
		this->_createPoint(number); // if the point doesn't exist yet

		return getPoint(number, point);
	}

	size_t size() {
		return __container.size();
	}

} inline _graph;