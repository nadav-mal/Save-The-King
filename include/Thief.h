#pragma once
#include "Player.h"
#include "Elf.h"

/* Thief class is in charge of the thief character.
 * The thief can loot keys to open gates,
 * but he may only hold one key at a time. */
class Thief : public Player
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

	/* Returns if the thief has a key or not. */
	bool getKeyInfo() const
	{
		return m_gotKey;
	}

	void setKeyInfo(bool info)
	{
		this->m_gotKey = info;
	}

private:
	bool m_gotKey = false; // To save info regarding key possession.
};
