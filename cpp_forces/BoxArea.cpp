#include "BoxArea.h"
#include <algorithm>

using force::BoxArea;
using sf::Vector2f;
using sf::RectangleShape;
using sf::Color;
using std::min;
using std::max;

BoxArea::BoxArea(Vector2f position, Vector2f size)
	:origin_(position),
	size_(size),
	offset_(size.x * 0.5f, size.y * 0.5f)
{
	shape_.setPosition(origin_);
	shape_.setSize(size);
	shape_.setFillColor(Color(10, 10, 220, 144));
	shape_.setOutlineColor(Color::White);
	shape_.setOutlineThickness(2.0f);
}

Vector2f BoxArea::get_size() const
{
	return size_;
}

Vector2f BoxArea::get_position() const
{
	return origin_;
}

Vector2f BoxArea::get_min() const
{
	Vector2f p1 = origin_;
	Vector2f p2 = origin_ + size_;
	return Vector2f(min(p1.x, p2.x), min(p1.y, p2.y));
}

Vector2f BoxArea::get_max() const
{
	Vector2f p1 = origin_;
	Vector2f p2 = origin_ + size_;
	return Vector2f(max(p1.x, p2.x), max(p1.y, p2.y));
}

void force::BoxArea::draw(sf::RenderWindow& window) const
{
	window.draw(shape_);
}

void force::BoxArea::update_position(sf::Vector2f pos)
{
	origin_ = pos - offset_;
}

void force::BoxArea::update()
{
	shape_.setPosition(origin_);
}
