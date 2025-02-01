export module Animatable;

import Globals;
import Textureable;

import Exceptions;

template <typename T>
	requires std::is_convertible_v<std::string, T>
std::vector<T> split(std::string str, const char divider = ' ') {
	std::vector<T> matches;

	std::string::iterator i = std::find(str.begin(), str.end(), divider);
	while (i != str.end()) {
		matches.push_back(std::string{ str.begin(), i });
		str.erase(str.begin(), i + 1);
		i = std::find(str.begin(), str.end(), divider);
	}

	return matches;
}

struct forward_frame {
	std::vector<std::filesystem::path> _animation_files;
	unsigned int _time_in_miliseconds;

	std::vector<std::filesystem::path>::iterator _texture_index;

	forward_frame(std::vector<std::filesystem::path> _af, unsigned int _tim)
		: _animation_files(_af), _time_in_miliseconds(_tim)
	{
		//_texture_index = _animation_files.begin();
	}

	void increment_texture_index() {
		if (_texture_index != _animation_files.end() - 1)
			_texture_index++;
		else _texture_index = _animation_files.begin();
	}

};

export class Animatable : public virtual Textureable {
	std::filesystem::path _directive_file_path;
	std::unordered_map<std::string, forward_frame> _animation_data;

	std::unordered_map<std::string, forward_frame>::iterator _animation_index;

	sf::Int32 _anim_last_change = globalClock.getElapsedTime().asMilliseconds();

public:
	Animatable(std::filesystem::path _dfp) : Textureable() {
		if (!std::filesystem::exists(_dfp))
			throw nonexistend_path_or_file();
		if (_dfp.extension() != ".txt")
			throw bad_extension_file();

		_directive_file_path = _dfp;

		std::ifstream _file_ad(_directive_file_path);
		
		std::smatch matches;
		std::regex pattern{ 
			R"(\s*([._\-[:alnum:]]+)\s*\[[ ]?(([._\-[:alnum:]]+[ ]?)*)\]\s+\[(\d+)\]$)" 
		};

		std::string file_line = "";
 
		while (!_file_ad.eof()) {
			std::getline(_file_ad, file_line);
			
			if (std::regex_match(file_line, pattern))
				std::regex_search(file_line, matches, pattern);
			else
				throw invalid_file_format();

			forward_frame animation_element(
				split<std::filesystem::path>(matches[2]), stoul(matches[4].str())
			);
			_animation_data.insert(std::make_pair(matches[1].str(), animation_element));

		}

		_file_ad.close();

		_animation_index = _animation_data.begin();
		_animation_index->second._texture_index = _animation_index->second._animation_files.begin();
		// wierd but it works, thought I could do that in constructor but it didn't work

		this->change_file(*_animation_index->second._texture_index);

	}

	void changeAnimation(std::string&& animation_name) {
		if (_animation_data.contains(animation_name)) {
			while (_animation_index->first != animation_name) {
				++_animation_index;
			}
		}
		else throw invalid_animation_name_argument();
	}

	void animateObject() {
		sf::Int32 elapsedTime = globalClock.getElapsedTime().asMilliseconds();
		if (elapsedTime - _anim_last_change > _animation_index->second._time_in_miliseconds) {
			_anim_last_change = elapsedTime;

			_animation_index->second.increment_texture_index(); // safer than ++_texture_index
			this->change_file(*_animation_index->second._texture_index);
			
		}
	}

};