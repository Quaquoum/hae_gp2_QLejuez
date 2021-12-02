#pragma once

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "Entity.hpp"

class Character {
public:
	sf::RectangleShape spr;
	sf::FloatRect hitbox;

	std::vector<bool>	alive;

	// Base coordinates
	int cx = 0;
	int cy = 0;
	float rx = 0.0f;
	float ry = 0.0f;

	// Movements
	float dx = 0.0f;
	float dy = 0.0f;

	// Resulting coordinates
	float px = 0.0f;
	float py = 0.0f;

	void syncSprite();

	void update(double dt);


	Character();

	void jump();
	void move(float x, float y);
	void attack();
	void setCoordinate(float x, float y);
	bool hasCollision(float ncx, float ncy);
	void collided(Character other);

	void draw(sf::RenderWindow& win);
};