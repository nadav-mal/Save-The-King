#include "Warrior.h"


/*Double dispatching to know what kind of object it is.*/
void Warrior::handleCollision(GameObject& object)
{
	if (&object == this) return;
	object.handleCollision(*this);
}

/*Returns to previous position*/
void Warrior::handleCollision(Elf& elf)
{
	this->setPosition(this->m_prevPosition);
	elf.handleCollision(*this);
}

/*Returns to previous position.*/
void Warrior::handleCollision(Thief& thief)
{
	this->setPosition(this->m_prevPosition);
}

/*Returns to previous position.*/
void Warrior::handleCollision(Wall& wall)
{
	this->setPosition(this->m_prevPosition);
}

/*Returns to previous position.*/
void Warrior::handleCollision(Mage& mage)
{
	this->setPosition(this->m_prevPosition);
}

/*Returns to previous position.*/
void Warrior::handleCollision(Key& Key)
{
	this->setPosition(this->m_prevPosition);
}

/*Returns to previous position.*/
void Warrior::handleCollision(Fire & fire)
{
	this->setPosition(this->m_prevPosition);
}

/*Returns to previous position.*/
void Warrior::handleCollision(Orc& orc)
{}

/*Returns to previous position.*/
void Warrior::handleCollision(Gate & gate)
{
	this->setPosition(this->m_prevPosition);
}

/*Returns to previous position.*/
void Warrior::handleCollision(Throne& throne)
{
	this->setPosition(this->m_prevPosition);
}

/*This collision is handled by RTTI via controller*/
void Warrior::handleCollision(Portal& portal)
{}

/*Will never happend since there is only one warrior.*/
void Warrior::handleCollision(Warrior& warrior)
{}

/*Returns to previous location.*/
void Warrior::handleCollision(King& king)
{
	this->setPosition(this->m_prevPosition);
}

/*Takes gift.*/
void Warrior::handleCollision(TimeGift& gift)
{}

/*Takes gift.*/
void Warrior::handleCollision(ElfGift& gift)
{}
