#pragma once
#include <iostream>
#include <memory>
#include <cmath>
#include "Card.h"
#include <vector>

class Player
{
public:

	Player(sf::Vector2f handPos);
	~Player();
	std::vector<std::unique_ptr<Card>>& getHand();
	void addToHand(std::unique_ptr<Card> card);
	void printHand();
	sf::Vector2f getCenterHandPos();

private:

	std::vector<std::unique_ptr<Card>> playerHand;
	sf::Vector2f handCenterPos;

};

