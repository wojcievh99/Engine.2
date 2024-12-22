export module Eventable;

import Globals;
import Functor;

// inherit from it in your object if your object 
// should respond to specified keyboards/mouse events
export class Eventable {
	bool __stopCheckingEvents;
public:
	Eventable() : __stopCheckingEvents(false) {}
	~Eventable() { clearAllAssociations(); }

	// held currently at the moment
	std::set<sf::Keyboard::Key>						_currentlyHeldKeys;
	std::set<sf::Mouse::Button>						_currentlyHeldButtons;

	// associations click key-event and click button-event
	std::unordered_map<sf::Keyboard::Key, Functor>	_keyAssociation;
	std::unordered_map<sf::Mouse::Button, Functor>	_buttonAssociation;

	// associations release key-event and release button-event
	std::unordered_map<sf::Keyboard::Key, Functor>	_rKeyAssociation;
	std::unordered_map<sf::Mouse::Button, Functor>	_rButtonAssociation;

	// if event should not happen at click for some time 
	std::set<sf::Keyboard::Key>						_lockedIndKeys;
	std::set<sf::Mouse::Button>						_lockedIndButtons;

	// if event should not happen at release for some time 
	std::set<sf::Keyboard::Key>						_lockedIndKeyRelease;
	std::set<sf::Mouse::Button>						_lockedIndButtonRelease;

	// press
	void addKeyAssociation(sf::Keyboard::Key key, Functor func) {
		func += Functor([this, key]() { this->_currentlyHeldKeys.insert(key); });
		_keyAssociation[key] = func;
	}
	void addButtonAssociation(sf::Mouse::Button button, Functor func) {
		func += Functor([this, button]() { this->_currentlyHeldButtons.insert(button); });
		_buttonAssociation[button] = func;
	}

	// release
	void addReleaseKeyAssociation(sf::Keyboard::Key key, Functor func) {
		func += Functor([this, key]() { this->_currentlyHeldKeys.erase(key); });
		_rKeyAssociation[key] = func;
	}
	void addReleaseButtonAssociation(sf::Mouse::Button button, Functor func) {
		func += Functor([this, button]() { this->_currentlyHeldButtons.erase(button); });
		_rButtonAssociation[button] = func;
	}

	void clearAllAssociations() {
		_currentlyHeldKeys.clear();
		_currentlyHeldButtons.clear();
		_keyAssociation.clear();
		_buttonAssociation.clear();
		_rKeyAssociation.clear();
		_rButtonAssociation.clear();
		_lockedIndKeys.clear();
		_lockedIndButtons.clear();
		_lockedIndKeyRelease.clear();
		_lockedIndButtonRelease.clear();
	}

	// lock/unlock every single event in object
	void lockEvents() {
		__stopCheckingEvents = true; _currentlyHeldKeys.clear(); _currentlyHeldButtons.clear();
	}
	void unlockEvents() { 
		__stopCheckingEvents = false; 
	}

	// lock/unlock specific event in object
	void lockIndEvent(sf::Keyboard::Key k) { _lockedIndKeys.insert(k); }
	void lockIndEvent(sf::Mouse::Button b) { _lockedIndButtons.insert(b); }

	void unlockIndEvent(sf::Keyboard::Key k) { _lockedIndKeys.erase(k); }
	void unlockIndEvent(sf::Mouse::Button b) { _lockedIndButtons.erase(b); }

	// lock for one time 
	// first release after calling one of those functions 
	// will not call the event but next and every other will 
	// (if it is not called again of course)
	void lockIndRelease(sf::Keyboard::Key k) {
		_lockedIndKeyRelease.insert(k); _currentlyHeldKeys.erase(k);
	}
	void lockIndRelease(sf::Mouse::Button b) {
		_lockedIndButtonRelease.insert(b); _currentlyHeldButtons.erase(b);
	}

	// check if all events are locked
	bool isLocked() { return __stopCheckingEvents; }

};