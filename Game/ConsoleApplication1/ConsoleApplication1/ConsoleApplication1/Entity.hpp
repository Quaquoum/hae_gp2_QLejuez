#pragma once
#include "SFML/Graphics/Shape.hpp"
#include "SFML/Graphics/Rect.hpp"

class Entity {
public:
	sf::Shape* spr;
	sf::FloatRect hitBox;

	Entity(sf::Shape* _spr)
	{
		
	}
};

class Brick {
public:

};

class EntityManager {
public:
	std::vector<Entity*> repository;
};