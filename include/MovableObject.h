#pragma once
#include "GameObject.h"

/* The MovableObject class is in charge of all the objects which are capable of moving. 
 * List of moving objects: King, Thief, Mage, Warrior, Elf. */
class MovableObject : public GameObject
{
public:
	//C-tor and D-tor
	MovableObject(sf::Vector2f& pos, Objects objEnum);
	virtual ~MovableObject() = default;

	/* Getters. */
	sf::Vector2f getPrevPosition() const;
	sf::Vector2f getDirection() const;

	/* Setters. */
	void setDirection(sf::Keyboard::Key key);
	void setPrevPosition(const sf::Vector2f& loc);

	/* Moving related functions. */
	void checkScreenCollision(sf::Vector2u posBgn, sf::Vector2u posEnd);
	virtual void move(sf::Time deltaTime, sf::Vector2u posBgn, sf::Vector2u posEnd) = 0; // Pure virtual function

	/* Collision functions. */
	bool collidesWith(const GameObject& obj);
	virtual void handleCollision(GameObject& object) = 0;
	virtual void handleCollision(Wall& wall) = 0;
	virtual void handleCollision(King& king) = 0;
	virtual void handleCollision(Elf& elf) = 0;
	virtual void handleCollision(Thief& thief) = 0;
	virtual void handleCollision(Warrior& warrior) = 0;
	virtual void handleCollision(Mage& mage) = 0;
	virtual void handleCollision(Fire& fire) = 0;
	virtual void handleCollision(Key& key) = 0;
	virtual void handleCollision(Orc& orc) = 0;
	virtual void handleCollision(Gate& gate) = 0;
	virtual void handleCollision(Throne& throne) = 0;
	virtual void handleCollision(Portal& portal) = 0;
	virtual void handleCollision(ElfGift& gift) = 0;
	virtual void handleCollision(TimeGift& portal) = 0;

private:
	sf::Vector2f m_direction; // Stores the direction which the object is walking towards.

protected:
	sf::Vector2f m_prevPosition; // Stores the previous position (before moving).
};