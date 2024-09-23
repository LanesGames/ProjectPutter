#include "Player.h"

Player::Player(sf::Vector2f handPos)
{
	handCenterPos = handPos;
}

Player::~Player()
{
}

std::vector<std::unique_ptr<Card>>& Player::getHand()
{
	return playerHand;
}

void Player::addToHand(std::unique_ptr<Card> card)
{
	playerHand.push_back(std::move(card));
}

void Player::printHand()
{
	for (int i = 0; i < playerHand.size(); i++)
	{
		std::cout << "Card Name: " << (playerHand[i])->GetCardName() << " Card Distance: " << (playerHand[i])->getDistance() << std::endl;
	}
}

sf::Vector2f Player::getCenterHandPos()
{
	return handCenterPos;
}


