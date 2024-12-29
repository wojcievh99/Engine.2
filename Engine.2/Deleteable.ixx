export module Deleteable;

import ObjectContainer;
import Base;

export class Deleteable : public virtual Base {
public:
	void deleteObject() {
		ObjectContainer::get().getBin().push_back(getID());
	}
};