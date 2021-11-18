#include "Block.hpp"

Block::Block(float posX, float posY) {
	int length = 80;
	int height = 20;
	b = sf::RectangleShape(sf::Vector2f(length, height));
	b.setOutlineThickness(1);
	b.setFillColor(sf::Color::Blue);
	b.setOutlineColor(sf::Color::White);
	b.setOrigin(sf::Vector2f(length/2, height/2));
	b.setPosition(posX, posY);
}

void Block::create(float posX_, float posY_)
{
}

void Block::update(double dt) 
{

}

void Block::killed() 
{

}

void Block::draw(sf::RenderWindow& win) 
{
	if (this == nullptr)
		return;

		win.draw(b);
}