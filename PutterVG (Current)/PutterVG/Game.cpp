#include "Game.h"

Game::Game(sf::RenderWindow& game_window) : window(game_window)
{
	srand(time(NULL));
}

Game::~Game()
{
}

bool Game::init()
{
	//initialise the game view
	camera.reset(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y));
	window.setView(camera);

	//initialise fonts
	gameUIFont = std::make_shared<sf::Font>();
	if (!gameUIFont->loadFromFile("../Font/arial.ttf"))
	{
		return -1;
	}

	//initialise background
	zoomBG = 3.0f;
	if (!backgroundTexture.loadFromFile("../Img/tableBG.png"))
	{
		return -1;
	}
	background.setTexture(backgroundTexture);
	background.setScale(zoomBG, zoomBG);
	background.setPosition(window.getSize().x / 2 - ((background.getLocalBounds().width / 2) * zoomBG), window.getSize().y / 2 - ((background.getLocalBounds().height / 2) * zoomBG));

	//initialise UI
	currentPlayerText.setString("Current Player Turn Invalid");
	currentPlayerText.setFont(*gameUIFont);
	currentPlayerText.setCharacterSize(25);
	currentPlayerText.setPosition(window.getSize().x/2 - currentPlayerText.getLocalBounds().width/2, window.getSize().y - currentPlayerText.getLocalBounds().height - 10); //minus 10 is the padding
	currentPlayerText.setFillColor(sf::Color::White);

	//initialise cardPiles
	cardScale = 20.0f;
	cardPadding = 20.0f;
	tablePadding = 80.0f;
	cardDimensions = sf::Vector2f(2.5f, 3.5f);

	//Positions of the play deck in the following order: Facedown - Faceup
	PlayDeckPos = std::vector<sf::Vector2f>{ sf::Vector2f(window.getSize().x / 2 + cardPadding / 2, window.getSize().y / 2 - (cardDimensions.y * cardScale) - cardPadding / 2),
		sf::Vector2f(window.getSize().x / 2 - ((cardDimensions.x * cardScale) + cardPadding / 2), window.getSize().y / 2 - (cardDimensions.y * cardScale) - cardPadding / 2)};

	//Positions of the course deck in the following order: Facedown - Faceup
	CourseDeckPos = std::vector<sf::Vector2f>{ sf::Vector2f(window.getSize().x / 2 + cardPadding / 2, window.getSize().y / 2 + cardPadding / 2),
		sf::Vector2f(window.getSize().x / 2 - ((cardDimensions.x * cardScale) + cardPadding/2), window.getSize().y / 2 + cardPadding / 2) };


	//initialise player station Positions
	playerStationPos = std::vector<sf::Vector2f>{ sf::Vector2f(window.getSize().x / 2, window.getSize().y - ((cardDimensions.y * cardScale) + tablePadding)),
		sf::Vector2f(tablePadding, window.getSize().y/2),
		sf::Vector2f(window.getSize().x / 2, tablePadding), 
		sf::Vector2f(window.getSize().x - ((cardDimensions.x * cardScale) + tablePadding), window.getSize().y / 2)};


	//initialise game state
	state = setup;

	return true;
}

void Game::update(float dt)
{
	switch (state)
	{
	case setup:



		break;

	case gameplay:



		break;
	}
}

