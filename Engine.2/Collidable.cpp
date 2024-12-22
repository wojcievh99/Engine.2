module Collidable;

import GraphContainer;

Collidable::Collidable(sf::Vector2u size, unsigned int definedBound)
	: Base(), __definedBound(definedBound), __objectBounds(this->getID(), __definedBound) {
	__objectBounds.addRectangleBound(_position.lock()->getNumber(), _position.lock()->getNumber() + size);
}

void Collidable::moveBound(sf::Vector2u move) {
	__objectBounds.moveBound(move);
}

bool Collidable::checkNextMove(sf::Vector2u nextMove) {
	std::vector<sf::Vector2u> nextFrameBound = __objectBounds.getVirtuallyMovedBound(nextMove);
	nextFrameBound = containerDifference(nextFrameBound, __objectBounds.getNumbers());
	for (sf::Vector2u e : nextFrameBound) {
		if (!GraphContainer::get().getPoint(e).lock()->tryBound(this->getID(), __definedBound)) {
			return false;
		}
	}
	return true;
}