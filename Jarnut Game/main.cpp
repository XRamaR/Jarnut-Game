#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Animation.h"
#include "Collider.h"
#include "Door.h"
#include "Platform.h"
#include <thread>
#include <vector>
#include <string>



int main()
{
	sf::RenderWindow window(sf::VideoMode(640, 480), "You know de wae", sf::Style::Close | sf::Style::Titlebar);

	sf::Texture playerTexture;
	sf::Texture backTexture;
	sf::Texture wallTexture;
	sf::Texture keyTexture;

	playerTexture.loadFromFile("droid_from_android.png");
	backTexture.loadFromFile("background.png");
	wallTexture.loadFromFile("wall.png");
	keyTexture.loadFromFile("Key.png");
	sf::Sprite background(backTexture);

	std::vector<Platform> platforms;
	std::vector<Platform> walls;

	Player player(&playerTexture, sf::Vector2u(3, 9), 0.3f, 130.0f, 160.0f);

	platforms.push_back(Platform(&wallTexture, sf::Vector2f(650.0f, 30.0f), sf::Vector2f(320.0f, 470.0f))); //floor

	platforms.push_back(Platform(NULL, sf::Vector2f(260.0f, 30.0f), sf::Vector2f(120.0f, 340.0f)));
	platforms.push_back(Platform(/*&wallTexture*/NULL, sf::Vector2f(260.0f, 30.0f), sf::Vector2f(500.0f, 340.0f)));
	platforms.push_back(Platform(NULL, sf::Vector2f(240.0f, 30.0f), sf::Vector2f(120.0f, 210.0f)));
	platforms.push_back(Platform(NULL, sf::Vector2f(240.0f, 30.0f), sf::Vector2f(500.0f, 210.0f)));
	platforms.push_back(Platform(NULL, sf::Vector2f(240.0f, 30.0f), sf::Vector2f(320.0f, 100.0f)));


	walls.push_back(Platform(&wallTexture, sf::Vector2f(30.0f, 480.0f), sf::Vector2f(630.0f, 240.0f)));
	walls.push_back(Platform(&wallTexture, sf::Vector2f(30.0f, 480.0f), sf::Vector2f(10.0f, 240.0f)));
	

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
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::C))
			window.close();
		for (Platform &platform : platforms)
		{
			if (platform.GetCollider().CheckCollision(x, direction, 1.0f))
				player.onColiision(direction);
		}
		window.clear();
		window.draw(background);
		player.Draw(window);
		for (Platform &platform : platforms)
		{
			platform.Move(sf::Vector2f(0.0f, 0.03f));
		}
		for (Platform &platform : platforms)
		{
			platform.Draw(window);
		}
		for (Platform &platform : walls)
		{
			platform.Draw(window);
		}
		if (player.OutOfScreen())
		{
			window.close();
		}
		window.display();
	}
	return 0;
}