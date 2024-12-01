export module Drawable;

import Globals;

// inherit from it in your object if your object 
// should be drawn on the screen 
// and define what is supposed to be drawn
export class Drawable {
public:
	virtual void drawObject() = 0;
};