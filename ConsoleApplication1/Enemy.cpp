#include "Enemy.h"
#include "animacja.h"

Enemy::Enemy(sf::Texture* texture, sf::Vector2f position, float speed) 
{
	this->speed = speed;

	body.setSize(sf::Vector2f(40.0f, 60.0f));
	body.setOrigin(20.0f, 30.0f);
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
	velocity.x = speed;
	

	if (body.getPosition().x == 300.0f)
	{
		velocity.x = -speed;
	}
	if (body.getPosition().x == 50.0f)
	{
		velocity.x = speed;
	}
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