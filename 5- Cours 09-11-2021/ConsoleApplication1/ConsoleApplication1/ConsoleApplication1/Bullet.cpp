#include "Bullet.hpp"

Bullet::Bullet(float posX, float posY) {
	int t = 10;
	b = sf::CircleShape(t);
	b.setFillColor(sf::Color::Magenta);
	b.setPosition(posX, posY);

	//b.setOutlineThickness(2);
	//b.setOutlineColor(sf::Color::Red);
	//b.setOrigin(sf::Vector2f(t, t));

	for (int i = 0; i < 5; i++)
	{
		Particles* p = new Particles(b.getPosition(), sf::Color::Magenta);
		parts[i] = p;
	}

}

void Bullet::shoot(sf::Vector2f pos, float angle)
{
	b.setPosition(pos.x, pos.y);
	b.setRotation(angle);
	bulletHitbox = b.getGlobalBounds();
	alive = true;
}

void Bullet::killed()
{
	for (int i = 0; i < 5; i++)
	{
		float moveX = (rand() % 200 + 0);
		float moveY = (rand() % 200 + 0);
		parts[i]->blockdeath(b.getPosition(), moveX / 100, moveY / 100);
	}
	alive = false;
}

void Bullet::update(double dt)
{
	if (alive)
	{
		bulletHitbox = b.getGlobalBounds();
		//Move Bullet
		float projRad = 3.14 / 180 * b.getRotation();
		float x = 8.0f * cos(projRad);
		float y = 8.0f * sin(projRad);

		b.move(x, y);
	}
	for (int i = 0; i < 5; i++)
	{
		parts[i]->update(dt);
	}

}



void Bullet::draw(sf::RenderWindow& win)
{
	if (this == nullptr)
		return;

	if (alive)
	{
		win.draw(b);
	}
	for (int i = 0; i < 5; i++)
	{
		parts[i]->draw(win);
	}
}