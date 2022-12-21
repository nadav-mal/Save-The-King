#include "Elf.h"

/* Move function which moves the elf randomly on the screen. */
void Elf::move(sf::Time deltaTime, sf::Vector2u posBgn, sf::Vector2u posEnd)
{	
	int direction = rand() % DIRECTION + dirStart; // 71 to 74
	this->setDirection((sf::Keyboard::Key)direction);

	m_prevPosition = m_objSprite.getPosition();
	
	m_objSprite.move(getDirection() * ElfSpeed * deltaTime.asSeconds());

	/* Changes animation direction. */
	if (getDirection() == DOWN_DIRECTION)
		this->m_row = 0;
	if (getDirection() == LEFT_DIRECTION)
		this->m_row = 1;
	if (getDirection() == RIGHT_DIRECTION)
		this->m_row = 2;
	if (getDirection() == UP_DIRECTION)
		this->m_row = 3;

	m_frame++;

	if (m_frame >= MAX_FRAME)
	{
		m_frame -= MAX_FRAME;
		++m_col %= NUM_OF_FRAMES;
	}

	/* Changes animation sprite. */
	m_objSprite.setTextureRect(sf::IntRect(PLAYER_SIZE * m_col, PLAYER_SIZE * m_row, PLAYER_SIZE, PLAYER_SIZE));

	checkScreenCollision(posBgn, posEnd);
}

/* Double dispatching to know what kind of object it is. */
void Elf::handleCollision(GameObject& object)
{
	if (&object == this) return;
	object.handleCollision(*this);
}

// Nothing can pass through the elf.
void Elf::handleCollision(Wall& wall)
{
	this->setPosition(this->m_prevPosition);
}

void Elf::handleCollision(King& king)
{
	this->setPosition(this->m_prevPosition);
}

void Elf::handleCollision(Elf& elf)
{}

void Elf::handleCollision(Thief & thief)
{
	this->setPosition(this->m_prevPosition);
}

void Elf::handleCollision(Warrior& warrior)
{
	this->setPosition(this->m_prevPosition);
}

void Elf::handleCollision(Mage& mage)
{
	this->setPosition(this->m_prevPosition);
}

void Elf::handleCollision(Fire& fire)
{
	this->setPosition(this->m_prevPosition);
}

void Elf::handleCollision(Key& Key)
{}

void Elf::handleCollision(Orc & orc)
{
	this->setPosition(this->m_prevPosition);
}

void Elf::handleCollision(Gate& gate)
{
	this->setPosition(this->m_prevPosition);
}

void Elf::handleCollision(Throne& throne)
{
	this->setPosition(this->m_prevPosition);
}

void Elf::handleCollision(Portal& portal)
{
	this->setPosition(this->m_prevPosition);
}

void Elf::handleCollision(TimeGift& gift)
{
	this->setPosition(this->m_prevPosition);
}
void Elf::handleCollision(ElfGift& gift)
{
	this->setPosition(this->m_prevPosition);
}
