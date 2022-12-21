#include "GameObject.h"
#include "TimeGift.h"

/* Constructor of GameObject class - Creates the objects. */
GameObject::GameObject(sf::Vector2f& pos, Objects objEnum)
{
    sf::Texture* temp = Textures::instance().getObjectTexture(objEnum);
    m_objSprite.setTexture(*temp);
    m_objSprite.setPosition(pos);
    m_isDisposed = false;

    // For animations.
    m_frame = 0;
    m_row = 0;
    m_col = 0;

    // Unmovable.
    if (objEnum > elf)
    {
        float x = m_objSprite.getGlobalBounds().height;
        float y = m_objSprite.getScale().y;
        m_objSprite.scale(x, y);
        m_objSprite.setScale(sf::Vector2f(((float)FIXED_BLOCK_SIZE / x), (float)FIXED_BLOCK_SIZE / x));
    }
    // Movable.
    else
    {
        m_objSprite.setTextureRect(sf::IntRect(PLAYER_SIZE, 0, PLAYER_SIZE, PLAYER_SIZE));
        m_objSprite.scale(1.9f, 1.9f);
    }
}

/* This function is in charge of getting the position of the sprite of the object. */
sf::Vector2f GameObject::getPosition() const
{
    return m_objSprite.getPosition();
}

/* This function recieves a location and sets the objects position to this location. */
void GameObject::setPosition(const sf::Vector2f& loc)
{
    m_objSprite.setPosition(loc);
}
/* This function recieves a texture and sets it as the objects sprite. */
void GameObject::setTexture(const sf::Texture* texture)
{
    this->m_objSprite.setTexture(*texture);
}
/* This function sets the disposal of an object. */
void GameObject::setDisposal(bool dispose)
{
    this->m_isDisposed = dispose;
}
/*This function returns the sprite of an object*/
sf::Sprite& GameObject::getSprite()
{
    return m_objSprite;
}
/*This function draws the sprite on a given window*/
void GameObject::drawObject(sf::RenderWindow& window)
{
    window.draw(m_objSprite);
}
/*This function returns the global bounds of an object*/
sf::FloatRect GameObject::getGlobalBounds() const
{
    return m_objSprite.getGlobalBounds();
}

