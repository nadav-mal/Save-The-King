#pragma once
#include "GameObject.h"

/* UnmovableObject class is in charge of the unmovable objects in the game. */
class UnmovableObject : public GameObject
{
public:
	//C-tor and D-tor
	using GameObject::GameObject;
	virtual ~UnmovableObject() = default;

	/* Virtual collision handlers. */
	virtual void handleCollision(GameObject& object) = 0;
	virtual void handleCollision(Wall& wall) = 0;
	virtual void handleCollision(King& king) = 0;
	virtual void handleCollision(Elf& elf) = 0;
	virtual void handleCollision(Thief & thief) = 0;
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