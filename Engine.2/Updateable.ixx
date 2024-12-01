export module Updateable;

import Globals;

// inherit from it in your object if your object 
// should update before every frame
export class Updateable {
public:
	virtual void updateObject() = 0;
};