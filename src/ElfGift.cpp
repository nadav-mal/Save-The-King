#include "ElfGift.h"

void ElfGift::handleCollision(GameObject& object)
{}

void ElfGift::handleCollision(Wall& wall)
{}

// Collected.
void ElfGift::handleCollision(King& king)
{
	 this->m_isDisposed = true;
}

void ElfGift::handleCollision(Elf& elf)
{}

// Collected.
void ElfGift::handleCollision(Thief& thief)
{
	this->m_isDisposed = true;
}

// Collected.
void ElfGift::handleCollision(Warrior& warrior)
{
	this->m_isDisposed = true;
}

// Collected.
void ElfGift::handleCollision(Mage& mage)
{
	this->m_isDisposed = true;
}

void ElfGift::handleCollision(Key& Key)
{}

void ElfGift::handleCollision(Fire& fire)
{}

void ElfGift::handleCollision(Orc& orc)
{}

void ElfGift::handleCollision(Gate& gate)
{}

void ElfGift::handleCollision(Throne& throne)
{}

void ElfGift::handleCollision(Portal& portal)
{}

void ElfGift::handleCollision(ElfGift& gift)
{}

void ElfGift::handleCollision(TimeGift& gift)
{}