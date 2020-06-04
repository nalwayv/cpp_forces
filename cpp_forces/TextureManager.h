#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <map>
#include <string>

// TODO: 
namespace force {
	class TextureManager
	{
	private:
		std::map<std::string, std::unique_ptr<sf::Texture>> texture_data_;

	public:
		TextureManager();
		void load(std::string id, std::string file_path);
		void remove(std::string id);
		const sf::Texture& get(std::string id)const;
	};
}
