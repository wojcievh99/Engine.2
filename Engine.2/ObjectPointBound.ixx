export module ObjectPointBound;

import Globals;

import GraphPoint;
import GraphContainer;

// designed to define the shape of an object mainly for collisions 
export class ObjectPointBound {
	// holds points that the object is currently standing on
	std::vector<std::weak_ptr<GraphPoint>> _bounds;
	std::unordered_set<sf::Vector2u, v2u_hash> _numbers;

	// ID of object that stands on those points and 
	// it's allowance of other object in those points 
	// (second described in detail in class Collidable)
	uint64_t _adherence;
	unsigned int _definedBound;

	// just a temp value for simplicity 
	// used frequently 
	std::weak_ptr<GraphPoint> temporary;
public:
	ObjectPointBound(uint64_t adherence, unsigned int definedBound)
		: _adherence(adherence), _definedBound(definedBound) {};

	// add one point of a shape by it's number
	bool addBound(sf::Vector2u number) {
		if (_numbers.contains(number)) 
			return false;
		GraphContainer::get().getPoint(number, temporary);
		temporary.lock()->intersected(_adherence, _definedBound);
		_bounds.push_back(temporary); 
		_numbers.insert(number);
		return true;
	}
	// add an area of points by border points
	bool addRectangleBound(sf::Vector2u numberA, sf::Vector2u numberB) {
		bool condition = true; 
		for (unsigned int line = numberA.y; line < numberB.y; line++) {
			for (unsigned int column = numberA.x; column < numberB.x; column++) {
				condition = addBound(sf::Vector2u(column, line));
			}
		}
		return condition;
	}

	// move every point of specified above shape by given vector of displacement
	void moveBound(sf::Vector2u move) {
		for (auto&& e : _bounds) {
			e.lock()->diverged(_adherence, _definedBound);
			GraphContainer::get().getPoint(e.lock()->getNumber() + move, e);
			e.lock()->intersected(_adherence, _definedBound);
		}
	}
	// get result as if bound was moved but the oryginal stays the same
	// returns a copy
	std::vector<sf::Vector2u> getVirtuallyMovedBound(sf::Vector2u move) {
		std::vector<sf::Vector2u> result; 
		for (std::weak_ptr<GraphPoint> e : _bounds) {
			result.push_back(e.lock()->getNumber() + move);
		}
		return result;
	}

	std::unordered_set<sf::Vector2u, v2u_hash> getNumbers() {
		return _numbers;
	}
};