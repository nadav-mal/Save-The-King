#pragma once
#include "UnmovableObject.h"

/* The Gifts class is the base class of the different gifts in the game. */
class Gifts : public UnmovableObject
{
public:
	// C-tor and d-tor.
	using UnmovableObject::UnmovableObject;
	~Gifts() {};

	// Collision handlers.
	virtual void handleCollision(GameObject& object) = 0;
	virtual void handleCollision(Wall& wall) = 0;
	virtual void handleCollision(King& king) = 0;
	virtual void handleCollision(Elf& elf) = 0;
	virtual void handleCollision(Thief& thief) = 0;
	virtual void handleCollision(Warrior& warrior) = 0;
	virtual void handleCollision(Mage& mage) = 0;
	virtual void handleCollision(Fire& fire) = 0;
	virtual void handleCollision(Key& Key) = 0;
	virtual void handleCollision(Orc& orc) = 0;
	virtual void handleCollision(Gate& gate) = 0;
	virtual void handleCollision(Throne& throne) = 0;
	virtual void handleCollision(Portal& portal) = 0;
	virtual void handleCollision(TimeGift& gift) = 0;
	virtual void handleCollision(ElfGift& gift) = 0;
};
