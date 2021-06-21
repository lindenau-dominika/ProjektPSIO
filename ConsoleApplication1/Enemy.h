#pragma once
#include <SFML/Graphics.hpp>
#include "animacja.h"
#include "Collider.h"
class Enemy
{
public:

	Enemy(sf::Texture* texture, sf::Vector2f position);
	~Enemy();
	void update1(float deltaTime);
	void Draw(sf::RenderWindow& window);
	void OnCollision(sf::Vector2f direction);
	void setPos(sf::Vector2f setPos);

	sf::Vector2f GetPosition()
	{
		return body.getPosition();
	}
	Collider GetCollider()
	{
		return Collider(body);
	}
private:
	sf::RectangleShape body;
	float speed;
	sf::Vector2f velocity;
};