void Game::render()
{
	switch (state)
	{
	case setup:

		

		break;

	case gameplay:

		//Render Basic Elements
		window.draw(background);
		window.draw(currentPlayerText);

		//Make top card of Course Deck visible
		window.draw(PlayDeck[PlayDeck.size() - 1]->getSprite().getBody());
		for (int i = 0; i < PlayDeck[PlayDeck.size() - 1]->getSprite().getText().size(); i++)
		{
			window.draw(*PlayDeck[PlayDeck.size() - 1]->getSprite().getText()[i]);
		}

		//Make top card of Course Deck visible
		window.draw(CourseDeck[CourseDeck.size() - 1]->getSprite().getBody());
		for (int i = 0; i < CourseDeck[CourseDeck.size() - 1]->getSprite().getText().size(); i++)
		{
			window.draw(*CourseDeck[CourseDeck.size() - 1]->getSprite().getText()[i]);
		}


		//Render players decks
		for (int i = 0; i < gamePlayers.size(); i++)
		{
			//Calculate new positions
			sf::Vector2f handCenter = gamePlayers[i]->getCenterHandPos(); // center position of the visual hand
			int cardTotal = gamePlayers[i]->getHand().size(); // how many cards the player currently has
			float startingPos = 0; //This values will gaurantee to change but is initialised at 0

			//calculates the position of the first card in the hand
			if (i % 2 == 0)
			{
				float lengthOfHand = (cardTotal * (cardDimensions.x * cardScale)) + (cardPadding * (cardTotal - 1));
				startingPos = handCenter.x - (lengthOfHand / 2);
			}
			else
			{
				float lengthOfHand = (cardTotal * (cardDimensions.y * cardScale)) + (cardPadding * (cardTotal - 1));
				startingPos = handCenter.y - (lengthOfHand / 2);
			}
			
			//iterates through every card in a players hand
			for (int j = 0; j < gamePlayers[i]->getHand().size(); j++)
			{
				float newCardPos = 0; //This values will gaurantee to change but is initialised at 0

				//Calculates the specific cards position in relation to the first card in the hand
				if (i % 2 == 0)
				{
					float newCardPos = startingPos + (j * ((cardDimensions.x * cardScale) + cardPadding)); // The new position of the card (currently only in the x axis)
					gamePlayers[i]->getHand()[j]->getSprite().updatePos(sf::Vector2f(newCardPos, handCenter.y));
				}
				else
				{
					float newCardPos = startingPos + (j * ((cardDimensions.y * cardScale) + cardPadding)); // The new position of the card (currently only in the x axis)
					gamePlayers[i]->getHand()[j]->getSprite().updatePos(sf::Vector2f(handCenter.x, newCardPos));
				}
				
				//Render their hand
				window.draw(gamePlayers[i]->getHand()[j]->getSprite().getBody()); //renders body
				for (int k = 0; k < gamePlayers[i]->getHand()[j]->getSprite().getText().size(); k++)
				{
					window.draw(*gamePlayers[i]->getHand()[j]->getSprite().getText()[k]); // renders all text on the current face of the card
				}
			}			
		}		

		break;
	}
}

void Game::mouseClicked(sf::Event event)
{
	if (state == gameplay)
	{
		//Get mouse click position
		sf::Vector2i click = sf::Mouse::getPosition(window);
		sf::Vector2i camera_click = sf::Vector2i(camera.getCenter().x - (camera.getSize().x / 2) + (click.x),
			camera.getCenter().y - (camera.getSize().y / 2) + (click.y));
		std::cout << "Camera Click Pos: " << camera_click.x << " " << camera_click.y << std::endl;

		// obtain course deck card bounds
		sf::Vector2f playDPos = PlayDeck[PlayDeck.size() - 1]->getSprite().getBody().getPosition();

		//Check if click was within the bounds of the course deck
		if (playDPos.x < camera_click.x && camera_click.x < (playDPos.x + (cardDimensions.x * cardScale)))
		{
			if (playDPos.y < camera_click.y && camera_click.y < (playDPos.y + (cardDimensions.y * cardScale)))
			{
				std::cout << "Clicking the Play Card Deck" << std::endl;
			}
		}
	}	
}

void Game::keyPressed(sf::Event event)
{
	//Increment to next players turn
	if (event.key.code == sf::Keyboard::P && state == gameplay)
	{
		IncrementPlayer();
		currentPlayerText.setString("Current Player: " + std::to_string(currentPlayer));
	}

	//Start Game
	if (event.key.code == sf::Keyboard::M)
	{
		startGame();
	}

	//Shuffle club deck
	if (event.key.code == sf::Keyboard::O && state == gameplay)
	{
		ShuffleDeck(PlayDeck);
	}

	//shuffle course deck
	if (event.key.code == sf::Keyboard::L && state == gameplay)
	{
		ShuffleDeck(CourseDeck);
	}

	//add card to players hand
	if (event.key.code == sf::Keyboard::K && state == gameplay)
	{
		givePlayerCard(gamePlayers[0]);
	}

	//close game
	if (event.key.code == sf::Keyboard::Escape)
	{
		window.close();
	}
}

void Game::keyReleased(sf::Event event)
{
	////Key Grab Example
	//if (event.key.code == sf::Keyboard::Enter)
}

void Game::IncrementPlayer()
{
	currentPlayer += 1;
	if (currentPlayer > players)
	{
		currentPlayer = 1;
	}
}

