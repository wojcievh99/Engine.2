export module ObjectPointBound;

import Globals;

import GraphPoint;
import GraphContainer;

// designed to define the shape of an object mainly for collisions 
export class ObjectPointBound {
	// holds points that the object is currently standing on
	std::vector<std::weak_ptr<GraphPoint>> _bounds;
	std::unordered_set<sf::Vector2i, v2i_hash> _numbers;

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
	bool addBound(sf::Vector2i number) {
		if (_numbers.contains(number)) 
			return false;
		GraphContainer::get().getPoint(number, temporary);
		temporary.lock()->intersected(_adherence, _definedBound);
		_bounds.push_back(temporary); 
		_numbers.insert(number);
		return true;
	}
	// add an area of points by border points
	void addRectangleBound(sf::Vector2i numberA, sf::Vector2i numberB) {
		for (int line = numberA.y; line < numberB.y; line++) {
			for (int column = numberA.x; column < numberB.x; column++) {
				addBound(sf::Vector2i(column, line));
			}
		}
	}

	void clearBound() {
		for (auto&& e : _bounds) {
			e.lock()->diverged(_adherence, _definedBound);
		}
		_bounds.clear(); _numbers.clear();
	}
	void clearBound(std::unordered_set<sf::Vector2i, v2i_hash> numbers) {

		for (size_t i = 0; i < _bounds.size(); i++) {
			if (numbers.contains(_bounds[i].lock()->getNumber())) {
				_bounds[i].lock()->diverged(_adherence, _definedBound);
				_bounds.erase(_bounds.begin() + i--);
			}
		}

	}

	// move every point of specified above shape by given vector of displacement
	void moveBound(sf::Vector2i move) {
		for (auto&& e : _bounds) {
			e.lock()->diverged(_adherence, _definedBound);
			GraphContainer::get().getPoint(e.lock()->getNumber() + move, e);
			e.lock()->intersected(_adherence, _definedBound);
		}
	}
	// get result as if bound was moved but the original stays the same
	// returns a copy
	std::vector<sf::Vector2i> getVirtuallyMovedBound(const sf::Vector2i move) {
		std::vector<sf::Vector2i> result; 
		for (std::weak_ptr<GraphPoint> e : _bounds) {
			result.push_back(e.lock()->getNumber() + move);
		}
		return result;
	}

	std::unordered_set<sf::Vector2i, v2i_hash> getNumbers() {
		return _numbers;
	}
};