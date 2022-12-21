#include "MovableObject.h"
/*Movable Object C-tor uses the C-tor of gameObject and defines the previous
  position to be the current position. */
MovableObject::MovableObject(sf::Vector2f& pos, Objects objEnum)
	: GameObject(pos, objEnum), m_prevPosition(m_objSprite.getPosition())
{}
/*SetDirection recieves a keyboard botton click and updates the current character's
  location*/
void MovableObject::setDirection(sf::Keyboard::Key Key)
{
	switch (Key) //key is the given Keyboard press by user
	{
	default:
		m_direction = DEFAULT_DIRECTION;
		break;

	case sf::Keyboard::Key::Left:
		m_direction = LEFT_DIRECTION;
		break;

	case sf::Keyboard::Key::Right:
		m_direction = RIGHT_DIRECTION;
		break;

	case sf::Keyboard::Key::Up:
		m_direction = UP_DIRECTION;
		break;

	case sf::Keyboard::Key::Down:
		m_direction = DOWN_DIRECTION;
		break;
	}
}

/*Returns current direction*/
sf::Vector2f MovableObject::getDirection() const
{
	return m_direction;
}
/*Checks if current move exits the screen bounds. */
void MovableObject::checkScreenCollision(sf::Vector2u posBgn, sf::Vector2u posEnd)
{
	if (this->m_objSprite.getPosition().x < posBgn.x)
		this->m_objSprite.setPosition(posBgn.x, this->m_objSprite.getPosition().y);

	if (this->m_objSprite.getPosition().y < posBgn.y)
		this->m_objSprite.setPosition(this->m_objSprite.getPosition().x, posBgn.y);

	if (this->m_objSprite.getPosition().x + this->m_objSprite.getGlobalBounds().width > posEnd.x)
		this->m_objSprite.setPosition(posEnd.x - this->m_objSprite.getGlobalBounds().width, this->m_objSprite.getPosition().y);

	if (this->m_objSprite.getPosition().y + this->m_objSprite.getGlobalBounds().height > posEnd.y)
		this->m_objSprite.setPosition(this->m_objSprite.getPosition().x, posEnd.y - this->m_objSprite.getGlobalBounds().height);
}
/*Returns previous position*/
sf::Vector2f MovableObject::getPrevPosition() const
{
	return m_prevPosition;
}
/*Adjusting previous position before moving towards a new position.*/
void MovableObject::setPrevPosition(const sf::Vector2f& loc)
{
	this->m_prevPosition = loc;
}
/*Checks if a movable object collides with a game object.*/
bool MovableObject::collidesWith(const GameObject& obj)
{
	return getGlobalBounds().intersects(obj.getGlobalBounds());
}
