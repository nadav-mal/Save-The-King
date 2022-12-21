#pragma once
#include "UnmovableObject.h"
#include <SFML/Graphics.hpp>
#include "Macros.h"
#include "King.h"
#include "Warrior.h"
#include "Thief.h"
#include "Mage.h"
#include "Elf.h"

/* Throne class is in charge of the throne object.
 * The throne is the win condition of the game.
 * If you reach the throne with the king you win. */
class Throne : public UnmovableObject
{
public:
	/* Ctor and dtor. */
	using UnmovableObject::UnmovableObject;
	~Throne() override;
	
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
	virtual void handleCollision(Throne& Throne) override;
	virtual void handleCollision(Portal& portal) override;
	virtual void handleCollision(TimeGift& gift) override;
	virtual void handleCollision(ElfGift& gift) override;
};