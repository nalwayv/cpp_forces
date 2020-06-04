#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>
#include <cmath>
#include <algorithm>
#include <random>
#include <toml.hpp>
#include <tuple>
#include "Object.h"
#include "TextureManager.h"
#include "BoxArea.h"
#include "V2.h"

// USING
using sf::RenderWindow;
using sf::VideoMode;
using sf::Vector2f;
using sf::Event;
using sf::Keyboard;
using sf::Clock;
using sf::Color;
using sf::CircleShape;
using sf::RectangleShape;
using sf::Sprite;
using force::Object;
using force::TextureManager;
using force::BoxArea;
using force::V2;
using std::cout;
using std::endl;
using std::string;
using std::acosf;
using std::min;
using std::max;
using std::tuple;
using std::make_tuple;

const float PI = acosf(-1);

float CorrectDegrees(float degrees) {
    while (degrees > 360.0f) {
        degrees -= 360.0f;
    }

    while (degrees < -360.0f) {
        degrees += 360.0f;
    }

    return degrees;
}

float r2d(float radians) {
    float degrees = radians * 57.295754f;
    degrees = CorrectDegrees(degrees);
    return degrees;
}

float d2r(float degrees) {
    degrees = CorrectDegrees(degrees);
    float radians = degrees * 0.0174533f;
    return radians;
}

float random_range(float min_value, float max_value)
{
    float min_v = min(min_value, max_value);
    float max_v = max(min_value, max_value);

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<float> range(min_v, max_v);

    return range(mt);
}

bool aabb(BoxArea const& a, BoxArea const& b) {
    auto aMin = a.get_min();
    auto aMax = a.get_max();
    auto bMin = b.get_min();
    auto bMax = b.get_max();

    auto check_x = bMin.x <= aMax.x && aMin.x <= bMax.x;
    auto check_y = bMin.y <= aMax.y && aMin.y <= bMax.y;


    return check_x && check_y;
}

bool cir_rect(BoxArea const& rect, Vector2f c_pos, float c_rad) {
    auto vmin = rect.get_min();
    auto vmax = rect.get_max();

    Vector2f cp = c_pos;
    cp.x = (cp.x < vmin.x) ? vmin.x : cp.x;
    cp.x = (cp.x > vmax.x) ? vmax.x : cp.x;

    cp.y = (cp.y < vmin.y) ? vmin.y : cp.y;
    cp.y = (cp.y > vmax.y) ? vmax.y : cp.y;

    return V2::v2_len_sq(cp - c_pos) <= (c_rad * c_rad);
}

// get ball data from toml file
tuple<float, float, float, float> parse_tome(string file_path, string name) {
    
    
    try {
        auto data = toml::parse(file_path);
    
        if (data.contains(name)) 
        {
            auto obj_name = toml::find(data, name);
            auto pos_x = toml::find_or<float>(obj_name, "position_x", 0.0);
            auto pos_y = toml::find_or<float>(obj_name, "position_y", 0.0);
            auto mass = toml::find_or<float>(obj_name, "mass", 0.0);
            auto radius = toml::find_or<float>(obj_name, "radius", 0.0);

            return make_tuple(pos_x, pos_y, radius,  mass);
        }
        
    }
    catch (std::exception e) {
        cout << "ERROR >> " << e.what() << endl;
    }

    return make_tuple(0.0f, 0.0f, 0.0f, 0.0f);

}

CircleShape new_circle(Vector2f pos, Color color, float radius) {
    CircleShape circle(radius, 16);
    circle.setFillColor(color);
    circle.setOrigin(Vector2f(radius * 0.5f, radius * 0.5f));
    circle.setOutlineColor(Color::Black);
    circle.setOutlineThickness(1.5f);

    return circle;
}

int main()
{
    cout << "FORCES!\n";

    RenderWindow window(VideoMode(500, 500), "FORCES");
    window.setFramerateLimit(60);
    window.setMouseCursorVisible(true);
    bool is_paused = false;
    Clock clock;

    // 
    TextureManager tm;
    tm.load("bg", "../assets/bg.png");

    Sprite sp(tm.get("bg"));
    auto data_a = parse_tome("../config.toml", "ball_a");
    Object obj1(Vector2f(std::get<0>(data_a), std::get<1>(data_a)), std::get<2>(data_a), std::get<3>(data_a));
    auto circle1 = new_circle(obj1.get_position(), Color::Red, obj1.get_radius());

    auto data_b = parse_tome("../config.toml", "ball_b");
    Object obj2(Vector2f(std::get<0>(data_b), std::get<1>(data_b)), std::get<2>(data_b), std::get<3>(data_b));
    auto circle2 = new_circle(obj2.get_position(), Color::Green, obj2.get_radius());

    Vector2f mouse_pos(0.0, 0.0);

    BoxArea water_box(Vector2f(10.0f, 400.0f), Vector2f(480.0f, 90.0f));

    while (window.isOpen()) {

        Event event;

        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }

            if (event.type == Event::KeyPressed) {
                if (event.key.code == Keyboard::Escape) {
                    window.close();
                }

                if (event.key.code == Keyboard::P) {
                    is_paused = !is_paused;
                }

                if (event.key.code == Keyboard::D) {
                    obj1.apply_wind(true, true);
                    obj2.apply_wind(true, true);
                }

                if (event.key.code == Keyboard::A) {
                    obj1.apply_wind(true, false);
                    obj2.apply_wind(true, false);
                }

                if (event.key.code == Keyboard::W) {
                    obj1.apply_lift(true);
                    obj2.apply_lift(true);
                }
            }

            if (event.type == Event::KeyReleased) {
                if (event.key.code == Keyboard::D) {
                    obj1.apply_wind(false, true);
                    obj2.apply_wind(false, true);
                }

                if (event.key.code == Keyboard::A) {
                    obj1.apply_wind(false, false);
                    obj2.apply_wind(false, false);
                }

                if (event.key.code == Keyboard::W) {
                    obj1.apply_lift(false);
                    obj2.apply_lift(false);
                }
            }

            if (event.type == Event::MouseMoved) {
                // get current mouse position.
                auto m = sf::Mouse::getPosition(window);
                mouse_pos.x = static_cast<float>(m.x);
                mouse_pos.y = static_cast<float>(m.y);
            }
        }

        if (!is_paused) {
            auto dt = clock.restart().asSeconds();

            // UPDATE ---
            obj1.update_euler(dt);
            obj2.update_euler(dt);

            circle1.setPosition(obj1.get_position());
            circle2.setPosition(obj2.get_position());

            // apply drag
            if (cir_rect(water_box, obj1.get_position(), obj1.get_radius())) {
                obj1.apply_drag(true);
            }
            else {
                obj1.apply_drag(false);
            }
            if (cir_rect(water_box, obj2.get_position(), obj2.get_radius())) {
                obj2.apply_drag(true);
            }
            else {
                obj2.apply_drag(false);
            }

            // RENDER ---
            window.clear(Color(21, 21, 21,255));
            window.draw(sp);

            window.draw(circle1);
            window.draw(circle2);

            water_box.draw(window);

            // draw velocity line
            obj1.draw(window);
            obj2.draw(window);

            window.display();
            // 

        }
        else {
            clock.restart();
        }
    }
}

