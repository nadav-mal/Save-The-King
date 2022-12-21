#include "Wall.h"

Wall::~Wall()
{}

void Wall::handleCollision(GameObject& object)
{}

void Wall::handleCollision(Wall& wall)
{}

/*King encountered a wall*/
void Wall::handleCollision(King& king)
{
	king.handleCollision(*this);
}

/*Elf encountered a wall*/
void Wall::handleCollision(Elf& elf)
{
	elf.handleCollision(*this);
}

/*Thief encountered a wall*/
void Wall::handleCollision(Thief& thief)
{
	thief.handleCollision(*this);
}

/*Warrior encountered a wall*/
void Wall::handleCollision(Warrior& warrior)
{
	warrior.handleCollision(*this);
}

/*Mage encountered a wall*/
void Wall::handleCollision(Mage& mage)
{
	mage.handleCollision(*this);
}

void Wall::handleCollision(Fire& fire)
{}

void Wall::handleCollision(Key & Key)
{}

void Wall::handleCollision(Orc & orc)
{}

void Wall::handleCollision(Gate & gate)
{}

void Wall::handleCollision(Throne & throne)
{}

void Wall::handleCollision(Portal & portal)
{}

void Wall::handleCollision(TimeGift& gift)
{}

void Wall::handleCollision(ElfGift& gift)
{}
