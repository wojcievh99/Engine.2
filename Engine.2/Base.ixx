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

	// implementation in Base.cpp
	template<Derived D, typename... Args>
	static std::shared_ptr<Base> create(Args&&... args);

	// Use in constructor of every object (obligated)
	void set(std::string _className = "!", sf::Vector2u _pos = sf::Vector2u(0, 0)) {
		GraphContainer::get().getPoint(_pos, _position);
		this->__object_className = _className;
		this->__object_id = ++globalID; _object_alive = true;
	}

	// implementation in Base.cpp
	std::weak_ptr<GraphPoint> getPosition() const;

	// implementation in Base.cpp
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

class Base::ObjectContainer{

	ObjectContainer() = default;
	~ObjectContainer() = default;

	ObjectContainer(const ObjectContainer&) = delete;
	ObjectContainer& operator=(const ObjectContainer&) = delete;

	// fundamental database; not designed to use outside of this class.
	std::map<std::string, std::unordered_map<uint64_t, std::shared_ptr<Base>>> _database;
	std::unordered_map<uint64_t, std::string> _membership;

public:
	// only one instantion
	// implementation in Base.cpp
	static ObjectContainer& get();

	// designed to define object's tasks; deisigned to use outside
	ObjectHolder tasks;

	// for when there is no other option that to use fundamental database
	std::shared_ptr<Base>& getObjectByID(uint64_t _id) {
		std::string _className = _membership[_id];
		return _database[_className][_id];
	}
	const auto& getRegister() {
		return _membership;
	}

	// implementation in Base.cpp
	void add(std::shared_ptr<Base>&r);
	void remove(uint64_t _id);

};
