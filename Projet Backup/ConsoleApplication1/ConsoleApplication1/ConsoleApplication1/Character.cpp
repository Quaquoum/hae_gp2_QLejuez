#include "Character.hpp"





void Character::draw(sf::RenderWindow & win)
{
	if (visible)
	{
		win.draw(this->spr);
	}
}
