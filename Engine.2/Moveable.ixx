export module Moveable;

import Globals;
import Base;

import GraphContainer;

// inherit from it in your object if your object 
// should move/be able to move
export class Moveable : public virtual Base {
	sf::Vector2u __moveDirection;
	sf::Vector2u __acceleration;
public:
	
	void setMoveDirection(sf::Vector2u _newMoveDir) { __moveDirection = _newMoveDir; }
	void setAccDirection(sf::Vector2u _newAccDir) { __acceleration = _newAccDir; }

	void setMoveDirectionX(unsigned int X) { __moveDirection.x = X; }
	void setMoveDirectionY(unsigned int Y) { __moveDirection.x = Y; }
	void setAccDirectionX(unsigned int X) { __acceleration.x = X; }
	void setAccDirectionY(unsigned int Y) { __acceleration.x = Y; }

	virtual void moveObject() {
		GraphContainer::get().getPoint(_position.lock()->getNumber() + this->getMoveDir(), _position);
	};
	void accelerateObject() {
		__moveDirection += __acceleration;
	}

	sf::Vector2u getMoveDir() { return __moveDirection; }
	sf::Vector2u getAccDir() { return __acceleration; }

};