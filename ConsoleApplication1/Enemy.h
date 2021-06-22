#pragma once
#include <SFML/Graphics.hpp>
#include "animacja.h"
#include "Collider.h"
#include "player.h"
class Enemy
{
public:

	Enemy(sf::Texture* texture, sf::Vector2f position, float speed, sf::Vector2u imageCount, float switchTime);
	~Enemy();
	void update1(float deltaTime);
	void update2(float deltaTime);
	void update3(float deltaTime);
	void update4(float deltaTime);
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
	unsigned int row;
	bool faceRight;
	sf::Vector2f velocity;
	Animation animation;
	sf::FloatRect bound;
	bool exists;
};

