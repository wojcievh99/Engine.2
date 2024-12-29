export module Base;

import Globals;
import GraphContainer;

import Concepts;

export class Base {
	std::uint64_t __object_id;
protected:
	std::weak_ptr<GraphPoint> _position;

public:
	Base(sf::Vector2u _pos = sf::Vector2u(0, 0)) {
		GraphContainer::get().getPoint(_pos, _position);
		this->__object_id = ++globalID;
	}
	virtual ~Base() = default;

	void _setSize(sf::RectangleShape& r, sf::Vector2u _size) {
		auto graph_point_distance = GraphContainer::get().getGraphPointDistance();
		r.setSize(sf::Vector2f(_size.x * graph_point_distance, _size.y * graph_point_distance));
	}
	void _setRadius(sf::CircleShape& c, float r) {
		auto graph_point_distance = GraphContainer::get().getGraphPointDistance();
		c.setRadius(r * graph_point_distance);
	}

	template <Positionable P>
	void correctPosition(P& body) {
		body.setPosition(_position.lock()->getPosition());
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
