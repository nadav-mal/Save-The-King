#pragma once
#include "MovableObject.h"

/* The Player class is in charge of the players (characters) of the game. 
 * The characters are: King, Thief, Mage, Warrior. */
class Player : public MovableObject
{
public:
	// C-tor.
	using MovableObject::MovableObject;

	// Function to move the players.
	virtual void move(sf::Time deltaTime, sf::Vector2u posBgn, sf::Vector2u posEnd) override;

	/* Collision handlers. */
	virtual void handleCollision(GameObject& object) = 0;
	virtual void handleCollision(Wall& wall) = 0;
	virtual void handleCollision(King& king) = 0;
	virtual void handleCollision(Thief& thief) = 0;
	virtual void handleCollision(Warrior& warrior) = 0;
	virtual void handleCollision(Mage& mage) = 0;
	virtual void handleCollision(Fire& fire) = 0;
	virtual void handleCollision(Key& Key) = 0;
	virtual void handleCollision(Orc& orc) = 0;
	virtual void handleCollision(Gate& gate) = 0;
	virtual void handleCollision(Throne& throne) = 0;
	virtual void handleCollision(Portal& portal) = 0;
};