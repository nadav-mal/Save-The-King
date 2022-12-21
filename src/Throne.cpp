#include "Throne.h"

Throne::~Throne()
{
}

/* Will never trigger. */
void Throne::handleCollision(GameObject& object)
{}

/* Do nothing if it collides itself. */
void Throne::handleCollision(Throne& Throne)
{}

/* Will never collide. */
void Throne::handleCollision(Portal & portal)
{}

/* Will never collide. */
void Throne::handleCollision(Orc& orc)
{}

/* Will never collide. */
void Throne::handleCollision(Gate& gate)
{}

/* Will never collide. */
void Throne::handleCollision(Fire& fire)
{}

/* Will never collide. */
void Throne::handleCollision(Key & Key)
{}

/* Will never collide. */
void Throne::handleCollision(Wall& wall)
{}

/*This collision is handled by RTTI via controller*/
void Throne::handleCollision(King& king)
{
	king.handleCollision(*this);
}

/*Thief encountered the throne*/
void Throne::handleCollision(Thief& thief)
{
	thief.handleCollision(*this);
}

/*Warrior encountered the throne*/
void Throne::handleCollision(Warrior& warrior)
{
	warrior.handleCollision(*this);
}

/*Mage encountered the throne*/
void Throne::handleCollision(Mage& mage)
{
	mage.handleCollision(*this);
}

/*Elf encountered the throne*/
void Throne::handleCollision(Elf& elf)
{
	elf.handleCollision(*this);
}

void Throne::handleCollision(TimeGift& gift)
{}

void Throne::handleCollision(ElfGift& gift)
{}
