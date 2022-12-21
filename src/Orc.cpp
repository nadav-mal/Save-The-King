#include "Orc.h"

Orc::~Orc()
{
}

/* Will never trigger. */
void Orc::handleCollision(GameObject& object)
{}

/* Do nothing if it collides itself. */
void Orc::handleCollision(Orc& Orc)
{}

/* Will never collide. */
void Orc::handleCollision(Gate & gate)
{}

/* Will never collide. */
void Orc::handleCollision(Throne & throne)
{}

void Orc::handleCollision(Portal & portal)
{}

/* Will never collide. */
void Orc::handleCollision(Key& Key)
{}

/* Will never collide. */
void Orc::handleCollision(Fire& fire)
{}

/* Will never collide. */
void Orc::handleCollision(Wall& wall)
{}

/*King handles this collision */
void Orc::handleCollision(King& king)
{
	king.handleCollision(*this);
}

/*Thief handles this collision */
void Orc::handleCollision(Thief& thief)
{
	thief.handleCollision(*this);
}

/*Warrior kills the orc */
void Orc::handleCollision(Warrior& warrior)
{
	this->m_isDisposed = true;
}

/*Mage handles this collision */
void Orc::handleCollision(Mage& mage)
{
	mage.handleCollision(*this);
}

/*Elf handles this collision */
void Orc::handleCollision(Elf& elf)
{
	elf.handleCollision(*this);
}

void Orc::handleCollision(TimeGift& gift)
{}

void Orc::handleCollision(ElfGift& gift)
{}
