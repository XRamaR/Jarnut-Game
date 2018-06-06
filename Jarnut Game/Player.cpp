#include "Player.h"



Player::Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, float jumpHeight) :
	animation(texture, imageCount, switchTime)
{
	this->speed = speed;
	this->jumpHeight = jumpHeight;
	row = 3;
	faceRigth = true;

	body.setSize(sf::Vector2f(40.0f, 60.0f));
	body.setPosition(20.0f, 400.0f);
	body.setTexture(texture);
}


Player::~Player()
{

}

void Player::Update(float deltaTime)
{
	velocity.x *= 0.3f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
	{
		velocity.x -= speed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		velocity.x += speed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)&&canJump)
	{
		canJump = false;
		velocity.y = -sqrtf(2.0f*981.0f*jumpHeight);
	}
	velocity.y += 981.0f*deltaTime;
	
	if (velocity.x == 0.0f)
		row = 0;
	else
	{
		row = 1;
		if (velocity.x > 0)
			faceRigth = true;
		else
			faceRigth = false;
	}

	animation.Update(row, deltaTime, faceRigth,inAir);
	body.setTextureRect(animation.uvRect);
	body.move(velocity*deltaTime);
}

void Player::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}

void Player::onColiision(sf::Vector2f direction)
{
	if (direction.x < 0.0f)
	{
		velocity.x = 0.0f;
	}
	else if (direction.x > 0.0f)
	{
		velocity.x = 0.0f;
	}
	if (direction.y < 0.0f)
	{
		velocity.y = 0.0f;
		canJump = true;
		
	}
	else if (direction.y > 0.0f)
	{
		velocity.y = 0.0f;
	}
}

void Player::foundKey(bool red, bool green, bool blue)
{
	if (red)
		redKey = true;
	if (green)
		greenKey = true;
	if (blue)
		blueKey = true;
}
