export module GraphContainer;

import Globals;
export import GraphPoint;

static bool operator == (sf::Vector2u a, sf::Vector2u b)
{
	if (a.x == b.x and a.y == b.y) return true;
	return false;
};

export
sf::Vector2u operator + (sf::Vector2u a, sf::Vector2i b)
{
	return sf::Vector2u(a.x + b.x, a.y + b.y);
};

// Container class for graph points
// 
// Graph points through the implementation of this class 
// can be dynamically created, loaded and accessed.
//
// Singleton: only one instance of this class is allowed.
export class GraphContainer {

	std::unordered_map<sf::Vector2i, std::shared_ptr<GraphPoint>, v2i_hash> __container;
	std::unique_ptr<float> __graphPointDistance;

	void _createPoint(sf::Vector2i number) {		
		addPoint(
			std::make_shared<GraphPoint>(
				sf::Vector2f(
					(float)number.x * *__graphPointDistance, (float)number.y * *__graphPointDistance
				),
				sf::Vector2i(number.x, number.y))
		);
	}

	GraphContainer() = default;
	~GraphContainer() = default;

	GraphContainer(const GraphContainer&) = delete;
	GraphContainer& operator=(const GraphContainer&) = delete;

public:

	// only one instance 
	static GraphContainer& get() {
		static GraphContainer _instance;
		return _instance;
	}

	// only once
	bool setGraphPointDistance(float _gpd) {
		if (!__graphPointDistance) {
			__graphPointDistance = std::make_unique<float>(_gpd);
			return true;
		}
		return false;
	}
	float getGraphPointDistance() {
		return *__graphPointDistance;
	}

	bool addPoint(std::shared_ptr<GraphPoint> newPoint) {
		if (__container.count(newPoint->getNumber())) // always 1 or 0
			return false; // Already exists.
		__container[newPoint->getNumber()] = newPoint; 
		return true;
	}

	// If the point doesn't exist then it is created.
	// Usually getPoint() is called when point is needed 
	// to stand on it or it is already defined so there
	// will not be a single point that exists but was
	// never used at least once.
	void getPoint(sf::Vector2i number, std::weak_ptr<GraphPoint>& point) {
		if (__container.count(number)) { // always 1 or 0
			point = __container[number]; return;
		}
		this->_createPoint(number); // if the point doesn't exist yet

		return getPoint(number, point);
	}

	// exacly the same but returns weak_ptr to that point
	// instead of changing reference given as a second argument 
	std::weak_ptr<GraphPoint> getPoint(sf::Vector2i number) {
		if (__container.count(number))
			return __container[number];
		else 
			this->_createPoint(number);
		return getPoint(number);
	}

	size_t size() {
		return __container.size();
	}

};