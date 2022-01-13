#include "Block.hpp"

Block::Block(float posX, float posY) {

	int length = 45;
	int height = 45;
	b = sf::RectangleShape(sf::Vector2f(length, height));
	b.setOutlineThickness(3);
	b.setFillColor(sf::Color::Black);
	b.setOutlineColor(sf::Color::Red);
	b.setOrigin(sf::Vector2f(length/2, height/2));
	b.setPosition(posX, posY);
	speed = (rand() % 200 + 1) / 100;

	for (int i = 0; i < 10; i++)
	{
		Particles* p = new Particles(b.getPosition(), sf::Color::Red);
		parts[i] = p;
	}
}

void Block::spawn(float posX_, float posY_, int curHp)
{
	if (!alive)
	{
		b.setPosition(posX_, posY_);
		speed = (rand() % 200 + 1) / 100;
		if (speed >= 1)
		{
			b.setOutlineColor(sf::Color::Yellow);
			hp = 1;
		}
		else
		{
			b.setOutlineColor(sf::Color::Red);
			hp = curHp;
		}
			
		
		alive = true;
	}
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
	hp--;
	if (hp == 0)
	{
		alive = false;
		for (int i = 0; i < 10; i++)
		{
			float moveX = (rand() % 200 + 0);
			float moveY = (rand() % 200 + 0);
			parts[i]->blockdeath(b.getPosition(), moveX / 100, moveY / 100);
		}
	}
}

void Block::update(double dt, float playerPosX, float playerPosY)
{
	if (alive)
	{
		if (playerPosX > b.getPosition().x)
		{
			b.move(1.5 + speed, 0);
		}
		if (playerPosX < b.getPosition().x)
		{
			b.move(-1.5 - speed, 0);
		}
		if (playerPosY > b.getPosition().y)
		{
			b.move(0, 1.5 + speed);
		}
		if (playerPosY < b.getPosition().y)
		{
			b.move(0, -1.5 - speed);
		}
	}
		for (int i = 0; i < 10; i++)
		{
		parts[i]->update(dt);
	}
}

void Block::draw(sf::RenderWindow& win) 
{
	if (this == nullptr)
		return;

	if (alive)
	{
		win.draw(b);
	}
	else
	{
		for (int i = 0; i < 10; i++)
		{
			parts[i]->draw(win);
		}
	}
}