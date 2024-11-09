export module Concepts;

import std;

export template <typename T>
concept Base2D = requires (T t) {
	t.getID;
	t.getClassName;
};

export template <typename P>
concept Positionable = requires (P p) {
	{ p.getPosition().lock()->getPosition().x } -> std::convertible_to<float>;
	{ p.getPosition().lock()->getNumber().x } -> std::convertible_to<unsigned int>;
};
