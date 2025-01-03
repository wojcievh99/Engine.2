export module Base;

import Globals;
import GraphContainer;

import Concepts;

export enum class object_type { RECTANGLE, CIRCLE, SPRITE, NONE };

// union for objects; not 
class DefinedObjectUnion {
	object_type union_type;
	std::variant<
		std::shared_ptr<sf::RectangleShape>, 
		std::shared_ptr<sf::CircleShape>, 
		std::shared_ptr<sf::Sprite>
	> union_value;

	void allocate(const object_type _type) {
		union_type = _type;

		if (_type == object_type::RECTANGLE)
			union_value.emplace<std::shared_ptr<sf::RectangleShape>>(std::make_shared<sf::RectangleShape>());
		else if (_type == object_type::CIRCLE)
			union_value.emplace<std::shared_ptr<sf::CircleShape>>(std::make_shared<sf::CircleShape>());
		else if (_type == object_type::SPRITE)
			union_value.emplace<std::shared_ptr<sf::Sprite>>(std::make_shared<sf::Sprite>());

	}

public:
	DefinedObjectUnion() : union_type(object_type::NONE) {};

	template <typename T>
	std::shared_ptr<T>& get() {
		if (std::holds_alternative< std::shared_ptr<T> >(union_value))
			return std::get< std::shared_ptr<T> >(union_value);
		else
			throw std::bad_variant_access();
	}
	const object_type getType() const {
		return union_type;
	}



	friend class Base;
};

// Every user created object has to inherit from this class
// All basics traits are here
export class Base {
	std::uint64_t __object_id;
protected:
	DefinedObjectUnion _object;
	std::weak_ptr<GraphPoint> _position;

public:
	Base(sf::Vector2u _pos = sf::Vector2u(0, 0)) {
		GraphContainer::get().getPoint(_pos, _position);
		this->__object_id = ++globalID;
	}
	virtual ~Base() = default;

	bool setObject(const object_type&& _type) {
		if (_object.getType() != object_type::NONE or _type == object_type::NONE) return false;
		_object.allocate(_type);
		
		if (_type == object_type::RECTANGLE)
			correctPosition<sf::RectangleShape>(_object.get<sf::RectangleShape>());
		else if (_type == object_type::CIRCLE)
			correctPosition<sf::CircleShape>(_object.get<sf::CircleShape>());
		else if (_type == object_type::SPRITE)
			correctPosition<sf::Sprite>(_object.get<sf::Sprite>());

		return true;
	}

	// Use when specifing size
	// Choose the correct function for user's case
	void _setSize(sf::Vector2u _size) {
		auto graph_point_distance = GraphContainer::get().getGraphPointDistance();

		if (_object.getType() == object_type::RECTANGLE)
			_object.get<sf::RectangleShape>()->setSize(
				sf::Vector2f(_size.x * graph_point_distance, _size.y * graph_point_distance)
			);

	}
	void _setRadius(float r) {
		auto graph_point_distance = GraphContainer::get().getGraphPointDistance();

		if (_object.getType() == object_type::CIRCLE)
			_object.get<sf::CircleShape>()->setRadius(r * graph_point_distance);

	}

	// Use when position of body in user's object 
	// might differ from the true position
	template <Positionable T>
	void correctPosition(std::shared_ptr<T>& body) {
		body->setPosition(_position.lock()->getPosition());
	}

	std::weak_ptr<GraphPoint> getPosition() const {
		return _position;
	};
	std::uint64_t getID() const {
		return __object_id;
	};
	virtual std::type_index getType() {
		return typeid(*this);
	}
};
