export module Base;

export import Globals;
import GraphContainer;

import ObjectHolder;

export class Base {
	std::string __object_className;
	std::uint64_t __object_id;
protected:
	std::weak_ptr<GraphPoint> _position;
	bool _object_alive;

	Base() = default;

public:
	
	virtual ~Base() = default;

	template<Derived D, typename... Args>
	static std::shared_ptr<Base> create(Args&&... args);

	void set(std::string _className = "!", sf::Vector2u _pos = sf::Vector2u(0, 0)) {
		GraphContainer::get().getPoint(_pos, _position);
		this->__object_className = _className;
		this->__object_id = ++globalID; _object_alive = true;
	}

	std::weak_ptr<GraphPoint> getPosition() const;

	std::uint64_t getID() const;
	std::string getClassName() const;

	class ObjectContainer;

	bool isObjectAlive() const {
		return _object_alive;
	}
	virtual void garbage() {
		std::cout << "[ID: " << __object_id << "](-) \n";
	}
};

export class Base::ObjectContainer{

	ObjectContainer() = default;
	~ObjectContainer() = default;

	ObjectContainer(const ObjectContainer&) = delete;
	ObjectContainer& operator=(const ObjectContainer&) = delete;

	std::map<std::string, std::unordered_map<uint64_t, std::shared_ptr<Base>>> _database;
	std::unordered_map<uint64_t, std::string> _membership;

public:
	static ObjectContainer& get();

	ObjectHolder tasks;

	std::shared_ptr<Base>& getObjectByID(uint64_t _id) {
		std::string _className = _membership[_id];
		return _database[_className][_id];
	}
	const auto& getRegister() {
		return _membership;
	}

	void add(std::shared_ptr<Base>&r);
	void remove(uint64_t _id);

};
