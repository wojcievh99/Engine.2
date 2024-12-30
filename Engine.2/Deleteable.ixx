export module Deleteable;

import ObjectContainer;
import Base;

// inherit from it in your object if it should be deletable
export class Deleteable : public virtual Base {
public:
	void deleteObject() {
		ObjectContainer::get().getBin().push_back(getID());
	}
};