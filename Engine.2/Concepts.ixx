export module Concepts;

import std;

export template<typename D>
concept Derived = requires (D d) {
	{ d.getClassName() } -> std::convertible_to<std::string>;
	{ d.getID() } -> std::convertible_to<std::uint64_t>;
};