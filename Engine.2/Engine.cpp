module Engine;

import Globals;
import GraphContainer;

import Exceptions;

import Eventable;
import Moveable;
import Collidable;

unsigned int __framerate;
bool __wop;

// Gates for all threads
sf::Mutex _deleteMutexOne;
sf::Mutex _deleteMutexTwo;
sf::Mutex _deleteMutexThree;

// Only one instance of Engine is allowed
Engine& Engine::get() {
	static Engine _instance;
	return _instance;
}

// helper for handling threads
static void runThread(const std::function<void()>& operation) {
		sf::Int32 prevTime = globalClock.getElapsedTime().asMilliseconds();

		while (__wop) {
			sf::Int32 elapsedTime = globalClock.getElapsedTime().asMilliseconds();
			if (elapsedTime - prevTime > 1000 / (__framerate)) {
				prevTime = elapsedTime;

				operation();
			}
		}

}

sf::Event _event;
void Engine::checkAndExecuteEventsInAllObjects() {
	while (window->pollEvent(_event)) {
		if (_event.type == sf::Event::Closed) {

			__wop = false;
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
							Functor f = func; f();
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
							Functor f = func; f();
					}

			}
		}
	}
}
void Engine::moveAllObjectsAndCheckCollisions() {
	_deleteMutexOne.lock();
	for (auto const& e : ObjectContainer::get().tasks.moves()) {

		auto mov_object = std::dynamic_pointer_cast<Moveable>(
			ObjectContainer::get().getObjectByID(e)
		);

		if (mov_object->getMoveDir() != sf::Vector2i(0, 0))
			if (auto col_object = std::dynamic_pointer_cast<Collidable>
				(ObjectContainer::get().getObjectByID(e))
				) 
			{
				if (col_object->checkNextMove(mov_object->getMoveDir())) {
					mov_object->moveObject();
					col_object->moveBound(mov_object->getMoveDir());

					if (col_object->checkNextMove(mov_object->getMoveDir() + mov_object->getAccDir()))
						mov_object->accelerateObject();
				}
				else
				{
					sf::Vector2i _dir = mov_object->getMoveDir() - 1;
					while (!col_object->checkNextMove(_dir)) {
						_dir = _dir - 1;
					}
					if (_dir != sf::Vector2i(0, 0)) {
						mov_object->moveOnce(_dir);
						col_object->moveBound(_dir);
					}

					if (!col_object->checkNextMove(sf::Vector2i(mov_object->getMoveDir().x, 0)))
						mov_object->setMoveDirectionX(0);
					if (!col_object->checkNextMove(sf::Vector2i(0, mov_object->getMoveDir().y)))
						mov_object->setMoveDirectionY(0);

					col_object->afterCollision();
				}		
			}
			else {
				mov_object->accelerateObject();
				mov_object->moveObject();
			}
		else {
			mov_object->accelerateObject();
		}
	}
	_deleteMutexOne.unlock();
}

void Engine::drawAllObjects() {
	for (auto const& e : ObjectContainer::get().tasks.draws()) {
		Functor f = e.second; f();
	}
}
void Engine::updateAllObjects() {
	_deleteMutexThree.lock();
	for (auto const& e : ObjectContainer::get().tasks.updates()) {
		Functor f = e.second; f();
	}
	_deleteMutexThree.unlock();
}
void Engine::deleteAllObjects() {
	if (ObjectContainer::get().getBin().size()) {
		_deleteMutexOne.lock();
		_deleteMutexTwo.lock();
		_deleteMutexThree.lock();
		
		uint64_t _id = ObjectContainer::get().getBin().front();
		ObjectContainer::get().remove(_id);
		ObjectContainer::get().getBin().pop_front();

		_deleteMutexOne.unlock();
		_deleteMutexTwo.unlock();
		_deleteMutexThree.unlock();
	}
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

	try {
		if (!window) throw uninit_window_run();
		__wop = true;

		sf::Thread moveThread(runThread, &Engine::moveAllObjectsAndCheckCollisions);
		sf::Thread updateThread(runThread, &Engine::updateAllObjects);
		sf::Thread deleteThread(runThread, &Engine::deleteAllObjects);

		moveThread.launch();
		updateThread.launch();
		deleteThread.launch();

		while (__wop) {
			sf::Int32 elapsedTime = globalClock.getElapsedTime().asMilliseconds();
			if (elapsedTime - prevTime > 1000 / (__framerate)) {
				prevTime = elapsedTime;

				_deleteMutexTwo.lock();

				checkAndExecuteEventsInAllObjects();

				window->clear();
				drawAllObjects();
				window->display();

				_deleteMutexTwo.unlock();
			}
		}
		window->close();

		moveThread.wait();
		updateThread.wait();
		deleteThread.wait();

	}
	catch (const std::exception& err) {
		std::cerr << "Fatal Error: " << red << err.what() << reset << std::endl;
		return;
	}

}
