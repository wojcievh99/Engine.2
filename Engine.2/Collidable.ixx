export module Collidable;

import Globals;
export import ObjectPointBound;

import Base;

export class Collidable : public virtual Base {
	// how many other objects may be on the same point to don't cause collision
	unsigned int _definedBound; 
	ObjectPointBound _objectBounds;
public:
	Collidable(sf::Vector2u size, unsigned int definedBound = 1) : Base(), _definedBound(definedBound) {
		_objectBounds.addRectangleBound(_position.lock()->getNumber(), _position.lock()->getNumber() + size);
	}

};