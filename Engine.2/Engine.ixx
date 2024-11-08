export module Engine;

import Globals;
import ObjectContainer;

import GraphContainer;

export class Engine {

	static void checkAndExecuteCollisionsInAllObjects() {
		for (std::pair<uint64_t, std::weak_ptr<Collidable>> e : oc._objectWithCollisions) {
			for (std::pair<uint64_t, std::weak_ptr<Collidable>> otherObject : oc._objectWithCollisions) {
				if (e.first != otherObject.first) {
					if (e.second.lock()->isInCollisionWith(otherObject.second)) {
						if (e.second.lock()->putObjectColliding(otherObject.second.lock())) {

							e.second.lock()->afterCollision();

						}
					}
					else if (e.second.lock()->checkCollisionList(otherObject.second.lock()))
						e.second.lock()->eraseObjectColliding(otherObject.second.lock());
				}
			}
		}
	}

	static void watchCollisionThread() {
		if (window) {

			sf::Int32 prevTime = globalClock.getElapsedTime().asMilliseconds();

			while (isWindowOpen) {
				sf::Int32 elapsedTime = globalClock.getElapsedTime().asMilliseconds();
				if (elapsedTime - prevTime > (1000 / (__framerate))) {

					prevTime = elapsedTime;

					deleteMutex.lock();
					checkAndExecuteCollisionsInAllObjects();
					deleteMutex.unlock();


				}
			}
		}
	}
	void checkAndExecuteEventsInAllObjects() {
		while (window->pollEvent(*event)) {
			if (event->type == sf::Event::Closed) {

				isWindowOpen = false;
				break;

			}
			for (std::pair<uint64_t, std::weak_ptr<Eventable>> e : oc._objectsWithEventsAssociatedWithFunctions) {
				if (!e.second.lock()->isLocked()) {

					for (auto const& [key, func] : e.second.lock()->_keyAssociation)
						if (!e.second.lock()->_lockedIndKeys.contains(key)
							and event->type == sf::Event::KeyPressed and event->key.code == key)
						{
							Functor f = func; f();
						}
					for (auto const& [key, func] : e.second.lock()->_rKeyAssociation)
						if (!e.second.lock()->_lockedIndKeys.contains(key)
							and event->type == sf::Event::KeyReleased and event->key.code == key)
						{
							if (!e.second.lock()->_lockedIndKeyRelease.contains(key)) {
								Functor f = func; f();
							}
							else e.second.lock()->_lockedIndKeyRelease.erase(key);
						}
					for (auto const& [button, func] : e.second.lock()->_buttonAssociation)
						if (!e.second.lock()->_lockedIndButtons.contains(button)
							and event->type == sf::Event::MouseButtonPressed and event->mouseButton.button == button)
						{
							Functor f = func; f();
						}
					for (auto const& [button, func] : e.second.lock()->_rButtonAssociation)
						if (!e.second.lock()->_lockedIndButtons.contains(button)
							and event->type == sf::Event::MouseButtonReleased and event->mouseButton.button == button)
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

			Functor f = e.second.first; f();
			f = e.second.second; f(); // think that through 

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

						deleteMutex.lock();
						oc.deleteObject(object->getID());
						deleteMutex.unlock();

						break;
					}
				}
				catch (const std::exception& err) {
					break;
				}
			}
		}
	}

	void createGraph(std::pair<unsigned int, unsigned int> _windowSize, unsigned int _pn) {
		sf::Int32 startT = globalClock.getElapsedTime().asSeconds();

		unsigned int _cpn = ((float)_pn / (float)_windowSize.second * (float)_windowSize.first);
		for (int line = 0; line <= _pn; line++) {
			for (int column = 0; column <= _cpn; column++) 
				_graph.addPoint(
					std::make_shared<GraphPoint>(
					sf::Vector2f(_windowSize.first / _cpn * column, _windowSize.second / _pn * line),
					sf::Vector2u(column, line))
				);
		}

		std::cout << "- GC took " << globalClock.getElapsedTime().asSeconds() - startT << " seconds -\n";
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

		event = std::make_unique<sf::Event>();

		isWindowOpen = true;

		std::cout << "<- Engine Loaded ->\n";
		return isWindowOpen;
	}

	bool lockViewOnObject(std::pair<std::string, uint64_t> _objectData) {
		if (oc._database[_objectData.first][_objectData.second] != nullptr) {
			viewObjectData = _objectData;
			return viewLock = true;
		}
		return false;
	}

	void run() {

		isWindowOpen = true;

		sf::Thread collisionThread(&watchCollisionThread);
		collisionThread.launch();

		sf::Int32 prevTime = globalClock.getElapsedTime().asMilliseconds();

		if (window) {
			window->setActive(false);

			while (isWindowOpen) {
				sf::Int32 elapsedTime = globalClock.getElapsedTime().asMilliseconds();
				if (elapsedTime - prevTime > 1000 / (__framerate)) {
					prevTime = elapsedTime;

					try {
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
					}

					//std::cout << _graph.size() << std::endl;
					checkAndExecuteEventsInAllObjects();
					moveAllObjects();
					updateAllObjects();
					deleteAllObjects();

					window->clear();
					drawAllObjects();
					window->display();
				}
			}
			window->close();

		}
		else {

			std::cout << "!- Init the window -!\n";

		}

		collisionThread.wait();

	}

} inline engine;