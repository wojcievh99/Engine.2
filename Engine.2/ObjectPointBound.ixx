export module ObjectPointBound;

import Globals;

import GraphPoint;
import GraphContainer;

export class ObjectPointBound {
	std::vector<std::weak_ptr<GraphPoint>> _bounds;
	std::unordered_set<sf::Vector2u, v2u_hash> _numbers;

	std::weak_ptr<GraphPoint> temporary;
public:

	bool addBound(sf::Vector2u number) {
		if (_numbers.contains(number)) 
			return false;
		_graph.getPoint(number, temporary);
		temporary.lock()->intersected();
		_bounds.push_back(temporary); 
		_numbers.insert(number);
		return true;
	}

	bool addRectangleBound(sf::Vector2u numberA, sf::Vector2u numberB) {
		bool condition = true; 
		for (unsigned int line = numberA.y; line < numberB.y; line++) {
			for (unsigned int column = numberA.x; column < numberB.x; column++) {
				condition = addBound(sf::Vector2u(column, line));
			}
		}
		return condition;
	}

	void moveBound(sf::Vector2u move) {
		for (auto&& e : _bounds) {
			e.lock()->diverged();
			_graph.getPoint(e.lock()->getNumber() + move, e);
			e.lock()->intersected();
		}
	}

};