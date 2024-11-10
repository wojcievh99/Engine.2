export module Engine;

import Globals;
import ObjectContainer;

import GraphContainer;

export class Engine {
	std::unique_ptr<sf::Event> _event;
	std::mutex _deleteMutex;

	void checkAndExecuteEventsInAllObjects() {
		while (window->pollEvent(*_event)) {
			if (_event->type == sf::Event::Closed) {

				window->close();
				break;

			}
			for (std::pair<uint64_t, std::weak_ptr<Eventable>> e : oc._objectsWithEventsAssociatedWithFunctions) {
				if (!e.second.lock()->isLocked()) {

					for (auto const& [key, func] : e.second.lock()->_keyAssociation)
						if (!e.second.lock()->_lockedIndKeys.contains(key)
							and _event->type == sf::Event::KeyPressed and _event->key.code == key)
						{
							Functor f = func; f();
						}
					for (auto const& [key, func] : e.second.lock()->_rKeyAssociation)
						if (!e.second.lock()->_lockedIndKeys.contains(key)
							and _event->type == sf::Event::KeyReleased and _event->key.code == key)
						{
							if (!e.second.lock()->_lockedIndKeyRelease.contains(key)) {
								Functor f = func; f();
							}
							else e.second.lock()->_lockedIndKeyRelease.erase(key);
						}
					for (auto const& [button, func] : e.second.lock()->_buttonAssociation)
						if (!e.second.lock()->_lockedIndButtons.contains(button)
							and _event->type == sf::Event::MouseButtonPressed and _event->mouseButton.button == button)
						{
							Functor f = func; f();
						}
					for (auto const& [button, func] : e.second.lock()->_rButtonAssociation)
						if (!e.second.lock()->_lockedIndButtons.contains(button)
							and _event->type == sf::Event::MouseButtonReleased and _event->mouseButton.button == button)
						{
							if (!e.second.lock()->_lockedIndButtonRelease.contains(button)) {
								Functor f = func; f();
							}
							else e.second.lock()->_lockedIndButtonRelease.erase(button);
						}

				}
			}
		}
	}
	void drawAllObjects() {
		for (auto const& e : oc._objectDraws) {
			Functor f = e.second; f();
		}
	}
	void moveAllObjects() {
		for (auto const& e : oc._objectMoves) {
			e.second.lock()->accelerateObject();
			if (oc._objectWithCollisions.count(e.first)) {
				if (oc._objectWithCollisions[e.first].lock()->checkNextMove(e.second.lock()->getMoveDir())) {
					e.second.lock()->moveObject();
					oc._objectWithCollisions[e.first].lock()->moveBound(e.second.lock()->getMoveDir());
				}
				else {
					oc._objectWithCollisions[e.first].lock()->afterCollision();
				}
			}
			else e.second.lock()->moveObject();
		}
	}
	void updateAllObjects() {
		for (auto const& e : oc._objectUpdates) {
			Functor f = e.second; f();
		}
	}
	void deleteAllObjects() {
		for (auto const& [className, element] : oc._database) {
			for (auto const& [id, object] : element) {
				try {
					if (object == nullptr) throw std::exception("Object Terminated.");
					if (!object->isObjectAlive()) {

						_deleteMutex.lock();
						oc.deleteObject(object->getID());
						_deleteMutex.unlock();

						break;
					}
				}
				catch (const std::exception& err) {
					break;
				}
			}
		}
	}

public:
	Engine() {
		std::cout << "<- Engine Loading... ->\n";
	}

	template <Base2D T>
	std::weak_ptr<T> addObject(std::shared_ptr<Base>&& ob) {
		oc.insertObject(ob);
		return std::weak_ptr<T>(std::dynamic_pointer_cast<T>(std::move(ob)));
	}

	bool init(
		std::pair<unsigned int, unsigned int> _windowSize, std::string _windowName, 
		bool _resizable = false, unsigned int _framerate = 60, unsigned int _pd = 1.0f) 
	{

		window = std::make_unique<sf::RenderWindow>
			(
				sf::VideoMode(_windowSize.first, _windowSize.second),
				_windowName, _resizable ? (sf::Style::Default) : (sf::Style::Close)
			);

		__framerate = _framerate; 
		__graphPointDistance = _pd;

		window->setFramerateLimit(__framerate);
		window->setVerticalSyncEnabled(true);
		window->setKeyRepeatEnabled(false);
		window->setPosition({ 0,0 });

		_event = std::make_unique<sf::Event>();

		std::cout << "<- Engine Loaded ->\n";
		return true;
	}

	void run() {
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

} inline engine;

/*try {
						if (viewLock) {
							std::weak_ptr<Base> _viewObject = oc._database[viewObjectData.first][viewObjectData.second];
							if (_viewObject.lock() == nullptr) throw std::exception("ViewObject terminated.");
							view.reset(sf::FloatRect(
								int(_viewObject.lock()->getPosition()->getPosition().x),
								int(_viewObject.lock()->getPosition()->getPosition().x),
								int(window->getSize().x), int(window->getSize().y)
							));
							view.setCenter(
								_viewObject.lock()->getPosition()->getPosition().x,
								_viewObject.lock()->getPosition()->getPosition().y
							);
							window->setView(view);

						}
					}
					catch (const std::exception& err) {
						viewLock = false;
					}*/