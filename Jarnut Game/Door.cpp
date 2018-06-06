#include "Door.h"


Door::Door(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position)
{
	body.setScale(size);
	body.setOrigin(size / 2.0f);
	body.setTexture(texture);
	body.setPosition(position);
}
void Door::open(sf::Texture* texture)
{
	body.setPosition(400.0f, 800.0f);
}
Door::~Door()
{
}
void Door::Draw(sf::RenderWindow & window)
{
	window.draw(body);
}

