#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <memory>
#include <random>
#include "Card.h"
#include "Player.h"

class Game
{
	public:

		enum gameState{ setup = 1, gameplay = 2};

		Game(sf::RenderWindow& window);
		~Game();
		bool init();
		void update(float dt);
		void render();
		void mouseClicked(sf::Event event);
		void keyPressed(sf::Event event);
		void keyReleased(sf::Event event);

	private:

		void IncrementPlayer();
		void CreateCards();
		void ShuffleDeck(std::vector<std::unique_ptr<Card>> &deck);
		void DisplayAllCards(std::vector<std::unique_ptr<Card>>& deck);
		void givePlayerCard(std::unique_ptr<Player>& player);
		void startGame();

		//Gameplay Values
		int players = 4;
		std::vector<sf::Vector2f> playerStationPos;
		int winsNeeded = 3;
		int handMax = 5;
		int currentPlayer = 1;
		std::vector<std::unique_ptr<Card>> CourseDeck;
		std::vector<std::unique_ptr<Card>> PlayDeck;

		//Gameplay UI
		std::shared_ptr<sf::Font> gameUIFont;
		sf::Text currentPlayerText;

		//Player variables
		std::vector<std::unique_ptr<Player>> gamePlayers;

		//window setup
		sf::View camera;
		sf::RenderWindow& window;
		int state = setup;

		//Card Piles
		sf::Vector2f cardDimensions;
		std::vector<sf::Vector2f> PlayDeckPos;
		std::vector<sf::Vector2f> CourseDeckPos;
		float cardScale;
		float cardPadding;
		float tablePadding;

		//Background Additions
		sf::Texture backgroundTexture;
		sf::Sprite background;
		float zoomBG;

		




};

