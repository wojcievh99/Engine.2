export module ObjectContainer;

import Globals;
import ObjectHolder;

import Base;

import Drawable;
import Updateable;
import Moveable;
import Collidable;
import Eventable;

export class ObjectContainer {

	ObjectContainer() = default;
	~ObjectContainer() = default;

	ObjectContainer(const ObjectContainer&) = delete;
	ObjectContainer& operator=(const ObjectContainer&) = delete;

	// fundamental database; not designed to use outside of this class.
	std::unordered_map<uint64_t, std::shared_ptr<Base>> _database;
	std::list<uint64_t> _bin;

public:
	// only one instance
	static ObjectContainer& get() {
		static ObjectContainer _instance;
		return _instance;
	}

	// designed to define object's tasks; deisigned to use outside
	ObjectHolder tasks;

	// for when there is no other option that to use fundamental database
	std::shared_ptr<Base>& getObjectByID(uint64_t _id) {
		return _database[_id];
	}
	std::list<uint64_t>& getBin() {
		return _bin;
	}
	

	void add(const std::shared_ptr<Base>& r) {

		// Adding object to the engine and spliting future tasks:

		_database[r->getID()] = r;

		// Polymorphic: 

		if (std::shared_ptr<Drawable> x = std::dynamic_pointer_cast<Drawable>(r))
			tasks._objectDraws[r->getID()] = Functor([x]() { x->drawObject(); });

		if (std::shared_ptr<Updateable> x = std::dynamic_pointer_cast<Updateable>(r))
			tasks._objectUpdates[r->getID()] = Functor([x]() { x->updateObject(); });

		if (std::shared_ptr<Moveable> x = std::dynamic_pointer_cast<Moveable>(r))
			tasks._objectMoves.insert(r->getID());

		if (std::shared_ptr<Collidable> x = std::dynamic_pointer_cast<Collidable>(r))
			tasks._objectWithCollisions.insert(r->getID());

		if (std::shared_ptr<Eventable> x = std::dynamic_pointer_cast<Eventable>(r))
			tasks._objectsWithEventsAssociatedWithFunctions.insert(r->getID());

	}

	void remove(uint64_t _id) {

		// deleting every instance of an object
		tasks._objectMoves.erase(_id);
		tasks._objectDraws.erase(_id);
		tasks._objectUpdates.erase(_id);
		tasks._objectWithCollisions.erase(_id);
		tasks._objectsWithEventsAssociatedWithFunctions.erase(_id);


		_database.erase(_id);

	}

};