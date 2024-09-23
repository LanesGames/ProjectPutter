#pragma once
//This file just holds notes on the game
//
// HotKeys:
//
// P - Moves to the next player turn
// O - Shuffles Club (Play) Deck
// L - Shuffles Course Deck
// M - Start Game
// K - Add card to a players hand
//
// Current Spec of the game:
//
// 1. Currently the game has a start up function
// 2. This start up function Generates all game cards (minus Effect Cards)
// 3. It then shuffles the decks
// 4. Generates the amount of players the game wants to have
// 5. Deals each player 5 cards randomly from the top of the deck.
// 6. It displays all of these cards face up to start with
//
// Notes:
// 
// - Changing the visible text in CardBody classes currently doesnt use unique_pointers and so is not fully efficient
// - Need to make the text and use of pointers for card visuals better as it seems a little clunky right now 
// - Currently Player hand only go left to rightas I only use the x dimensions of a card, to fix this I would need to 
// add a player ID and use even and odd numbers to distinguish the use of x or y
// - Currently the position of the cards in a players hand are decided and calculated in the render function which is inefficient due to the fact the game runs on events
// - Need to make the comments in the game a lot better to not forget what everything does
//