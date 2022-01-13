#pragma once

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "Particles.hpp"

class Block {
public:
	sf::RectangleShape b;

	bool alive = false;

	//float px;
	//float py;
	float speed;
	Particles* parts[10];
	int hp = 1;

	sf::Vector2u direction;

	Block(float posX, float posY);

	void spawn(float posX, float posY, int curHp);
	bool collided(sf::FloatRect bulletHitbox);
	void killed();
	void update(double dt, float playerPosX, float playerPosY);

	void draw(sf::RenderWindow& win);
};