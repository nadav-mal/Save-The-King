#include "Thief.h"

/*Double dispatching to know what kind of object it is.*/
void Thief::handleCollision(GameObject& object)
{
	if (&object == this) return;
	object.handleCollision(*this);
}
/*Returns to previous position.*/
void Thief::handleCollision(Wall& wall)
{
	this->setPosition(this->m_prevPosition);
}
/*Returns to previous position.*/
void Thief::handleCollision(King& king)
{
	this->setPosition(this->m_prevPosition);
}
/*Returns to previous position.*/
void Thief::handleCollision(Elf& elf)
{
	this->setPosition(this->m_prevPosition);
	elf.handleCollision(*this);
}

/*Will never happend since there is only one thief on board.*/
void Thief::handleCollision(Thief& thief)
{}

/*Returns to previous position.*/
void Thief::handleCollision(Warrior & warrior)
{
	this->setPosition(this->m_prevPosition);
}

/*Returns to previous position.*/
void Thief::handleCollision(Mage& mage)
{
	this->setPosition(this->m_prevPosition);
}
/*Returns to previous position.*/
void Thief::handleCollision(Fire& fire)
{
	this->setPosition(this->m_prevPosition);
}
/*The thief Recieves a key, sprite changes to an image of a thief holding a key.*/
void Thief::handleCollision(Key& Key)
{	
	if (Key.isDisposed())
	{
		this->m_gotKey = true; // Thief can now open gates.
		this->m_objSprite.setTexture(*Textures::instance().getObjectTexture(thiefWKey));
	}
}
/*Returns to previous position.*/
void Thief::handleCollision(Orc& orc)
{
	this->setPosition(this->m_prevPosition);
}
/*Thief can open gates if he has a key. Else, he shall not pass.*/
void Thief::handleCollision(Gate& gate)
{
	if (!this->m_gotKey) 
		this->setPosition(this->m_prevPosition);
	else // A key is used once, thief uses the key and now no longer has it.
	{
		this->m_gotKey = false; 
		this->m_objSprite.setTexture(*Textures::instance().getObjectTexture(thief));
	}
}
/*Returns to previous position.*/
void Thief::handleCollision(Throne& throne)
{
	this->setPosition(this->m_prevPosition);
}

/*this collision is handled in controller by using RTTI */
void Thief::handleCollision(Portal& portal)
{}

/*Takes gift.*/
void Thief::handleCollision(TimeGift& gift)
{}

/*Takes gift.*/
void Thief::handleCollision(ElfGift& gift)
{}
