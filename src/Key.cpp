#include "Key.h"

Key::~Key()
{
}

/* Will never trigger. */
void Key::handleCollision(GameObject& object)
{}

/* Do nothing if it collides itself. */
void Key::handleCollision(Key& key)
{}

/* Will never collide. */
void Key::handleCollision(Orc & orc)
{}

/* Will never collide. */
void Key::handleCollision(Gate& gate)
{}

/* Will never collide. */
void Key::handleCollision(Throne & throne)
{}

/* Will never collide. */
void Key::handleCollision(Portal & portal)
{}

/* Will never collide. */
void Key::handleCollision(Fire& fire)
{}

/* Will never collide. */
void Key::handleCollision(Wall& wall)
{}

void Key::handleCollision(King& king)
{
	king.handleCollision(*this);
}
/*Dispose the key if the thief isnt holding a key*/
void Key::handleCollision(Thief& thief)
{
	if (!thief.getKeyInfo())
		this->m_isDisposed = true;

	thief.handleCollision(*this); //thief handles collision either way
}

void Key::handleCollision(Warrior& warrior)
{}

void Key::handleCollision(Mage& mage)
{}

void Key::handleCollision(Elf& elf)
{}

void Key::handleCollision(TimeGift& gift)
{}

void Key::handleCollision(ElfGift& gift)
{}
