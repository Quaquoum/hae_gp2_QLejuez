#include "Block.hpp"

Block::Block() {
	int length = 10;
	int height = 10;
	b = sf::RectangleShape(sf::Vector2f(length, height));
	b.setOutlineThickness(1);
	b.setFillColor(sf::Color::Blue);
	b.setOutlineColor(sf::Color::White);
	b.setOrigin(sf::Vector2f(length/2, height/2));
}

void Block::create(float posX_, float posY_)
{
	for (int i = 0; i < posX.size(); ++i) {
		if (!alive[i]) {
			posX[i] = posY_;
			posY[i] = posX_;
			alive[i] = true;
			return;
		}
	}
	posX.push_back(posX_);
	posX.push_back(posY_);
	alive.push_back(true);
	b.setPosition(posX_, posY_);
}

void Block::update(double dt) {
}

void Block::draw(sf::RenderWindow& win) {
	int idx = 0;
	const int sz = posX.size();
	while (idx < sz) {
		if (alive[idx]) {
			win.draw(b);
		}
		idx++;
	}
}