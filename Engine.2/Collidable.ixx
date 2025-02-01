export module Collidable;

import Globals;

import Base;
import ObjectPointBound;

// inherit from it in your object if your object 
// should detect and respond to collisions with 
// other Collidable objects 
export class Collidable : public virtual Base {

	// how many other objects may be on the same point to don't cause collision
	// if it is defined as 2 then only object that has __definedBound >= 2 can be on the same point
	// because 1/2 + 1/2 <= 1 and 1/2 + 1/3(or 1/4, 1/5... and so on) <= 1
	// this algorithm is defined in class GraphPoint in function tryBound()
	unsigned int __definedBound; 

	// specified inside of that class
	ObjectPointBound __objectBounds;

public:
	// default shape is rectangle with given size.
	// Future development can add an option to add a txt file with any 
	// defined inside shape that will be taken instead of rectangle
	Collidable(sf::Vector2i size, unsigned int definedBound = 1);
	Collidable(unsigned int definedBound = 1);
	~Collidable();

	virtual void afterCollision() { };
	// with object move (defined in class Moveable) comes move bound as well
	void moveBound(sf::Vector2i);

	// redefine bound if object size changes
	void redefineBound(sf::Vector2i);

	// checks if next move will cause an intersection with other object
	// this intersection-collision is defined in class GraphPoint in function tryBound()
	bool checkNextMove(sf::Vector2i);
};