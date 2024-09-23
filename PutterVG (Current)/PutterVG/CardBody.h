#pragma once
#include <SFML/Graphics.hpp>

class CardBody
{
public:

	CardBody();
	CardBody(sf::Vector2f scale, std::shared_ptr<sf::Font>, std::string fName, std::string bName, int distance);
	~CardBody();
	void updatePos(sf::Vector2f position);
	void makeFaceUp(bool facingUp);
	sf::RectangleShape& getBody();
	std::vector<std::shared_ptr<sf::Text>>& getText();

private:


	bool face_up;
	sf::RectangleShape sprite;
	std::vector<std::shared_ptr<sf::Text>> visibletext;

	std::shared_ptr<sf::Text> frontName;
	sf::Vector2f localPosFN;

	std::shared_ptr<sf::Text> backName;
	sf::Vector2f localPosBN;

	std::shared_ptr<sf::Text> distance;
	sf::Vector2f localPosD;



};

