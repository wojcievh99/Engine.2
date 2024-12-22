export module Engine;

export import Globals;

import Base;
import ObjectContainer;
import Concepts;

// all implementations in Engine.cpp
export class Engine {
	std::mutex _deleteMutex;

	// algorithms/calls for handling all tasks:
	void checkAndExecuteEventsInAllObjects();
	void moveAllObjects();

	void drawAllObjects();
	void updateAllObjects();
	void deleteAllObjects();
	
	Engine() = default;
	~Engine() = default;

public:
	Engine(const Engine&) = delete;
	Engine& operator=(const Engine&) = delete;

	static Engine& get();

	template<Derived T, typename... Args>
	std::weak_ptr<T> create(Args&&... args) {

		auto object = std::make_shared<T>(std::forward<Args>(args)...);
		auto projected_to_base = std::static_pointer_cast<Base>(object);
		ObjectContainer::get().add(projected_to_base);

		std::weak_ptr<T> result = object;
		return std::move(result);
	}

	void init(
		std::pair<unsigned int, unsigned int> _windowSize, std::string _windowName,
		bool _resizable = false, unsigned int _framerate = 60, unsigned int _pd = 1);

	void run();

};


// for future development:
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