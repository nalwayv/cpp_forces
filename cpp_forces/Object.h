#pragma once

#include <SFML/Graphics.hpp>

namespace force {
	class Object
	{
	private:
		sf::Vector2f position_;
		sf::Vector2f velocity_;
		sf::Vector2f total_forces_;

		sf::Vertex v_line_[2];

		float radius_;
		float max_speed_;
		float angle_;
		float mass_;
		float friction_;

		sf::Vector2f mouse_pos_;
		bool is_active_;
		bool apply_wind_right_;
		bool apply_wind_left_;
		bool apply_lift_;
		bool apply_drag_;

	private:
		void apply_forces();
		void screen_wrap(float width, float height);
		void clear_total_forces_();

	public:
		Object(sf::Vector2f pos, float radius, float mass);
		void set_mouse_position(sf::Vector2f new_position);
		void apply_wind(bool value, bool is_right);
		void apply_lift(bool value);
		void apply_drag(bool value);

		const float get_radius() const;
		const float get_angle() const;
		const sf::Vector2f get_position() const;

		void draw(sf::RenderWindow& window);

		void update_euler(float dt);
	};
}
