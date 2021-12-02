#pragma once
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Shape.hpp"
#include "SFML/Graphics/Rect.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/CircleShape.hpp"
/*
class Entity {
	
	// Graphical object
	sf::CircleShape e;
	sf::Sprite spr;
	sf::Shape* spr = nullptr;

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

    static const int stride = 32;

	Entity(sf::Shape* _spr, int _cx, int _cy)
	{
		this->spr = _spr;
		cx = _cx;
		cy = _cy;
		syncSprite();
	}

	void syncSprite();
	void update(double dt);
	void draw(sf::RenderWindow& win);
	
};*/