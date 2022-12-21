#pragma once
#include "UnmovableObject.h"
#include <SFML/Graphics.hpp>
#include "Macros.h"
#include "King.h"
#include "Warrior.h"
#include "Thief.h"
#include "Mage.h"
#include "Elf.h"

/* The Gate class is in charge of the gate object. 
 * The gate can be opened with a key, which can only be obtained by the thief. */
class Gate : public UnmovableObject
{
public:
	// C-tor and d-tor.
	using UnmovableObject::UnmovableObject;
	~Gate() override;

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
	virtual void handleCollision(Gate& Gate) override;
	virtual void handleCollision(Orc& orc) override;
	virtual void handleCollision(Throne& throne) override;
	virtual void handleCollision(Portal& portal) override;
	virtual void handleCollision(TimeGift& gift) override;
	virtual void handleCollision(ElfGift& gift) override;
};