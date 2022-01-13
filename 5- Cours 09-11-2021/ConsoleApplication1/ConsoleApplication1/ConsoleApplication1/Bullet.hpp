#pragma once

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/CircleShape.hpp"
#include "Particles.hpp"

class Bullet {
public:
	sf::CircleShape b;
	bool alive = false;

	Particles* parts[5];

	sf::FloatRect bulletHitbox;
	sf::Vector2u direction;

	Bullet(float posX, float posY);

	void shoot(sf::Vector2f pos, float angle);
	void killed();
	void update(double dt);

	void draw(sf::RenderWindow& win);
};