#include <iostream>
#include <cmath>
#include "Object.h"
#include "V2.h"

// USING
using force::Object;
using force::V2;
using sf::Vector2f;
using std::cout;
using std::endl;
using std::powf;
using std::sqrtf;
using std::acos; // acos(-1) = PI

Object::Object(Vector2f pos, float radius, float mass)
	:position_(pos),
	velocity_(0.0f, 0.0f),
	total_forces_(0.0f, 0.0f),
	radius_(radius),
	max_speed_(150.0f),
	angle_(0.0f),
	mass_(mass),
	friction_(0.99f),
	mouse_pos_(0.0f, 0.0f),
	is_active_(true),
	apply_wind_right_(false),
	apply_wind_left_(false),
	apply_drag_(false),
	apply_lift_(false)
{

	v_line_[0] = sf::Vertex(Vector2f(0.0f, 0.0f), sf::Color::White);
	v_line_[1] = sf::Vertex(Vector2f(0.0f, 0.0f), sf::Color::White);
}

void Object::set_mouse_position(Vector2f new_position)
{
	mouse_pos_ = new_position;
}

const float Object::get_radius() const
{
	return radius_;
}

void Object::apply_wind(bool value, bool is_right)
{
	if (is_right) {
		apply_wind_right_ = value;
	}
	else {
		apply_wind_left_ = value;
	}
}

void force::Object::apply_lift(bool value)
{
	apply_lift_ = value;
}

void Object::apply_drag(bool value)
{
	apply_drag_ = value;
}

const Vector2f Object::get_position() const
{
	return position_;
}

void Object::draw(sf::RenderWindow& window)
{
	window.draw(v_line_, 2, sf::LinesStrip);
}

const float Object::get_angle() const
{
	return angle_;
}

void Object::apply_forces()
{
	/*
	// angle towards mouse pos
	auto dir = V2::v2_unit(mouse_pos_ - position_);
	// move towards target
	acceleration_ = V2::v2_set_len(dir, 50.0f);
	*/

	// clear out old
	clear_total_forces_();

	// gravity
	total_forces_ += Vector2f(0.0f, 9.81f) * mass_;
	
	//wind
	if (apply_wind_right_) {
		total_forces_ += Vector2f(10.0f, 0.0f);
	}
	else if (apply_wind_left_) {
		total_forces_ += Vector2f(-10.0f, 0.0f);
	}

	// lift
	if (apply_lift_) {
		total_forces_ += Vector2f(0.0f, -50.0f);
	}

	
	if (apply_drag_) {
		auto drag = V2::v2_unit(velocity_) * -1.0f;
		auto drag_c = 0.1f;
		auto drag_f = V2::v2_len_sq(velocity_) * 0.05f;
		drag = V2::v2_set_len(drag, drag_c * drag_f);

		total_forces_ += drag;
	}

	// fric
	//auto friction = V2::v2_set_len(V2::v2_unit(velocity_) * -1.0f, (0.95f * mass_));
	//total_forces_ += friction;
}

void Object::screen_wrap(float width, float height)
{
	if (position_.x > width - radius_) {
		position_.x = width - radius_;
		velocity_.x = velocity_.x * -1.f;
	}
	if (position_.x < radius_) {
		position_.x = radius_;
		velocity_.x = velocity_.x * -1.f;
	}

	if (position_.y > height - radius_) {
		position_.y = height - radius_;
		velocity_.y = velocity_.y * -1.f;
	}
	if (position_.y < radius_) {
		position_.y = radius_;
		velocity_.y = velocity_.y * -1.f;
	}
}

void Object::clear_total_forces_()
{
	total_forces_ *= 0.0f;
}

void Object::update_euler(float dt)
{
	if (is_active_) {
		screen_wrap(500.0f, 500.0f);
		// max speed
		velocity_ = V2::v2_limit_len(velocity_, 500.0f);

		apply_forces();

		auto acceleration_ = total_forces_ / mass_;
		auto speed = 50.0f;

		velocity_ += acceleration_ * speed * dt;
		position_ += velocity_ * 0.5f * dt;

		// visual velocity line
		v_line_[0].position = position_ + Vector2f(radius_ * 0.5f, radius_ * 0.5f);
		v_line_[1].position = position_ + V2::v2_set_len(velocity_, 50.0f);
	}
}
