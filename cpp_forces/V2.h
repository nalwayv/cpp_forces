#pragma once
#include <SFML/Graphics.hpp>
namespace force {
	class V2
	{
	public:
		static float v2_dot(sf::Vector2f v1, sf::Vector2f v2);
		static float v2_len(sf::Vector2f v1);
		static float v2_len_sq(sf::Vector2f v1);
		static float v2_angle(sf::Vector2f v1);
		static float v2_angle_between(sf::Vector2f v1, sf::Vector2f v2);
		static float v2_distance_between(sf::Vector2f v1, sf::Vector2f v2);
		static float v2_cross(sf::Vector2f v1, sf::Vector2f v2);
		static float V2_angle_to(sf::Vector2f v1, sf::Vector2f v2);
		//
		static sf::Vector2f v2_reflect(sf::Vector2f v1, sf::Vector2f v2);
		static sf::Vector2f v2_set_rotation(float by);
		static sf::Vector2f v2_rotation_by(sf::Vector2f v1, float by);
		static sf::Vector2f v2_set_len(sf::Vector2f v1, float len);
		static sf::Vector2f v2_set_ang(sf::Vector2f v1, float ang);
		static sf::Vector2f v2_unit(sf::Vector2f v1);
		static sf::Vector2f v2_limit_len(sf::Vector2f v1, float max_len);
	};

}