module Base;

import Drawable;
import Updateable;
import Moveable;
import Collidable;
import Eventable;

template<Derived D, typename... Args>
static std::shared_ptr<Base> Base::create(Args&&... args) {
	//static_assert(std::is_base_of<Base2, Derived>::value, "Derived class must derive from Base2");

	auto obj = std::make_shared<D>(std::forward<Args>(args)...);
	//auto obj = std::shared_ptr<Derived>(new Derived(std::forward<Args>(args)...));

	Base::ObjectContainer::get().add(obj);

	return obj;
}

std::weak_ptr<GraphPoint> Base::getPosition() const {
	return _position;
}

std::uint64_t Base::getID() const {
	return __object_id;
}
std::string Base::getClassName() const {
	return __object_className;
}

Base::ObjectContainer& Base::ObjectContainer::get() {
	static ObjectContainer _instance;
	return _instance;
}

void Base::ObjectContainer::add(std::shared_ptr<Base>& r) {
	Base::ObjectContainer::get()._database[r->getClassName()][r->getID()] = r;
	Base::ObjectContainer::get()._membership[r->getID()] = r->getClassName();

	if (std::shared_ptr<Drawable> x = std::dynamic_pointer_cast<Drawable>(r)) {
		Base::ObjectContainer::get().tasks._objectDraws[r->getID()] = Functor([x]() { x->drawObject(); });
	}
	if (std::shared_ptr<Updateable> x = std::dynamic_pointer_cast<Updateable>(r)) {
		Base::ObjectContainer::get().tasks._objectUpdates[r->getID()] = Functor([x]() { x->updateObject(); });
	}
	if (std::shared_ptr<Moveable> x = std::dynamic_pointer_cast<Moveable>(r)) {
		Base::ObjectContainer::get().tasks._objectMoves.insert(r->getID());
	}
	if (std::shared_ptr<Collidable> x = std::dynamic_pointer_cast<Collidable>(r)) {
		Base::ObjectContainer::get().tasks._objectWithCollisions.insert(r->getID());
	}
	if (std::shared_ptr<Eventable> x = std::dynamic_pointer_cast<Eventable>(r)) {
		Base::ObjectContainer::get().tasks._objectsWithEventsAssociatedWithFunctions.insert(r->getID());
	}
}

void Base::ObjectContainer::remove(uint64_t _id) {

	// deleting every instance of an object
	Base::ObjectContainer::get().tasks	._objectMoves.erase(_id);
	Base::ObjectContainer::get().tasks	._objectDraws.erase(_id);
	Base::ObjectContainer::get().tasks	._objectUpdates.erase(_id);
	Base::ObjectContainer::get().tasks	._objectWithCollisions.erase(_id);
	Base::ObjectContainer::get().tasks	._objectsWithEventsAssociatedWithFunctions.erase(_id);

	std::string _className = Base::ObjectContainer::get()._membership[_id];

	Base::ObjectContainer::get()		._database[_className].erase(_id);
	Base::ObjectContainer::get()		._membership.erase(_id);

}

