#pragma once
#include "MovableObject.h"
#include <SFML/Graphics.hpp>
#include "Macros.h"

#include "Wall.h"
#include "Key.h"
#include "Fire.h"
#include "Orc.h"
#include "Gate.h"
#include "Throne.h"
#include "Portal.h"
#include "ElfGift.h"
#include "TimeGift.h"

/* The Elf class is in charge of elves in the game. 
 * The elves can block the players from moving. */
class Elf : public MovableObject
{
public:
	using MovableObject::MovableObject;

	// Function to move the elves randomly.
	virtual void move(sf::Time deltaTime, sf::Vector2u posBgn, sf::Vector2u posEnd) override;

	/* Collision handlers. */
	virtual void handleCollision(GameObject& object) override;
	virtual void handleCollision(Wall& wall) override;
	virtual void handleCollision(King& king) override;
	virtual void handleCollision(Elf& elf) override;
	virtual void handleCollision(Thief& thief) override;
	virtual void handleCollision(Warrior& warrior) override;
	virtual void handleCollision(Mage& mage) override;
	virtual void handleCollision(Fire& fire) override;
	virtual void handleCollision(Key& Key) override;
	virtual void handleCollision(Orc& orc) override;
	virtual void handleCollision(Gate& gate) override;
	virtual void handleCollision(Throne& throne) override;
	virtual void handleCollision(Portal& portal) override;
	virtual void handleCollision(TimeGift& gift) override;
	virtual void handleCollision(ElfGift& gift) override;

private:
	// Stores the current direction which the elf is walking towards.
	sf::Vector2f m_elfDirection;
};