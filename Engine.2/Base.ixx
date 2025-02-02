export module Base;

import Globals;
import GraphContainer;

import Concepts;
import Exceptions;

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
	DefinedObjectUnion __object;

protected:
	std::weak_ptr<GraphPoint> _position;

public:
	Base(sf::Vector2i _pos = sf::Vector2i(0, 0)) {
		GraphContainer::get().getPoint(_pos, _position);
		this->__object_id = ++globalID;
	}
	virtual ~Base() = default;

	void setObject(const object_type&& _type) {
		if (__object.getType() != object_type::NONE or _type == object_type::NONE) 
			throw invalid_union_object();

		__object.allocate(_type);
		
		if (_type == object_type::RECTANGLE)
			correctPosition<sf::RectangleShape>(__object.get<sf::RectangleShape>());
		else if (_type == object_type::CIRCLE)
			correctPosition<sf::CircleShape>(__object.get<sf::CircleShape>());
		else if (_type == object_type::SPRITE)
			correctPosition<sf::Sprite>(__object.get<sf::Sprite>());

	}
	template <typename T>
	std::shared_ptr<T>& getObject() {
		return __object.get<T>();
	}

	// Use when specifing size
	// Choose the correct function for user's case
	void setSize(sf::Vector2i _size) {
		auto graph_point_distance = GraphContainer::get().getGraphPointDistance();

		if (__object.getType() == object_type::RECTANGLE)
			__object.get<sf::RectangleShape>()->setSize(
				sf::Vector2f(_size.x * graph_point_distance, _size.y * graph_point_distance)
			);
		else throw std::bad_variant_access();

	}
	void setRadius(float r) {
		auto graph_point_distance = GraphContainer::get().getGraphPointDistance();

		if (__object.getType() == object_type::CIRCLE)
			__object.get<sf::CircleShape>()->setRadius(r * graph_point_distance);
		else throw std::bad_variant_access();

	}

	// Use when position of body in user's object 
	// might differ from the true position
	template <Positionable T> // +
	void correctPosition(std::shared_ptr<T>& body) {
		body->setPosition(_position.lock()->getPosition());
	}

	void correctPosition_sprite(std::shared_ptr<sf::Sprite>& body) {
		body->setPosition(_position.lock()->getPosition() + body->getGlobalBounds().getSize() / 2.f );
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

	sf::Vector2i find_point_size(sf::Vector2f _realSize) {
		return sf::Vector2i(
			ceil(_realSize.x / GraphContainer::get().getGraphPointDistance()),
			ceil(_realSize.y / GraphContainer::get().getGraphPointDistance())
		);
	}
};
