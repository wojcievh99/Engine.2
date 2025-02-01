export module ObjectHolder;
import Globals;

import Functor;

// defines held objects for tasks 
export class ObjectHolder {

	std::unordered_map<uint64_t, Functor>	_objectDraws;
	std::unordered_map<uint64_t, Functor>	_objectUpdates;
	std::unordered_map<uint64_t, Functor>	_objectAnimations;
	std::unordered_set<uint64_t>			_objectMoves;
	std::unordered_set<uint64_t>			_objectWithCollisions;
	std::unordered_set<uint64_t>			_objectsWithEventsAssociatedWithFunctions;

public:

	// get implementation for containers above:
	const std::unordered_map<uint64_t, Functor>&	draws() {
		return _objectDraws;
	}
	const std::unordered_map<uint64_t, Functor>&	updates() {
		return _objectUpdates;
	}
	const std::unordered_map<uint64_t, Functor>&	animations() {
		return _objectAnimations;
	}
	const std::unordered_set<uint64_t>&				moves() {
		return _objectMoves;
	}
	const std::unordered_set<uint64_t>&				collisions() {
		return _objectWithCollisions;
	}
	const std::unordered_set<uint64_t>&				events() {
		return _objectsWithEventsAssociatedWithFunctions;
	}

	// friend class instead of setters
	friend class ObjectContainer;
};