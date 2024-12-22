module Engine;

import Globals;
import ObjectContainer;
import GraphContainer;

import Eventable;
import Moveable;
import Collidable;

unsigned int __framerate;

Engine& Engine::get() {
	static Engine _instance;
	return _instance;
}

sf::Event _event;
void Engine::checkAndExecuteEventsInAllObjects() {
	while (window->pollEvent(_event)) {
		if (_event.type == sf::Event::Closed) {

			window->close();
			break;

		}
		for (uint64_t e : ObjectContainer::get().tasks.events()) {

			auto evn_object = std::dynamic_pointer_cast<Eventable>(
				ObjectContainer::get().getObjectByID(e)
			);

			if (!evn_object->isLocked()) {

				for (auto const& [key, func] : evn_object->_keyAssociation)
					if (!evn_object->_lockedIndKeys.contains(key)
						and _event.type == sf::Event::KeyPressed and _event.key.code == key)
					{
						Functor f = func; f();
					}
				for (auto const& [key, func] : evn_object->_rKeyAssociation)
					if (!evn_object->_lockedIndKeys.contains(key)
						and _event.type == sf::Event::KeyReleased and _event.key.code == key)
					{
						if (!evn_object->_lockedIndKeyRelease.contains(key)) {
							Functor f = func; f();
						}
						else evn_object->_lockedIndKeyRelease.erase(key);
					}
				for (auto const& [button, func] : evn_object->_buttonAssociation)
					if (!evn_object->_lockedIndButtons.contains(button)
						and _event.type == sf::Event::MouseButtonPressed and _event.mouseButton.button == button)
					{
						Functor f = func; f();
					}
				for (auto const& [button, func] : evn_object->_rButtonAssociation)
					if (!evn_object->_lockedIndButtons.contains(button)
						and _event.type == sf::Event::MouseButtonReleased and _event.mouseButton.button == button)
					{
						if (!evn_object->_lockedIndButtonRelease.contains(button)) {
							Functor f = func; f();
						}
						else evn_object->_lockedIndButtonRelease.erase(button);
					}

			}
		}
	}
}
void Engine::moveAllObjects() {
	for (auto const& e : ObjectContainer::get().tasks.moves()) {

		auto mov_object = std::dynamic_pointer_cast<Moveable>(
			ObjectContainer::get().getObjectByID(e)
		);

		if (mov_object->getMoveDir() != sf::Vector2u(0, 0))
			if (auto col_object = std::dynamic_pointer_cast<Collidable>
				(ObjectContainer::get().getObjectByID(e))
				) {
				if (col_object->checkNextMove(mov_object->getMoveDir())) {
					mov_object->accelerateObject();
					mov_object->moveObject();
					col_object->moveBound(mov_object->getMoveDir());
				}
				else {
					col_object->afterCollision();
				}
			}
			else {
				mov_object->accelerateObject();
				mov_object->moveObject();
			}
	}
}

void Engine::drawAllObjects() {
	for (auto const& e : ObjectContainer::get().tasks.draws()) {
		Functor f = e.second; f();
	}
}
void Engine::updateAllObjects() {
	for (auto const& e : ObjectContainer::get().tasks.updates()) {
		Functor f = e.second; f();
	}
}
void Engine::deleteAllObjects() {
	
}

void Engine::init(
	std::pair<unsigned int, unsigned int> _windowSize, std::string _windowName,
	bool _resizable, unsigned int _framerate, unsigned int _pd)
{

	window = std::make_unique<sf::RenderWindow>
		(
			sf::VideoMode(_windowSize.first, _windowSize.second),
			_windowName, _resizable ? (sf::Style::Default) : (sf::Style::Close)
		);

	__framerate = _framerate;
	GraphContainer::get().setGraphPointDistance(_pd);

	window->setFramerateLimit(__framerate);
	window->setVerticalSyncEnabled(true);
	window->setKeyRepeatEnabled(false);
	window->setPosition({ 0,0 });

}


void Engine::run() {
	sf::Int32 prevTime = globalClock.getElapsedTime().asMilliseconds();

	if (window) {
		while (window->isOpen()) {
			sf::Int32 elapsedTime = globalClock.getElapsedTime().asMilliseconds();
			if (elapsedTime - prevTime > 1000 / (__framerate)) {
				prevTime = elapsedTime;

				_deleteMutex.lock();

				checkAndExecuteEventsInAllObjects();
				moveAllObjects();
				updateAllObjects();
				deleteAllObjects();

				window->clear();
				drawAllObjects();
				window->display();

				_deleteMutex.unlock();

			}
		}
	}
	else {
		std::cout << "!- Init the window -!\n";
	}

}
