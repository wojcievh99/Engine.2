module Collidable;

import GraphContainer;

Collidable::Collidable(unsigned int definedBound)
	: Base(), __definedBound(definedBound), __objectBounds(this->getID(), __definedBound) {

	try {

		__objectBounds.addRectangleBound(
			_position.lock()->getNumber(), 
			_position.lock()->getNumber() 
				+ this->find_point_size(_object.get<sf::Sprite>()->getGlobalBounds().getSize())
			);

	}
	catch (const std::bad_variant_access& e) {} 
	//ignore, user will redefine bound later

}
Collidable::Collidable(sf::Vector2i size, unsigned int definedBound)
	: Base(), __definedBound(definedBound), __objectBounds(this->getID(), __definedBound) {
	__objectBounds.addRectangleBound(_position.lock()->getNumber(), _position.lock()->getNumber() + size);
}
Collidable::~Collidable() {
	__objectBounds.clearBound();
}

void Collidable::moveBound(sf::Vector2i move) {
	__objectBounds.moveBound(move);
}

void Collidable::redefineBound(sf::Vector2i size) {
	__objectBounds.clearBound();
	__objectBounds.addRectangleBound(_position.lock()->getNumber(), _position.lock()->getNumber() + size);
}

bool Collidable::checkNextMove(sf::Vector2i nextMove) {
	std::vector<sf::Vector2i> nextFrameBound = __objectBounds.getVirtuallyMovedBound(nextMove);
	nextFrameBound = containerDifference(nextFrameBound, __objectBounds.getNumbers());
	for (sf::Vector2i e : nextFrameBound) {
		if (!GraphContainer::get().getPoint(e).lock()->tryBound(this->getID(), __definedBound)) {
			return false;
		}
	}
	return true;
}