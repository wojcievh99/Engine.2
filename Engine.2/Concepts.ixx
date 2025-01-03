export module Concepts;

import std;

// designed for Base.ixx and Base.cpp
// concept of a class that resembles/inherits from Base
// only class Base itself meets this conditions in this project
export template<typename D>
concept Derived = requires (D d) {
	{ d.getType() } -> std::convertible_to<std::type_index>;
	{ d.getID() } -> std::convertible_to<std::uint64_t>;
};

export template <typename P>
concept Positionable = requires (P p) {
	{ p.setPosition };
	{ p.getPosition };
};

export template <typename P>
concept Pointer = std::is_pointer_v<P>;

export template <typename D>
concept DrawableDerived = requires (D d) {
	{ d->draw };
};