#include "King.h"

/*Double dispatching to know what kind of object it is.*/
void King::handleCollision(GameObject& object)
{
	if (&object == this) return;
	object.handleCollision(*this);
}

/*Returns to previous position.*/
void King::handleCollision(Wall& wall)
{
	this->setPosition(this->m_prevPosition);
}


void King::handleCollision(King& king)
{}

/*Returns to previous position.*/
void King::handleCollision(Elf& elf)
{
	this->setPosition(this->m_prevPosition);
	elf.handleCollision(*this);
}

/*Returns to previous position.*/
void King::handleCollision(Thief& thief)
{
	this->setPosition(this->m_prevPosition);
}

/* Returns to previous position. */
void King::handleCollision(Warrior& warrior)
{
	this->setPosition(this->m_prevPosition);
}

/* Returns to previous position. */
void King::handleCollision(Mage& mage)
{
	this->setPosition(this->m_prevPosition);
}

/* Returns to previous position. */
void King::handleCollision(Fire& fire)
{
	this->setPosition(this->m_prevPosition);
}

/* Returns to previous position. */
void King::handleCollision(Key& Key)
{}

/* Returns to previous position. */
void King::handleCollision(Orc& orc)
{
	this->setPosition(this->m_prevPosition);
}

/* Returns to previous position. */
void King::handleCollision(Gate& gate)
{
	this->setPosition(this->m_prevPosition);
}

/* This collision is handled by RTTI via controller */
void King::handleCollision(Throne& throne)
{}

void King::handleCollision(Portal & portal)
{}

/*Takes gift.*/
void King::handleCollision(TimeGift& gift)
{
	gift.handleCollision(*this);
}

/*Takes gift.*/
void King::handleCollision(ElfGift& gift)
{
	gift.handleCollision(*this);
}
