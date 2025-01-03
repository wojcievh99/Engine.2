export module Textureable;

import Globals;
import Base;

export class Textureable : public virtual Base {
	sf::Texture tex;

	std::string folder_path;
	std::string current_tex_file;

public:
	Textureable(std::string _path, std::string _file = "") 
		: folder_path(_path), current_tex_file(_file) 
	{
		setObject(object_type::SPRITE);

		if (current_tex_file != "") {
			tex.loadFromFile(folder_path + "/" + current_tex_file);
			_object.get<sf::Sprite>()->setTexture(tex);
		}

	};

	void change_file(std::string _file) {
		current_tex_file = _file;
		tex.loadFromFile(folder_path + "/" + current_tex_file);
		_object.get<sf::Sprite>()->setTexture(tex);
	}

};