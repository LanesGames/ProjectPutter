#include "CardBody.h"

CardBody::CardBody()
{
}

CardBody::CardBody(sf::Vector2f scale, std::shared_ptr<sf::Font> font, std::string fName, std::string bName, int cardDistance)
{
	sprite = sf::RectangleShape(scale);
	sprite.setFillColor(sf::Color::White);
	sprite.setPosition(sf::Vector2f(0.0f, 0.0f));
	float text_scale = 15.0f;
	float text_padding = 5.0f;

	//initialise front of card name
	frontName = std::make_shared<sf::Text>();
	frontName->setFont(*font);
	frontName->setCharacterSize(text_scale);
	frontName->setFillColor(sf::Color::Black);
	frontName->setString(fName);
	frontName->setPosition(sprite.getPosition().x + (sprite.getLocalBounds().width/2) - (frontName->getLocalBounds().width / 2), sprite.getPosition().y + text_padding);

	//initialise back of card name
	backName = std::make_shared<sf::Text>();
	backName->setFont(*font);
	backName->setCharacterSize(text_scale);
	backName->setFillColor(sf::Color::Black);
	backName->setString(bName);
	backName->setPosition(sprite.getPosition().x + (sprite.getLocalBounds().width / 2) - (backName->getLocalBounds().width / 2),
		sprite.getPosition().y + (sprite.getLocalBounds().height / 2) - (backName->getLocalBounds().height / 2));

	//initialise distance text
	distance = std::make_shared<sf::Text>();
	distance->setFont(*font);
	distance->setCharacterSize(text_scale);
	distance->setFillColor(sf::Color::Black);
	distance->setString(std::to_string(cardDistance));
	distance->setPosition(sprite.getPosition().x + (sprite.getLocalBounds().width / 2) - (distance->getLocalBounds().width / 2), 
		sprite.getPosition().y + sprite.getLocalBounds().height - (distance->getLocalBounds().height + text_padding));


	localPosFN = frontName->getPosition() - sprite.getPosition();
	localPosBN = backName->getPosition() - sprite.getPosition();
	localPosD = distance->getPosition() - sprite.getPosition();
}

CardBody::~CardBody()
{
}

void CardBody::updatePos(sf::Vector2f position)
{
	//updates the main card position and adjusts all th others locally
	sprite.setPosition(position);
	frontName->setPosition(position + localPosFN);
	backName->setPosition(position + localPosBN);
	distance->setPosition(position + localPosD);
}

void CardBody::makeFaceUp(bool facingUp)
{
	//Keeping only the visible text components on the card
	visibletext.clear();
	if (facingUp)
	{
		visibletext.push_back(frontName);
		visibletext.push_back(distance);
	}
	else
	{
		visibletext.push_back(backName);
	}
}

sf::RectangleShape& CardBody::getBody()
{
	//return a reference to the card body sprite
	return sprite;
}

std::vector<std::shared_ptr<sf::Text>>& CardBody::getText()
{
	//returns a reference to all current visiblke 
	return visibletext;
}

