#include "Gate.h"

Gate::~Gate()
{}

/* Will never trigger. */
void Gate::handleCollision(GameObject& object)
{}

/* Do nothing if it collides itself. */
void Gate::handleCollision(Gate& Gate)
{}

/* Will never collide. */
void Gate::handleCollision(Orc& orc)
{}

/* Will never collide. */
void Gate::handleCollision(Throne& throne)
{}

/* Will never collide. */
void Gate::handleCollision(Portal& portal)
{}

/* Will never collide. */
void Gate::handleCollision(Fire& fire)
{}

/* Will never collide. */
void Gate::handleCollision(Key& Key)
{}

/* Will never collide. */
void Gate::handleCollision(Wall& wall)
{}
/* checks if thief has key, if so: dispose gate*/
void Gate::handleCollision(Thief& thief)
{
	if (thief.getKeyInfo())
		this->m_isDisposed = true;

	thief.handleCollision(*this);
}
/*Warrior handles this collision */
void Gate::handleCollision(Warrior& warrior)
{
	warrior.handleCollision(*this);
}
/*Mage handles this collision */
void Gate::handleCollision(Mage& mage)
{
	mage.handleCollision(*this);
}
/*Elf handles this collision */
void Gate::handleCollision(Elf& elf)
{
	elf.handleCollision(*this);
}
/*King handles this collision */
void Gate::handleCollision(King& king)
{
	king.handleCollision(*this);
}
void Gate::handleCollision(TimeGift& gift)
{}

void Gate::handleCollision(ElfGift& gift)
{}
