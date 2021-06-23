#include "Enemy.h"
#include "animacja.h"

Enemy::Enemy(sf::Texture* texture, sf::Vector2f position, float speed, sf::Vector2u imageCount, float switchTime) : animation(texture, imageCount, switchTime)
{
	this->speed = speed;
	
	row = 0;
	faceRight = true;
	body.setSize(sf::Vector2f(50.0f, 40.0f));
	body.setOrigin(25.0f, 20.0f);
	body.setPosition(position);
	body.setTexture(texture);
	
	exists = true;

	
}

Enemy::~Enemy()
{

}
void Enemy::update1(float deltaTime)
{
	bound = body.getGlobalBounds();
	
	//velocity.x = speed;

	if (body.getPosition().x >= 640.0f)
	{
		velocity.x = -speed;
		
	}
	if (body.getPosition().x <= 380.0f)
	{
		velocity.x = +speed;
	}
	animation.Update(row, deltaTime, faceRight);
	body.setTextureRect(animation.uvRect);
	body.move(velocity * deltaTime);

}
void Enemy::update2(float deltaTime)
{
	bound = body.getGlobalBounds();
	
	//velocity.x = speed;

	if (body.getPosition().x >= 640.0f)
	{
		velocity.x = -speed;
		
	}
	if (body.getPosition().x <= 210.0f)
	{
		velocity.x = +speed;
	}
	animation.Update(row, deltaTime, faceRight);
	body.setTextureRect(animation.uvRect);
	body.move(velocity * deltaTime);
}
void Enemy::update3(float deltaTime)
{
	bound = body.getGlobalBounds();
	
	//velocity.x = speed;

	if (body.getPosition().x >= 840.0f)
	{
		velocity.x = -speed;
		
	}
	if (body.getPosition().x <= 560.0f)
	{
		velocity.x = +speed;
	}
	animation.Update(row, deltaTime, faceRight);
	body.setTextureRect(animation.uvRect);
	body.move(velocity * deltaTime);
}
void Enemy::update4(float deltaTime)
{
	bound = body.getGlobalBounds();
	
	//velocity.x = speed;

	if (body.getPosition().x >= 640.0f)
	{
		velocity.x = -speed;
		
	}
	if (body.getPosition().x <= 360.0f)
	{
		velocity.x = +speed;
	}
	animation.Update(row, deltaTime, faceRight);
	body.setTextureRect(animation.uvRect);
	body.move(velocity * deltaTime);
}


void Enemy::Draw(sf::RenderWindow& window)
{
		window.draw(body);
}

void Enemy::OnCollision(sf::Vector2f direction)
{
	if (direction.x < 0.0f)
	{
		//collision on the left
		velocity.x = 0.0f;
	}
	else if (direction.x > 0.0f)
	{
		//collision on the right
		velocity.x = 0.0f;
	}
}
const sf::FloatRect Enemy::getBounds() const
{
	return this->bound;
}

bool Enemy::getExists()
{
	return this->exists;
	
}

void Enemy::kill()
{
	this->exists = false;
}