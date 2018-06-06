#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "Collider.h"
class Door
{
public:
	Door(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position);
	~Door();
	void open(sf::Texture* texture);
	void Draw(sf::RenderWindow & window);
	Collider GetCollider()
	{
		return Collider(body);
	}
private:
	sf::RectangleShape body;
	bool locked=true;
	std::string color;
};

