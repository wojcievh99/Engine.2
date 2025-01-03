export module Moveable;

import Globals;
import Base;

import GraphContainer;

export 
sf::Vector2i operator-(sf::Vector2i v, unsigned int i) {
	if (v.x > 0) v.x--;
	else if (v.x != 0) v.x++;
	if (v.y > 0) v.y--;
	else if (v.y != 0) v.y++;
	return v;
}

// inherit from it in your object if your object 
// should move/be able to move
export class Moveable : public virtual Base {
	sf::Vector2i __moveDirection;
	sf::Vector2i __acceleration;
public:

	void setMoveDirection(sf::Vector2i _newMoveDir) { __moveDirection = _newMoveDir; }
	void setAccDirection(sf::Vector2i _newAccDir) { __acceleration = _newAccDir; }

	void setMoveDirectionX(int X) { __moveDirection.x = X; }
	void setMoveDirectionY(int Y) { __moveDirection.y = Y; }
	void setAccDirectionX(int X) { __acceleration.x = X; }
	void setAccDirectionY(int Y) { __acceleration.y = Y; }

	void moveObject() {
		GraphContainer::get().getPoint(_position.lock()->getNumber() + this->getMoveDir(), _position);
	};
	void moveOnce(sf::Vector2i _dir) {
		GraphContainer::get().getPoint(_position.lock()->getNumber() + _dir, _position);
	}
	void accelerateObject() {
		if (__moveDirection.x > 25 or __moveDirection.y > 25) return;
		__moveDirection += __acceleration;
	}

	sf::Vector2i getMoveDir() const { return __moveDirection; }
	sf::Vector2i getAccDir() const { return __acceleration; }

};