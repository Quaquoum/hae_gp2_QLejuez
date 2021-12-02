#pragma once

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/Sprite.hpp"


class Character {
public:
	sf::Sprite spr;
	sf::FloatRect cHitBox;

	bool visible = true;

	std::vector<float>	px;
	std::vector<float>	py;

	std::vector<float>	dx;
	std::vector<float>	dy;

	std::vector<bool>	alive;

	void update(double dt);

	void jump();
	void move();
	void attack();

	void draw(sf::RenderWindow& win);
};