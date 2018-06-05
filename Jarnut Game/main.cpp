#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Animation.h"
#include "Collider.h"
#include "Platform.h"
#include <thread>
#include <vector>

bool inair(Player player, Platform platform)
{
	if (player.GetPosition().y <= 440.0f)
		return false;

	return true;
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(640, 480), "You know de wae", sf::Style::Close | sf::Style::Titlebar);

	sf::Texture playerTexture;
	sf::Texture backTexture;
	sf::Texture wallTexture;

	playerTexture.loadFromFile("droid_from_android.png");
	backTexture.loadFromFile("background.png");
	wallTexture.loadFromFile("wall.png");
	sf::Sprite background(backTexture);

	std::vector<Platform> platforms;

	Player player(&playerTexture, sf::Vector2u(3, 9), 0.3f, 90.0f, 20.0f);

	platforms.push_back(Platform(&wallTexture, sf::Vector2f(650.0f, 30.0f), sf::Vector2f(320.0f, 470.0f)));
	platforms.push_back(Platform(&wallTexture, sf::Vector2f(200.0f, 30.0f), sf::Vector2f(160.0f, 240.0f)));
	platforms.push_back(Platform(&wallTexture, sf::Vector2f(30.0f, 480.0f), sf::Vector2f(630.0f, 240.0f)));
	platforms.push_back(Platform(&wallTexture, sf::Vector2f(30.0f, 480.0f), sf::Vector2f(10.0f, 240.0f)));

	sf::Vector2u textureSize = playerTexture.getSize();

	Animation animation(&playerTexture, sf::Vector2u(3, 9), 0.3f);

	textureSize.x /= 3;
	textureSize.y /= 9;

	float deltaTime = 0.0f;
	sf::Clock clock;

	
	while (window.isOpen())
	{
		deltaTime = clock.restart().asSeconds();
		sf::Event evet;
		while (window.pollEvent(evet))
		{
			if (evet.type == evet.Closed)
			{
				window.close();
			}
		}

		player.Update(deltaTime);
		sf::Vector2f direction;
		Collider x = player.GetCollider();
		for (Platform &platform : platforms)
		{
			platform.GetCollider().CheckCollision(x, direction, 1.0f);
		}

		window.clear();
		window.draw(background);
		player.Draw(window);
		for (Platform &platform : platforms)
		{
			platform.Draw(window);
		}
		
		window.display();
	}
	return 0;
}