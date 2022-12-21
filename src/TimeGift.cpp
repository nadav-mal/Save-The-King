#include "TimeGift.h"


/*This function randomize time of gift*/
int TimeGift::getTime() const
{
	int pos = rand() % 2;

	if (pos)
		return ((rand() % TimeGiftSeed) + 1);
	else
		return (-((rand() % TimeGiftSeed) + 1));
}

void TimeGift::handleCollision(GameObject& object)
{}

void TimeGift::handleCollision(Wall& wall)
{}

/*King takes gift*/
void TimeGift::handleCollision(King& king)
{
	 this->m_isDisposed = true;
}
/*Elf will handle its own collision*/
void TimeGift::handleCollision(Elf& elf)
{
	elf.handleCollision(*this);
}
/*Thief takes gift*/
void TimeGift::handleCollision(Thief& thief)
{
	this->m_isDisposed = true;
}
/*Warrior takes gift*/
void TimeGift::handleCollision(Warrior& warrior)
{
	this->m_isDisposed = true;
}
/*Mage takes gift*/
void TimeGift::handleCollision(Mage& mage)
{
	this->m_isDisposed = true;
}

void TimeGift::handleCollision(Key& Key)
{}

void TimeGift::handleCollision(Fire& fire)
{}

void TimeGift::handleCollision(Orc& orc)
{}

void TimeGift::handleCollision(Gate& gate)
{}

void TimeGift::handleCollision(Throne& throne)
{}

void TimeGift::handleCollision(Portal& portal)
{}

void TimeGift::handleCollision(ElfGift& gift)
{}

void TimeGift::handleCollision(TimeGift& gift)
{}