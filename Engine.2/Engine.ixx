export module Engine;

import Globals;
import Base;

import Moveable;
import Collidable;
import Eventable;

export class Engine {
	std::unique_ptr<sf::Event> _event;
	std::mutex _deleteMutex;

	void checkAndExecuteEventsInAllObjects() {
		while (window->pollEvent(*_event)) {
			if (_event->type == sf::Event::Closed) {

				window->close();
				break;

			}
			for (uint64_t e : Base::ObjectContainer::get().tasks.events()) {
		
				auto evn_object = std::dynamic_pointer_cast<Eventable>(
					Base::ObjectContainer::get().getObjectByID(e)
				);

				if (!evn_object->isLocked()) {

					for (auto const& [key, func] : evn_object->_keyAssociation)
						if (!evn_object->_lockedIndKeys.contains(key)
							and _event->type == sf::Event::KeyPressed and _event->key.code == key)
						{
							Functor f = func; f();
						}
					for (auto const& [key, func] : evn_object->_rKeyAssociation)
						if (!evn_object->_lockedIndKeys.contains(key)
							and _event->type == sf::Event::KeyReleased and _event->key.code == key)
						{
							if (!evn_object->_lockedIndKeyRelease.contains(key)) {
								Functor f = func; f();
							}
							else evn_object->_lockedIndKeyRelease.erase(key);
						}
					for (auto const& [button, func] : evn_object->_buttonAssociation)
						if (!evn_object->_lockedIndButtons.contains(button)
							and _event->type == sf::Event::MouseButtonPressed and _event->mouseButton.button == button)
						{
							Functor f = func; f();
						}
					for (auto const& [button, func] : evn_object->_rButtonAssociation)
						if (!evn_object->_lockedIndButtons.contains(button)
							and _event->type == sf::Event::MouseButtonReleased and _event->mouseButton.button == button)
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
	void drawAllObjects() {
		for (auto const& e : Base::ObjectContainer::get().tasks.draws()) {
			Functor f = e.second; f();
		}
	}
	void moveAllObjects() {
		for (auto const& e : Base::ObjectContainer::get().tasks.moves()) {

			auto mov_object = std::dynamic_pointer_cast<Moveable>(
				Base::ObjectContainer::get().getObjectByID(e)
			);

			if (mov_object->getMoveDir() != sf::Vector2u(0, 0))
				if (auto col_object = std::dynamic_pointer_cast<Collidable>
					( Base::ObjectContainer::get().getObjectByID(e) )
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
	void updateAllObjects() {
		for (auto const& e : Base::ObjectContainer::get().tasks.updates()) {
			Functor f = e.second; f();
		}
	}
	void deleteAllObjects() {
		for (auto const& [id, __] : Base::ObjectContainer::get().getRegister()) {
			
			std::shared_ptr<Base> object = Base::ObjectContainer::get().getObjectByID(id);
				try {
					if (object == nullptr) throw std::exception("Object Terminated.");
					if (!object->isObjectAlive()) {

						_deleteMutex.lock();
						Base::ObjectContainer::get().remove(object->getID());
						_deleteMutex.unlock();

						break;
					}
				}
				catch (const std::exception& err) {
					break;
				}
			
		}
	}
	
	Engine() = default;
	~Engine() = default;

public:
	Engine(const Engine&) = delete;
	Engine& operator=(const Engine&) = delete;

	inline static Engine& get() {
		static Engine _instance;
		return _instance;
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

};

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