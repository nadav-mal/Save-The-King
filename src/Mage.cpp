#include "Mage.h"
#include <iostream>


/*Double dispatching to know what kind of object it is.*/
void Mage::handleCollision(GameObject& object)
{
	if (&object == this) return;
	object.handleCollision(*this);
}

/*Returns to previous position.*/
void Mage::handleCollision(King& king)
{
	this->setPosition(this->m_prevPosition);
}

/*Returns to previous position.*/
void Mage::handleCollision(Thief& thief)
{
	this->setPosition(this->m_prevPosition);
}

/*Returns to previous position.*/
void Mage::handleCollision(Warrior& warrior)
{
	this->setPosition(this->m_prevPosition);
}

/*Will never happend since there is only one mage.*/
void Mage::handleCollision(Mage& mage)
{}

/*mage Puts fire down in the fire collision with mage, without moving*/
void Mage::handleCollision(Fire & fire)
{
	this->setPosition(this->m_prevPosition);
}


void Mage::handleCollision(Key& Key)
{}

/*Returns to previous position.*/
void Mage::handleCollision(Orc & orc)
{
	this->setPosition(this->m_prevPosition);
}

/*Returns to previous position.*/
void Mage::handleCollision(Gate& gate)
{
	this->setPosition(this->m_prevPosition);
}

/*Returns to previous position.*/
void Mage::handleCollision(Throne& throne)
{
	this->setPosition(this->m_prevPosition);
}

/*This collision is handled by RTTI via controller*/
void Mage::handleCollision(Portal& portal)
{}

/*Returns to previous position.*/
void Mage::handleCollision(Wall& wall)
{
	this->setPosition(this->m_prevPosition);
}

/*Returns to previous position.*/
void Mage::handleCollision(Elf& elf)
{
	this->setPosition(this->m_prevPosition);
	elf.handleCollision(*this);
}

/*Takes gift	.*/
void Mage::handleCollision(TimeGift& gift)
{
	gift.handleCollision(*this);
}

/*Takes gift.*/
void Mage::handleCollision(ElfGift& gift)
{
	gift.handleCollision(*this);
}