void Game::CreateCards()
{
	//Generate Club Cards
	int clubTotal = 0;
	std::vector<std::string> clubTypes{ "driver", "iron", "pitcher", "putter" };
	std::vector<int> clubTotals{ 6, 4, 4 };
	std::vector<std::vector<int>> clubValues;
	clubValues.push_back(std::vector<int>{10, 11, 12}); // adding driver values to clubValues vector
	clubValues.push_back(std::vector<int>{5, 6, 7}); // adding driver values to clubValues vector
	clubValues.push_back(std::vector<int>{3, 4}); // adding driver values to clubValues vector
	clubValues.push_back(std::vector<int>{1, 2}); // adding driver values to clubValues vector

	for (int i = 0; i < clubTypes.size(); i++)
	{
		for (int j = 0; j < clubValues[i].size(); j++)
		{
			for (int k = 0; k < clubTotals[j]; k++)
			{
				clubTotal += 1;
				PlayDeck.push_back(std::make_unique<Card>("club", clubTypes[i], clubValues[i][j], sf::Vector2f(cardDimensions.x * cardScale, 
					cardDimensions.y * cardScale), gameUIFont));
				PlayDeck[PlayDeck.size() - 1]->getSprite().updatePos(PlayDeckPos[0]);
				//std::cout << clubTypes[i] << std::endl;
			}
		}
	}
	std::cout << "Club Total: " << clubTotal << std::endl;

	//Generate Course Cards
	int courseTotal = 0;
	std::vector<std::string> courseTypes{ "Par 3", "Par 4", "Par 5" };
	int totalPerType = 6; //How many of each different par course card we will have
	int overlapPerType = 2; //overlap between a course's distance 
	int currentHoleDistance = 15; //Starting distance at creation point, used as distance on cards

	for (int i = 0; i < courseTypes.size(); i++)
	{
		for (int j = 0; j < totalPerType; j++)
		{
			if (j != 0) { currentHoleDistance += 1; }
			courseTotal += 1;
			// Add current hole distance to card once child class has been made
			CourseDeck.push_back(std::make_unique<Card>("course", courseTypes[i], currentHoleDistance - (i * (overlapPerType - 1)), 
				sf::Vector2f(cardDimensions.x * cardScale, cardDimensions.y * cardScale), gameUIFont));
			CourseDeck[CourseDeck.size() - 1]->getSprite().updatePos(CourseDeckPos[0]);
			//std::cout << courseTypes[i] << ": " << currentHoleDistance - (i*(overlapPerType - 1)) << std::endl; //This subtracts the overlap distance between pars
		}
	}
	std::cout << "Course Total: " << courseTotal << std::endl;

	//Generate Effect Cards

	DisplayAllCards(PlayDeck);
	DisplayAllCards(CourseDeck);
}

void Game::ShuffleDeck(std::vector<std::unique_ptr<Card>>& deck)
{
	//shuffle
	std::cout << "Shuffling " << (*deck[0]).GetType() << " Deck" << std::endl;
	
	//Create Shuffle
	for (int i = deck.size() - 1; i > 0; i--)
	{
		int randint = rand() % i;

		std::swap(deck[i], deck[randint]);
	}

	DisplayAllCards(deck);
}

void Game::DisplayAllCards(std::vector<std::unique_ptr<Card>>& deck)
{
	std::cout << "All " << (deck[0])->GetType() << " Cards: " << std::endl;
	for (int i = 0; i < deck.size(); i++)
	{
		std::cout << (deck[i])->GetType() << " - " << (deck[i])->GetCardName() << " - " << (deck[i])->getDistance() << std::endl;
	}
}

void Game::givePlayerCard(std::unique_ptr<Player>& player)
{
	PlayDeck[PlayDeck.size() - 1]->getSprite().makeFaceUp(true);
	(player)->addToHand(std::move(PlayDeck[PlayDeck.size() - 1]));
	PlayDeck.pop_back();
}

void Game::startGame()
{
	///Start Game
	std::cout << "Game Setup Started: " << std::endl;

	//Generate Cards
	CreateCards();
	ShuffleDeck(PlayDeck);
	ShuffleDeck(CourseDeck);

	//intialise players
	for (int i = 0; i < players; i++)
	{
		gamePlayers.push_back(std::make_unique<Player>(playerStationPos[i]));
		for (int j = 0; j < handMax; j++)
		{
			givePlayerCard(gamePlayers[i]);
		}
		(gamePlayers[i])->printHand();
		std::cout << "Size of Play Deck: " << PlayDeck.size() << std::endl;

		gamePlayers[i]->getHand()[0]->getSprite().updatePos(gamePlayers[i]->getCenterHandPos());
	}

	//setup player turn text
	currentPlayerText.setString("Current Player: " + std::to_string(currentPlayer));
	currentPlayerText.setFont(*gameUIFont);
	currentPlayerText.setCharacterSize(25);
	currentPlayerText.setPosition(window.getSize().x / 2 - currentPlayerText.getLocalBounds().width / 2, window.getSize().y - currentPlayerText.getLocalBounds().height - 10); //minus 10 is the padding
	currentPlayerText.setFillColor(sf::Color::White);

	//change state
	state = gameplay;

	std::cout << "---- Game Setup Ended" << std::endl;
}

