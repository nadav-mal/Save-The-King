#pragma once
#include "Player.h"
#include "Elf.h"

/* King class is in charge of the king character. */
class King : public Player
{
public:
	using Player::Player;

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