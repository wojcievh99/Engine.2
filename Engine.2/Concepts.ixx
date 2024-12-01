export module Concepts;

import std;

// designed for Base.ixx and Base.cpp
// concept of a class that resembles/inherits from Base
// only class Base itself meets this conditions in this project
export template<typename D>
concept Derived = requires (D d) {
	{ d.getClassName() } -> std::convertible_to<std::string>;
	{ d.getID() } -> std::convertible_to<std::uint64_t>;
};