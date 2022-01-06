#pragma once

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "Entity.hpp"

class Character;

class State {
public:
	Character* e = nullptr;

	virtual void onEnter() = 0;
	virtual void onUpdate(double dt) = 0;
};


class IdleState : public State {
public:
	IdleState(Character*_e) {
		e = _e;
	};

	virtual void onEnter();
	virtual void onUpdate(double dt);
};

class walkState : public State {
public:
	walkState(Character*_e) {
		e = _e;
	};

	virtual void onEnter();
	virtual void onUpdate(double dt);
};

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
	bool sprint = false;

	// Resulting coordinates
	float px = 0.0f;
	float py = 0.0f;

	//Frictions
	float frictX = 0.80f;
	float frictY = 0.80f;

	void syncSprite();

	void update(double dt);

	State*			current = nullptr;

	Character();

	void jump(float y);
	void move(float x, float y);
	void attack();
	void setCoordinate(float x, float y);
	bool hasCollision(float ncx, float ncy);
	void collided(Character* wall);
	void CreateWall(sf::Vector2i);
	void setState(State* state);

	void draw(sf::RenderWindow& win);
};