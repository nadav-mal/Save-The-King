#include "Portal.h"

Portal::~Portal()
{
}

/* Will never trigger. */
void Portal::handleCollision(GameObject& object)
{}

/* Do nothing if it collides itself. */
void Portal::handleCollision(Portal& Portal)
{}

/* Will never collide. */
void Portal::handleCollision(Orc& orc)
{}

/* Will never collide. */
void Portal::handleCollision(Gate& gate)
{}

/* Will never collide. */
void Portal::handleCollision(Throne& throne)
{}

/* Will never collide. */
void Portal::handleCollision(Fire& fire)
{}

/* Will never collide. */
void Portal::handleCollision(Key & Key)
{}

/* Will never collide. */
void Portal::handleCollision(Wall& wall)
{}

void Portal::handleCollision(King& king)
{}

void Portal::handleCollision(Thief& thief)
{}

void Portal::handleCollision(Warrior& warrior)
{}

/* Mage encountered a portal. */
void Portal::handleCollision(Mage& mage)
{
	mage.handleCollision(*this);
}

/*Elf handles this collision */
void Portal::handleCollision(Elf& elf)
{
	elf.handleCollision(*this);
}

void Portal::handleCollision(TimeGift& gift)
{}

void Portal::handleCollision(ElfGift& gift)
{}
