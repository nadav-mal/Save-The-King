#pragma once
#include <SFML/Graphics.hpp>
#include "Textures.h"

class Elf;
class Player;
class King;
class Warrior;
class Mage;
class Thief;
class Fire;
class Key;
class Wall;
class Orc;
class Gate;
class Throne;
class Portal;
class TimeGift;
class ElfGift;

/* The GameObject class is the base class of all of the objects in the game. */
class GameObject
{
public:
	//D-tor and C-tor
	GameObject(sf::Vector2f& pos, Objects objEnum);
	virtual ~GameObject() = default;

	virtual void drawObject(sf::RenderWindow& window); // Draw function for the objects.

	/* Getters. */
	sf::FloatRect getGlobalBounds() const; // Returns the bounding rectangle of the object.
	sf::Sprite& getSprite(); // Returns the sprite of the object.
	sf::Vector2f getPosition() const; // Returns the position of the object.

	/* Setters. */
	void setPosition(const sf::Vector2f& loc);
	void setTexture(const sf::Texture* texture);
	void setDisposal(bool dispose);

	// Returns wether the object should be removed.
	bool isDisposed() const
	{
		return m_isDisposed;
	}

	/* Collision handlers. */
	virtual void handleCollision(GameObject& object) = 0;
	virtual void handleCollision(Wall& wall) = 0;
	virtual void handleCollision(King& king) = 0;
	virtual void handleCollision(Elf& elf) = 0;
	virtual void handleCollision(Thief& thief) = 0;
	virtual void handleCollision(Warrior& warrior) = 0;
	virtual void handleCollision(Mage& mage) = 0;
	virtual void handleCollision(Fire& fire) = 0;
	virtual void handleCollision(Key& Key) = 0;
	virtual void handleCollision(Orc& orc) = 0;
	virtual void handleCollision(Gate& gate) = 0;
	virtual void handleCollision(Throne& throne) = 0;
	virtual void handleCollision(Portal& portal) = 0;
	virtual void handleCollision(TimeGift& gift) = 0;

protected:
	sf::Sprite m_objSprite; // Stores the sprite of the object.
	bool m_isDisposed; // Stores the current disposal status.

	// For animations.
	int m_row; 
	int m_col;
	int m_frame;
};