export module Collidable;

import Globals;

export import ObjectPointBound;
import GraphContainer;

import Base;

export class Collidable : public virtual Base {
	// how many other objects may be on the same point to don't cause collision
	unsigned int __definedBound; 
	ObjectPointBound __objectBounds;

public:
	Collidable(sf::Vector2u size, unsigned int definedBound = 1) 
		: Base(), __definedBound(definedBound), __objectBounds(this->getID(), __definedBound) {
		__objectBounds.addRectangleBound(_position.lock()->getNumber(), _position.lock()->getNumber() + size);
	}

	virtual void afterCollision() { };
	void moveBound(sf::Vector2u move) {
		__objectBounds.moveBound(move);
	}

	bool checkNextMove(sf::Vector2u nextMove) {
		std::vector<sf::Vector2u> nextFrameBound = __objectBounds.getVirtuallyMovedBound(nextMove);
		nextFrameBound = containerDifference(nextFrameBound, __objectBounds.getNumbers());
		for (sf::Vector2u e : nextFrameBound) {
			if (!GraphContainer::get().getPoint(e).lock()->tryBound(this->getID(), __definedBound)) {
				return false;
			}
		}
		return true;
	}

};