export module Textureable;

import Globals;
import Base;
import GraphContainer;

import Exceptions;

// facing: right, left, up or down
export enum class XA { RIGHT, LEFT };
export enum class YA { UP, DOWN };

export class Textureable : public virtual Base {
	sf::Texture tex;

	std::filesystem::path folder_path;
	std::filesystem::path current_tex_file;

	std::pair<XA, YA> current_face;

public:
	Textureable() {};

	Textureable(std::filesystem::path _path, sf::Vector2f _scale = sf::Vector2f(1.f, 1.f), 
		std::filesystem::path _file = "")
		: folder_path(_path), current_tex_file(_file), current_face(XA::RIGHT, YA::UP)
	{
		setObject(object_type::SPRITE);
		getObject<sf::Sprite>()->scale(abs(_scale.x), abs(_scale.y));

		if (current_tex_file != "") 
			change_file(current_tex_file);

	};

	Textureable(std::filesystem::path _path, float _scaleX = 1.f, float _scaleY = 1.f, 
		std::filesystem::path _file = "")
		: folder_path(_path), current_tex_file(_file)
	{
		setObject(object_type::SPRITE);
		getObject<sf::Sprite>()->scale(abs(_scaleY), abs(_scaleY));

		if (current_tex_file != "") 
			change_file(current_tex_file);

	};

	void change_file(std::filesystem::path _file) {
		current_tex_file = _file; 
		
		if (!std::filesystem::exists(folder_path / current_tex_file))
			throw nonexistend_file_indirective();

		// safe loading
		tex.loadFromFile((folder_path / current_tex_file).string());
		getObject<sf::Sprite>()->setTexture(tex);
		getObject<sf::Sprite>()->setOrigin(tex.getSize().x / 2.f, tex.getSize().y / 2.f);

	}

	void change_folder_path(std::filesystem::path _folder) {
		folder_path = _folder; current_tex_file = "";
	}

	sf::Vector2f getTextureSize() {
		return getObject<sf::Sprite>()->getGlobalBounds().getSize();
	}

	void turn_sprite_x(XA x) {
		if (current_face.first != x)
			getObject<sf::Sprite>()->scale(-1.f, 1.f);
		current_face.first = x;
	}
	void turn_sprite_y(YA y) {
		if (current_face.second != y)
			getObject<sf::Sprite>()->scale(1.f, -1.f);
		current_face.second = y;
	}
};