#include "player.h"
#include "animacja.h"
#include "Enemy.h"

Player::Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, float jumpHeight) :
	animation(texture, imageCount, switchTime)
{ 
	this->speed = speed;
	this->jumpHeight = jumpHeight;
	
	row = 0;
	faceRight = true;
	
	body.setSize(sf::Vector2f(80.0f, 112.0f));
	body.setPosition(128.0f, 450.0f);
    body.setOrigin(40.0f, 56.0f);
    body.setTexture(texture);
	health = 3.0f;
	
}

Player::~Player()
{

}
//pobieram znaki z klawiatury ktore beda odpowiadaly poruszaniu sie playera, warunkujê jaka predkosc ma osiagnac player w danych kierunkach
void Player::update(float deltaTime)
{
	bound = body.getGlobalBounds();
	/*velocity.x = 0.0f;*/

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		velocity.x =- speed; 
	
	row = 5;
	}
	if (velocity.x > 0)
	{
		velocity.x -= 0.1f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{velocity.x =+ speed; 
	row = 0;
	}
	if (velocity.x < 0)
	{
		velocity.x += 0.1f;

	}

	// warunkuje kiedy player moze skakac, czyli jezeli nacisnieta jest spacja, oraz do poki canJump bedzie prawda
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && canJump)
	{
		canJump = false;
		velocity.y = -sqrtf(2.0f * 981.0f * jumpHeight);
		
	}
	velocity.y += 981.0f * deltaTime;


	if (abs(velocity.x) <0.1f )
	{
		row = 3;
	}
	if (abs(velocity.y) > 10.0f)
	{
		row = 1;
	}
	if (body.getPosition().x  <= -1000.0f)
	{
		body.setPosition(128.0f, 450.0f);
	}
	
	animation.Update(row, deltaTime, faceRight);
	body.setTextureRect(animation.uvRect);
	body.move(velocity * deltaTime);
}
const sf::FloatRect Player::getBounds() const
{
	return this->bound;
}

void Player::updateB(float deltaTime)
{
	velocity.x = 0.0f;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		velocity.x -= speed;
		row = 5;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		velocity.x = speed;
		row = 0;
	}


	//animation.Update(row, deltaTime, faceRight);
	body.setTextureRect(animation.uvRect);
	body.move(velocity * deltaTime);
	body.setSize(sf::Vector2f(2048.0f, 2048.0f));
	body.setOrigin(1024.0f, 1500.0f);
}
void Player::updateB2(float deltaTime)
{
	velocity.x = 0.0f;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		velocity.x -= speed;
		row = 5;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		velocity.x = speed;
		row = 0;
	}

	//animation.Update(row, deltaTime, faceRight);
	body.setTextureRect(animation.uvRect);
	body.move(velocity * deltaTime);
	body.setSize(sf::Vector2f(1024.0f, 1024.0f));
	body.setOrigin(512.0f, 512.0f);

	if (body.getPosition().x >= 1900.0f)
	{
		body.setPosition(128.0f, 450.0f);
	}
}

void Player::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}
void Player::OnCollision(sf::Vector2f direction)
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
	if (direction.y < 0.0f)
	{
		//collision on the bottom
		velocity.y = 0.0f;
		canJump = true;
	}
	else if (direction.y > 0.0f)
	{
		//collision on the top
		velocity.y = 0.0f;
	}
}
//***********************************************************//
