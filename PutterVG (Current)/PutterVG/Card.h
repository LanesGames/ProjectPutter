#pragma once
#include <iostream>
#include "CardBody.h"

class Card
{
public:

	Card(std::string cardType, std::string cardName, int distance, sf::Vector2f Scale, std::shared_ptr<sf::Font> font);
	~Card();
	std::string GetType();
	std::string GetCardName();
	int getDistance();
	CardBody& getSprite();

private:

	enum cardTypes { club = 1, effect = 2, course = 3 };
	int type;
	std::string typeName;
	std::string cardName;
	int distance;
	
	bool facing_up;
	CardBody body;

};

