#pragma once

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/RectangleShape.hpp"

class Block {
public:
	sf::RectangleShape b;

	bool alive = true;

	//float px;
	//float py;

	sf::Vector2u direction;

	Block(float posX, float posY);

	void spawn(float posX, float posY);
	bool collided(sf::FloatRect bulletHitbox);
	void killed();
	void update(double dt, float playerPosX, float playerPosY);
	void createParticles();

	void draw(sf::RenderWindow& win);
};