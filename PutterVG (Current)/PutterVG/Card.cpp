#include "Card.h"

Card::Card(std::string cardType, std::string theCardName, int cardDistance, sf::Vector2f scale, std::shared_ptr<sf::Font> font)
{
	cardName = theCardName;
	typeName = cardType;
	distance = cardDistance;
	body = CardBody(scale, font, theCardName, cardType, cardDistance);

	facing_up = false;
	body.makeFaceUp(facing_up);

	//std::cout << cardType << std::endl;
	if (cardType == "club")
	{
		type = club;
		//std::cout << "Created club card" << std::endl;
	}
	else if(cardType == "course")
	{
		type = course;
		//std::cout << "Created course card" << std::endl;
	}
	else if (cardType == "effect")
	{
		type = effect;
		//std::cout << "Created effect card" << std::endl;
	}
	else
	{
		type = 0;
		//std::cout << "ERROR, invalid card type being created" << std::endl;
	}
}

Card::~Card()
{
}

std::string Card::GetType()
{
	return typeName;
}

std::string Card::GetCardName()
{
	return cardName;
}


int Card::getDistance()
{
	return distance;
}

CardBody& Card::getSprite()
{
	// TODO: insert return statement here
	return body;
}
