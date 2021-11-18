#include "Block.hpp"

Block::Block(float posX, float posY) {
	int length = 80;
	int height = 20;
	b = sf::RectangleShape(sf::Vector2f(length, height));
	b.setOutlineThickness(2);
	b.setFillColor(sf::Color(209,0,0,255));
	b.setOutlineColor(sf::Color::Black);
	b.setOrigin(sf::Vector2f(length/2, height/2));
	b.setPosition(posX, posY);
}

void Block::create(float posX_, float posY_)
{
}

bool Block::collided(sf::FloatRect bulletHitbox)
{
	if (this == nullptr)
		return false;

	sf::FloatRect bHitbox = b.getGlobalBounds();
	if (bHitbox.intersects(bulletHitbox))
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Block::killed() 
{
	alive = false;
}

void Block::createParticles()
{

}

void Block::draw(sf::RenderWindow& win) 
{
	if (this == nullptr)
		return;

	if (alive = true)
	{
		win.draw(b);
	}
}