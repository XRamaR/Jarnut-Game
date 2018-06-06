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
	sf::Texture platformTexture;
	sf::Texture endingScreenTexture;

	playerTexture.loadFromFile("droid_from_android.png");
	backTexture.loadFromFile("background.png");
	wallTexture.loadFromFile("wall.png");
	platformTexture.loadFromFile("plank.png");
	endingScreenTexture.loadFromFile("Endingscreen.png");

	sf::Sprite endingScreen(endingScreenTexture);
	sf::Sprite background(backTexture);

	std::vector<Platform> platforms;
	std::vector<Platform> walls;

	Player player(&playerTexture, sf::Vector2u(3, 9), 0.3f, 130.0f, 160.0f);

	platforms.push_back(Platform(&platformTexture, sf::Vector2f(650.0f, 30.0f), sf::Vector2f(320.0f, 470.0f))); //floor
	platforms.push_back(Platform(&platformTexture, sf::Vector2f(260.0f, 30.0f), sf::Vector2f(320.0f, 340.0f)));

	for (int i = 0; i < 10; i++)
	{
		platforms.push_back(Platform(&platformTexture, sf::Vector2f(240.0f - 25.0f*i, 30.0f), sf::Vector2f(330.0f, 100.0f - 220.0f*i)));
		platforms.push_back(Platform(&platformTexture, sf::Vector2f(240.0f - 25.0f*i, 30.0f), sf::Vector2f(120.0f, 190.0f - 220.0f*i)));
		platforms.push_back(Platform(&platformTexture, sf::Vector2f(240.0f - 25.0f*i, 30.0f), sf::Vector2f(500.0f, 190.0f - 220.0f*i)));
	}
	for (int i = 0; i < 10; i++)
	{
		platforms.push_back(Platform(&platformTexture, sf::Vector2f(240.0f - 25.0f*(10-i), 30.0f), sf::Vector2f(330.0f, -2100.0f - 220.0f*i)));
		platforms.push_back(Platform(&platformTexture, sf::Vector2f(240.0f - 25.0f*(10 - i), 30.0f), sf::Vector2f(120.0f, -2010.0f - 220.0f*i)));
		platforms.push_back(Platform(&platformTexture, sf::Vector2f(240.0f - 25.0f*(10 - i), 30.0f), sf::Vector2f(500.0f, -2010.0f - 220.0f*i)));
	}


	walls.push_back(Platform(&wallTexture, sf::Vector2f(30.0f, 480.0f), sf::Vector2f(630.0f, 240.0f)));
	walls.push_back(Platform(&wallTexture, sf::Vector2f(30.0f, 480.0f), sf::Vector2f(10.0f, 240.0f)));


	sf::Vector2u textureSize = playerTexture.getSize();

	Animation animation(&playerTexture, sf::Vector2u(3, 9), 0.2f);

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
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
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
			sf::Time time = clock.getElapsedTime();
			float timeAs = time.asMilliseconds;
			platform.Move(sf::Vector2f(0.0f, 0.05f+timeAs));
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
			window.clear();
			window.draw(endingScreen);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				window.close();
		}
		window.display();
	}
	return 0;
}