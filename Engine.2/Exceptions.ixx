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

export class nonexistend_path_or_file : public std::exception {
public:
	const char* what() const noexcept override {
		return "Attempt of accesing a nonexistend path or file.";
	}
};

export class bad_extension_file : public std::exception {
public:
	const char* what() const noexcept override {
		return "Attempt of accesing a file not meeting extension conditions.";
	}
};

export class invalid_file_format : public std::exception {
public:
	const char* what() const noexcept override {
		return "Attempt of reading file with invalid format.";
	}
};

export class invalid_animation_name_argument : public std::exception {
public:
	const char* what() const noexcept override {
		return "Attempt of providing nonexistend animation.";
	}
};

export class invalid_union_object : public std::exception {
public:
	const char* what() const noexcept override {
		return "Attempt of impacting build-in union already in use or providing none type.";
	}
};

export class nonexistend_file_indirective : public std::exception {
public:
	const char* what() const noexcept override {
		return "Attempt of providing a nonexistend animation file in animation directives.";
	}
};