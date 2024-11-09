export module Base;

export import Globals;
export import GraphContainer;

export class Base {
	std::string __object_className;
	std::uint64_t __object_id;
protected:
	std::shared_ptr<GraphPoint> _position;
	bool _object_alive;
public:
	Base(std::string _className = "!", sf::Vector2u _pos = sf::Vector2u(0, 0))
		: __object_className(_className)
	{
		_graph.getPoint(_pos, _position);

		this->__object_id = ++globalID; _object_alive = true;
		std::cout << "[ID: " << __object_id << ", className: " << __object_className << "](+) \n";
	}
	~Base() {
		std::cout << "[ID: " << __object_id << ", className: " << __object_className << "](-) \n";
	}

	std::shared_ptr<GraphPoint> getPosition() {
		return _position;
	}
	std::uint64_t getID() {
		return __object_id;
	}
	std::string getClassName() {
		return __object_className;
	}

	bool isObjectAlive() {
		return _object_alive;
	}
	virtual void garbage() {
		std::cout << "[ID: " << __object_id << "](-) \n";
	}
};
