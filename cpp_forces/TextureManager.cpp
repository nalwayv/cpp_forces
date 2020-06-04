#include "TextureManager.h"
#include <iostream>

using force::TextureManager;
using std::make_unique;
using std::string;
using std::cout;
using std::endl;

TextureManager::TextureManager()
{
}

void TextureManager::load(string id, string file_path)
{
	auto it = texture_data_.find(id);
	if (it == texture_data_.end()) {

		auto texture = std::make_unique<sf::Texture>();
		texture->loadFromFile(file_path);

		texture_data_.insert({ id, std::move(texture) });
	}
	else {
		cout << "that id has already been used!" << endl;
	}
}

void force::TextureManager::remove(std::string id)
{
	auto it = texture_data_.find(id);
	if (it != texture_data_.end()) {
		cout << "removed {" << id << "}" << endl;
		texture_data_.erase(id);
	}
	else {
		cout << "failed to find texture with id {" << id << " }" << endl;
	}
}

const sf::Texture& TextureManager::get(string id) const
{
	auto it = texture_data_.find(id);

	if (it != texture_data_.end()) {
		return *it->second;
	}

	cout << "failed to find texture with id {" << id  <<" }"<< endl;
	// empty texture
	return sf::Texture();
}
