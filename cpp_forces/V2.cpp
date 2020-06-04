#include "V2.h"
#include <cmath>

//USING
using force::V2;
using sf::Vector2f;
using std::sqrtf;
using std::cosf;
using std::sinf;
using std::atan2f;
using std::acosf;

// dot product
float V2::v2_dot(Vector2f v1, Vector2f v2)
{
	return (v1.x * v2.x) + (v1.y * v2.y);
}

// v2 length
float V2::v2_len(Vector2f v1)
{
	return sqrtf((v1.x * v1.x) + (v1.y * v1.y));
}

// v2 length squared 
float V2::v2_len_sq(Vector2f v1)
{
	return (v1.x * v1.x) + (v1.y * v1.y);
}

float V2::v2_cross(Vector2f v1, Vector2f v2)
{
	return v1.x * v2.y - v1.y * v2.x;
}

Vector2f V2::v2_reflect(Vector2f v1, Vector2f v2)
{
	auto dot = v2_dot(v1, v2);
	return v1 - v2 * (dot * 2.0f);
}

// rotate
Vector2f V2::v2_set_rotation(float by)
{
	return Vector2f(cosf(by), sinf(by));
}

// angle from v1 to v2
float V2::V2_angle_to(Vector2f v1, Vector2f v2)
{
	return atan2f(v1.y - v2.y, v1.x - v2.x);
}

// rotation by angle
Vector2f V2::v2_rotation_by(Vector2f v1, float by)
{    
	// rotation matrix
	// [ cos - sin ]
	// [ sin + cos ]
	return Vector2f(
		(v1.x * cosf(by)) - (v1.y * sinf(by)),
		(v1.x * sinf(by)) + (v1.y * cosf(by)));
}

// angle of vector
float V2::v2_angle(Vector2f v1)
{
	return atan2f(v1.y, v1.x);
}

// angle bwteen two vectors
float V2::v2_angle_between(Vector2f v1, Vector2f v2)
{
	//return acosf(v2_dot(v1, v2) / sqrtf(v2_len_sq(v1) * v2_len_sq(v2)));
	return atan2f(v2_cross(v1, v2), v2_dot(v1, v2));
}

// distance between two vectors
float V2::v2_distance_between(Vector2f v1, Vector2f v2)
{
	return sqrtf(v2_len_sq(v1 - v2));
}

// set vector magnitude to
Vector2f V2::v2_set_len(Vector2f v1, float len)
{
	return v2_set_rotation(v2_angle(v1)) * len;
}

// set vector angle to
Vector2f V2::v2_set_ang(Vector2f v1, float ang)
{
	return v2_set_rotation(ang) * v2_len(v1);
}

// unit vector
Vector2f V2::v2_unit(Vector2f v1)
{
	auto l = v2_len_sq(v1);
	if (l != 0.0f) {
		return v1 / sqrtf(l);
	}
	return Vector2f(0.0f, 0.0f);
}

sf::Vector2f force::V2::v2_limit_len(sf::Vector2f v1, float max_len)
{
	if (v2_len_sq(v1) > max_len * max_len) {
		v1 = v2_set_len(v1, max_len);
	}

	return v1;
}
