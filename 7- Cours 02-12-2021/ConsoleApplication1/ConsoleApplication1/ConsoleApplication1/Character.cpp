#include "Character.hpp"


Character::Character()
{
	spr.setSize(sf::Vector2f(sf::Vector2f(32, 32)));
	spr.setFillColor(sf::Color::Green);
	spr.setOutlineThickness(3);
	spr.setOutlineColor(sf::Color::Red);
	//spr.setOrigin(spr.getSize().x * 0.5f, spr.getSize().y * 0.5);

	cx = 10;
	cy = 10;
	rx = 0;
	ry = 0;
}

void Character::syncSprite()
{
}

void Character::update(double dt)
{
	//Movement
	ry += dy;
	rx += dx;
	dx *= 0.80;
	dy *= 0.80;

	while (rx > 1) { 
		rx--;	
		cx++; 
	}
	while (rx < 0) { 
		rx++;	
		cx--;
	}
	while (ry > 1) {
		ry--;	
		cy++; 
	}
	while (ry < 0) {
		ry++;	
		cy--; 
	}

	px = ((cx + rx) * 32);
	py = ((cy + ry) * 32);

	//Collisions
	/*
	if (hasCollision(cx + 1, cy) && rx >= 0.7) {
		rx = 0.7;
		dx = 0;
	}
	if (hasCollision(cx - 1, cy) && rx <= 0.3) {
		rx = 0.3;
		dx = 0;
	}
	if (hasCollision(cx, cy - 1) && ry <= 0.3) {
		dy = 0;
		ry = 0.3;
	}
	if (hasCollision(cx, cy + 1) && ry >= 0.5) {
		dy = 0;
		ry = 0.5;
	}
	*/

	spr.setPosition(px, py);
}

void Character::move(float x, float y)
{
	if (x != 0)
	dx = x;
	if (y != 0)
	dy = y;
}

void Character::setCoordinate(float x, float y)
{
	px = x;
	py = y;
	cx = (px / 32);
	cy = (py / 32);
	rx = (px - cx * 32) / 32;
	ry = (py - cy * 32) / 32;
}

bool Character::hasCollision(float ncx, float ncy)
{
	//check chaque entity

	return false;
}

void Character::collided(Character other)
{
	sf::Vector2f tOrigin = this->spr.getOrigin();
	sf::Vector2f eOrigin = other.spr.getOrigin();


}

void Character::CreateWall(sf::Vector2i)
{
	
}

void Character::draw(sf::RenderWindow & win)
{
	win.draw(this->spr);
}
