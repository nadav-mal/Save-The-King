#include "Fire.h"

Fire::~Fire()
{
}

/* Will never trigger. */
void Fire::handleCollision(GameObject& object)
{}

/* Do nothing if it collides itself. */
void Fire::handleCollision(Fire& fire)
{}

/* Will never collide. */
void Fire::handleCollision(Key & Key)
{}

/* Will never collide. */
void Fire::handleCollision(Orc & orc)
{}

/* Will never collide. */
void Fire::handleCollision(Gate & gate)
{}

/* Will never collide. */
void Fire::handleCollision(Throne & throne)
{}

/* Will never collide. */
void Fire::handleCollision(Portal & portal)
{}

/* Will never collide. */
void Fire::handleCollision(Wall& wall)
{}

// King encountered fire.
void Fire::handleCollision(King& king)
{
	king.handleCollision(*this);
}

// Elf encountered fire.
void Fire::handleCollision(Elf& elf)
{
	elf.handleCollision(*this);
}

// Thief encountered fire.
void Fire::handleCollision(Thief& thief)
{
	thief.handleCollision(*this);
}

// Warrior encountered fire.
void Fire::handleCollision(Warrior& warrior)
{
	warrior.handleCollision(*this);
}

// Mage encountered fire.
void Fire::handleCollision(Mage& mage)
{
	this->m_isDisposed = true;
}
void Fire::handleCollision(TimeGift& gift)
{}

void Fire::handleCollision(ElfGift& gift)
{}
