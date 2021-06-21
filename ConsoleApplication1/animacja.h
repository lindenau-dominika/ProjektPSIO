#pragma once
#include <SFML\Graphics.hpp>

class Animation
{
public:
	//konstruktory i destruktory
	Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime);
	~Animation();
	//metoda do aktualizowania animacji
	void Update(int row, float deltaTime, bool faceRight);
public:
	sf::IntRect uvRect;
	void setSmooth(bool smooth);
	//funkcje
	
	private:
		sf::Vector2u imageCount;
		sf::Vector2u currentImage;
		

		float totalTime;
		float switchTime;

};

