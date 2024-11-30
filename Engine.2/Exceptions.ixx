export module Exceptions;

import std;

export class InsetErrorException : public std::exception {
public:
	const char* what() const noexcept override {
		return "The inject operation at Inset went wrong.";
	}
};