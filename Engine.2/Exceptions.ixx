export module Exceptions;

import std;

export class uninit_window_create : public std::exception {
public:
	const char* what() const noexcept override {
		return "Attempt of creating an object with uninitialised window.";
	}
};

export class uninit_window_run : public std::exception {
public:
	const char* what() const noexcept override {
		return "Attempt of running the engine without initialising the window.";
	}
};

export class accesing_nonexistend_object : public std::exception {
public:
	const char* what() const noexcept override {
		return "Attempt of accesing a nonexistend object by id.";
	}
};

export class removing_nonexistend_object : public std::exception {
public:
	const char* what() const noexcept override {
		return "Attempt of removing a nonexistend object by id.";
	}
};