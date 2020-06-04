#pragma once
#include <SFML/Graphics.hpp>
namespace force {
	class BoxArea
	{
	private:
		sf::Vector2f origin_;
		sf::Vector2f size_;
		sf::Vector2f offset_;

		sf::RectangleShape shape_;
	public:

		BoxArea(sf::Vector2f position, sf::Vector2f size);

		sf::Vector2f get_size() const;
		sf::Vector2f get_position() const;
		sf::Vector2f get_min()const;
		sf::Vector2f get_max()const;

		void draw(sf::RenderWindow& window) const;
		void update_position(sf::Vector2f pos);
		void update();
	};
}


