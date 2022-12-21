#pragma once
#include "UnmovableObject.h"
#include <SFML/Graphics.hpp>
#include "Macros.h"
#include "King.h"
#include "Warrior.h"
#include "Thief.h"
#include "Mage.h"
#include "Elf.h"

/* Nothing much to say, this is a wall. */
class Wall : public UnmovableObject
{
public:
	using UnmovableObject::UnmovableObject;
	~Wall() override;

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
};