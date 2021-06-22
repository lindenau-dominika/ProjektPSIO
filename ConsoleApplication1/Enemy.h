#pragma once
#include <SFML/Graphics.hpp>
#include "animacja.h"
#include "Collider.h"
#include "player.h"
class Enemy
{
public:

	Enemy(sf::Texture* texture, sf::Vector2f position, float speed);
	~Enemy();
	void update1(float deltaTime);
	void Draw(sf::RenderWindow& window);
	void OnCollision(sf::Vector2f direction);
	const sf::FloatRect getBounds() const;

	bool getExists();
	void kill();

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
	sf::FloatRect bound;
	bool exists;
};

