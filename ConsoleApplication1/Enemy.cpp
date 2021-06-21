#include "Enemy.h"
#include "animacja.h"

Enemy::Enemy(sf::Texture* texture, sf::Vector2f position) 
{
	this->speed = speed;

	body.setSize(sf::Vector2f(40.0f, 60.0f));
	body.setOrigin(20.0f, 30.0f);
	body.setPosition(position);
	//Enemy enemy(&monsterTexture, 100.0f, sf::Vector2f(700.0f, 200.0f));

}

Enemy::~Enemy()
{

}
void Enemy::update1(float deltaTime)
{
	velocity.x = .0f;
	body.move(velocity * deltaTime);

	if (body.getPosition().x + 20.0f == 200.0f)
	{
		velocity.y = +100.0f;
	}
	if (body.getPosition().x + 20.0f == 100.0f)
	{
		velocity.y = -100.0f;
	}
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

void Enemy::setPos(sf::Vector2f setPos)
{
	body.setPosition(1000.0f, 10000.0f);
}
